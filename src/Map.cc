#include "Map.hh"
#include <fstream>

namespace
{
  template <typename T>
  bool loadFromFile(const std::string& filename, T& collection)
  {
    std::ifstream file(filename.c_str());
    typename T::type::type x;
    typename T::type::type y;
    typename T::type::type z;

    if (!file)
      return false;

    while (file)
    {
      file >> x >> y >> z;
      collection.add(new typename T::type(x, y, z));
    }

    return true;
  }

  void checkAndLinks(const Map::temp_map_type& map, Block* block)
  {
#define LINK(X,Y,Z,ASSIGN) \
    {\
  auto found = map.find(Core::Container3D<int>(block->_x + X, block->_y + Y, block->_z + Z)); \
  if (found != map.end())\
  block->ASSIGN = found->second;\
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
  return loadFromFile(filename, _triangles);
}

void
Map::clear()
{
  _blocks.clear();
  _triangles.clear();
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
