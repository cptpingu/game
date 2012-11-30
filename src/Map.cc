#include "Map.hh"

#include "Core/Traits.hh"
#include "Architecte.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Random.hh"

namespace
{
  template <typename T, bool is_pointer>
  struct LoadFromFileHelper
  {
    static bool func(const std::string& filename, T& collection)
    {
      std::ifstream file(filename.c_str());
      typename T::raw_item_type::type x;
      typename T::raw_item_type::type y;
      typename T::raw_item_type::type z;

      if (!file)
        return false;

      while (file)
      {
        file >> x >> y >> z;
        collection.add(new typename T::raw_item_type(x, y, z));
      }

      return true;
    }
  };

  template <typename T>
  struct LoadFromFileHelper<T, false>
  {
    static bool func(const std::string& filename, T& collection)
    {
      std::ifstream file(filename.c_str());
      typename T::type::raw_type x;
      typename T::type::raw_type y;
      typename T::type::raw_type z;

      if (!file)
        return false;

      while (file)
      {
        file >> x >> y >> z;
        collection.add(typename T::raw_item_type(x, y, z));
      }

      return true;
    }
  };

  template <typename T>
  bool loadFromFile(const std::string& filename, T& collection)
  {
    return LoadFromFileHelper<T, Core::isPointer<typename T::item_type>::value>::func(filename, collection);
  }

  bool loadFromFile(const std::string& filename, Map::blocks_type& blocks)
  {
      std::ifstream file(filename.c_str());
      int x;
      int y;
      int z;

      if (!file)
        return false;

      while (file)
      {
        file >> x >> y >> z;
        blocks.insert(Map::blocks_type::value_type(Core::Container3D<int>(x, y, z), new Block(x, y, z)));
      }

    return true;
  }

  void checkAndLinks(const Map::temp_map_type& map, Block* block)
  {
#define LINK(X,Y,Z,ASSIGN)                                              \
    {                                                                   \
      auto found = map.find(Core::Container3D<int>(block->_x + X, block->_y + Y, block->_z + Z)); \
      if (found != map.end())                                           \
        block->ASSIGN = found->second;                                  \
    }

    LINK(1,0,0, _left);
    LINK(-1,0,0, _right);
    LINK(0,1,0, _front);
    LINK(0,-1,0, _back);
    LINK(0,0,1, _up);
    LINK(0,0,-1, _down);

#undef LINK
  }




  /*void linkBlocks(Map::blocks_type& blocks)
  {
    Map::temp_map_type map;
    auto end = blocks.end();
    for (auto it = blocks.begin(); it != end; ++it)
    {
      Core::Container3D<int> cont((*it)->_x, (*it)->_y, (*it)->_z);
      Block* block = *it;
      map.insert(Map::temp_map_type::value_type(cont, block));
    }

    auto mapEnd = map.end();
    for (auto it = map.begin(); it != mapEnd; ++it)
      checkAndLinks(map, it->second);
  }*/
} //namespace


void
Map::createBlock(const Core::Container3D<int>& where)
{

  if (_blocks.find(where) == _blocks.end())
   _blocks.insert(blocks_type::value_type(where, new Block(where._x , where._y, where._z)));

}

void Map::InitGroundBlocks(int SIZE)
{
    Core::Container3D<int> where;

      for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
     {where._x= i;
      where._y= j;
      where._z= 100*cos(fabs(i+j-50)*2*3.1467) + 100*sin(fabs(i+j-50)*2*3.1467);
      //where._z = 100*exp(- (sqrt((i-25)^2+(j-25)^2))/100);
      //where._z= where._z + Random::rand()%3 - 1;
      //where._z = 100/(sqrt((i-SIZE/2)*(i-SIZE/2) + (j-SIZE/2)*(j-SIZE/2)));
      createBlock(where);
}


}



