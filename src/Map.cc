#include "Map.hh"

#include "Core/Traits.hh"
#include "Architecte.hh"
#include "Random.hh"
#include "Block/Cube.hh"
#include "Block/Triangle.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

Map::Map()
{
}

Map::~Map()
{
  clear();
}

void
Map::createBlock(const Core::Container3D<int>& where)
{
  if (_blocks.find(where) == _blocks.end())
  {
    Block::Basic* block = 0;
    if (Random::rand() % 2 == 0)
      block = new Block::Cube(where._x , where._y, where._z);
    else
      block = new Block::Triangle(where._x , where._y, where._z);
    _blocks.insert(blocks_type::value_type(where, block));
  }
}

void Map::InitGroundBlocks(int SIZE)
{
  Core::Container3D<int> where;

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      where._x = i;
      where._y = j;
      where._z = 0;
      createBlock(where);
    }
  }
return;

  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      where._x= i;
      where._y= j;
      where._z= 100*cos(fabs(i+j-50)*2*3.1467) + 100*sin(fabs(i+j-50)*2*3.1467);
      //where._z = 100*exp(- (sqrt((i-25)^2+(j-25)^2))/100);
      //where._z= where._z + Random::rand()%3 - 1;
      //where._z = 100/(sqrt((i-SIZE/2)*(i-SIZE/2) + (j-SIZE/2)*(j-SIZE/2)));
      createBlock(where);
    }
  }
}


void Map::insertBlockNearBlock(const Block::Basic* who, const Block::FaceType where)

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

  createBlock(container);
}


void
Map::eraseBlock(const Block::Basic* who)
{
  if (who)
  {
    auto container = Core::Container3D<int>(who->_x, who->_y, who->_z);
    delete _blocks[container];
    _blocks.erase(container);
  }
}

Block::Basic*
Map::findBlock(const Core::Container3D<int>& where) const
{
  auto found = _blocks.find(where);
  if(found == _blocks.end())
    return(0);
  return(found->second);
}

Block::Basic*
Map::findBlock(int x, int y, int z) const
{
  return findBlock(Core::Container3D<int>(x, y, z));
}

bool
Map::loadBlocks(const std::string& filename)
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
    createBlock(Core::Container3D<int>(x, y, z));
  }

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





