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

  void linkBlocks(Map::blocks_type& blocks)
  {
    auto end = blocks.end();
    for (auto current = blocks.begin(); current != (end - 1); ++current)
    {
      for (auto it = current + 1; it != end; ++it)
      {
        if (((*it)->_x + 1) == (*current)->_x)
        {
          (*current)->_right = *it;
          (*it)->_left = *current;
        }
        else if (((*it)->_x - 1) == (*current)->_x)
        {
          (*current)->_left = *it;
          (*it)->_right = *current;
        }

        if (((*it)->_y + 1) == (*current)->_y)
        {
          (*current)->_up = *it;
          (*it)->_down = *current;
        }
        else if (((*it)->_y - 1) == (*current)->_y)
        {
          (*current)->_down = *it;
          (*it)->_up = *current;
        }

        if (((*it)->_z + 1) == (*current)->_z)
        {
          (*current)->_front = *it;
          (*it)->_back = *current;
        }
        else if (((*it)->_z - 1) == (*current)->_z)
        {
          (*current)->_back = *it;
          (*it)->_front = *current;
        }
      }
    }
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