void
Map::insertBlockfromBlock(const Block* who, const Block::FaceType where)
{
    if (!who)
      return;

    Core::Container3D<int> container;
    switch (where)
    {
       case Block::back:
        container = Core::Container3D<int>(who->_x , who->_y-1, who->_z);
        break;
      case Block::front:
        container = Core::Container3D<int>(who->_x , who->_y+1, who->_z);
        break;
      case Block::left:
        container = Core::Container3D<int>(who->_x+1 , who->_y, who->_z );
        break;
      case Block::right:
        container = Core::Container3D<int>(who->_x-1 , who->_y, who->_z );
        break;
      case Block::up:
        container = Core::Container3D<int>(who->_x , who->_y, who->_z+1);
        break;
      case Block::down:
        container = Core::Container3D<int>(who->_x, who->_y, who->_z-1);
        break;
      default:
        assert(false && "Bad face");
    }
    if (_blocks.find(container) == _blocks.end())
      _blocks.insert(blocks_type::value_type(container, new Block(container._x , container._y, container._z)));
}




void
Map::eraseBlock(const Block* who)
{
    if (who)
    {
        auto container = Core::Container3D<int>(who->_x, who->_y, who->_z);
        delete _blocks[container];
        _blocks.erase(container);
    }
}

Block*
Map::findBlock(const Core::Container3D<int>& where) const
  {
    auto found = _blocks.find(where);
    if(found == _blocks.end())
        return(0);
    return(found->second);
  }

Map::Map()
{
}

Map::~Map()
{
  clear();
}

bool
Map::loadBlocks(const std::string& filename)
{
  if (!loadFromFile(filename, _blocks))
    return false;

  //linkBlocks(_blocks);
  return true;
}

namespace
{
  Chunk* loadChunk(int x, int y, const Map::chunks_type& chunks)
  {
    Chunk* chunk = new Chunk(x, y);

    if (!chunk->loadFromFile())
    {
      Chunk::chunk_coord_type coords;
      Architecte::initChunk(coords, std::make_pair(x, y), chunks);
      chunk->createRealCoord(coords);
      const bool res = chunk->saveToFile(coords);
      assert(res && "Unable to save file!");
      _UNUSED(res);
    }
    return chunk;
  }
} // namespace

void
Map::chunkLazyLoading(const Vector3D& position, const Map::chunks_type& chunks)
{
  const int x = Chunk::absoluteToChunkCoord(position._x);
  const int y = Chunk::absoluteToChunkCoord(position._y);
  std::vector<std::pair<int, int> > tmpChunkList;

#define LAZY_LOAD(X, Y)                                                 \
  {                                                                     \
    std::pair<int, int> current(x + (X), y + (Y));                      \
    tmpChunkList.push_back(current);                                    \
    if (_chunks.find(current) == _chunks.end())                         \
      _chunks.insert(chunks_type::value_type(current, loadChunk(current.first, current.second, chunks))); \
  }

  LAZY_LOAD(0, 0);
  LAZY_LOAD(1, 0);
  LAZY_LOAD(0, 1);
  LAZY_LOAD(-1, 0);
  LAZY_LOAD(0, -1);
  LAZY_LOAD(-1, 1);

  LAZY_LOAD(-1, -1);
  LAZY_LOAD(1, -1);
  LAZY_LOAD(1, 1);



#undef LAZY_LOAD

  std::vector<std::pair<int, int> > deleteList;
  auto chunkEnd = _chunks.end();
  for (auto it =_chunks.begin(); it != chunkEnd; ++it)
    if (std::find(tmpChunkList.begin(), tmpChunkList.end(), it->first) == tmpChunkList.end())
      deleteList.push_back(it->first);

  auto deleteEnd = deleteList.end();
  for (auto it = deleteList.begin(); it != deleteEnd; ++it)
  {
    delete _chunks[*it];
    _chunks.erase(*it);
  }

 //std::cout << "Taille map: " << _chunks.size() << std::endl;

}

void
Map::clear()
{
  _blocks.clear();
  _chunks.clear();
}

Map::blocks_type&
Map::getBlocks()
{
  return _blocks;
}

Map::chunks_type&
Map::getChunks()
{
  return _chunks;
}

const Map::blocks_type&
Map::getBlocks() const
{
  return _blocks;
}

const Map::chunks_type&
Map::getChunks() const
{
  return _chunks;
}





