#include "Map.hh"


#include "Core/Traits.hh"
#include "Architecte.hh"

#include <fstream>
#include <algorithm>

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

  void linkBlocks(Map::blocks_type& blocks)
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
  }
} //namespace

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

  linkBlocks(_blocks);
  return true;
}

bool
Map::loadTriangles(const std::string& filename)
{
  std::ifstream file(filename.c_str());
  double x;
  double y;
  double z;

  if (!file)
    return false;

  while (file)
  {
    file >> x >> y >> z;
    _triangles.add(x, y, z);
  }

  return true;
}

namespace
{
  Chunk* loadChunk(int x, int y)
  {
    const Vector3D where((x * Chunk::SIZE) - (Chunk::SIZE / 2),
                         (y * Chunk::SIZE) - (Chunk::SIZE / 2),
                         0);
    Architecte architecte;
    Chunk* chunk = new Chunk;
    architecte.generateRandomGround(*chunk, where);
    chunk->meshAllCoord();
    // FIXME generate from file if it exists

    return chunk;
  }
} // namespace

void
Map::lazyChunkLoading(const Vector3D& position)
{
  const int x = Chunk::absoluteToChunkCoord(position._x);
  const int y = Chunk::absoluteToChunkCoord(position._y);
  std::vector<std::pair<int, int> > tmpChunkList;

#define LAZY_LOAD(X, Y)                                                 \
  {                                                                     \
    std::pair<int, int> current(x + (X), y + (Y));                      \
    tmpChunkList.push_back(current);                                    \
    if (_chunks.find(current) == _chunks.end())                         \
      _chunks.insert(chunks_type::value_type(current, loadChunk(current.first, current.second))); \
  }

  LAZY_LOAD(0, 0);

  LAZY_LOAD(-1, 0);
  LAZY_LOAD(-1, -1);
  LAZY_LOAD(0, -1);
  LAZY_LOAD(1, -1);

  LAZY_LOAD(0, 1);
  LAZY_LOAD(1, 1);
  LAZY_LOAD(1, 0);
  LAZY_LOAD(-1, 1);

#undef LAZY_LOAD

  auto end = _chunks.end();
  for (auto it =_chunks.begin(); it != end; ++it)
  {
    if (std::find(tmpChunkList.begin(), tmpChunkList.end(), it->first) == tmpChunkList.end())
    {
      delete it->second;
      _chunks.erase(it->first);
    }
  }
}

void
Map::clear()
{
  _blocks.clear();
  _triangles.clear();
  _chunks.clear();
}

Map::blocks_type&
Map::getBlocks()
{
  return _blocks;
}

Map::triangles_type&
Map::getTriangles()
{
  return _triangles;
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

const Map::triangles_type&
Map::getTriangles() const
{
  return _triangles;
}

const Map::chunks_type&
Map::getChunks() const
{
  return _chunks;
}
