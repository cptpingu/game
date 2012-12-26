#include "Map.hh"

#include "Core/Traits.hh"
#include "Architecte.hh"
#include "Core/Random.hh"
#include "Core/Assert.hh"
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
  static int temp = 63 - 6;

  if (_blocks.find(where) == _blocks.end())
  {
    Block::Basic* block = 0;
   //if (Core::Random::rand() % 2 == 0)
      block = new Block::Cube(where._x , where._y, where._z);
//    else
//      block = new Block::Triangle(where._x , where._y, where._z);
      block->init();
      _blocks.insert(blocks_type::value_type(where, block));
      auto found = _groups.find(Model::CubeType);
      if (found == _groups.end())
      {
        auto pair =  _groups.insert(groups_type::value_type(Model::CubeType, new Block::GroupBlock));
        ASSERT(pair.second);
        found = pair.first;
      }
      ASSERT_MSG(found != _groups.end(), "Error while adding block!");
      found->second->add(temp++, block);
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
      container = Core::Container3D<int>(who->_x , who->_y + 1, who->_z);
      break;
    case Block::front:
      container = Core::Container3D<int>(who->_x , who->_y - 1, who->_z);
      break;
    case Block::left:
      container = Core::Container3D<int>(who->_x - 1 , who->_y, who->_z );
      break;
    case Block::right:
      container = Core::Container3D<int>(who->_x + 1 , who->_y, who->_z );
      break;
    case Block::up:
      container = Core::Container3D<int>(who->_x, who->_y, who->_z + 1);
      break;
    case Block::down:
      container = Core::Container3D<int>(who->_x, who->_y, who->_z - 1);
      break;
    default:
      ASSERT_MSG(false, "Bad face");
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

void
Map::clear()
{
  _blocks.clear();
  auto end = _groups.cend();
  for (auto it = _groups.cbegin(); it != end; ++it)
    delete it->second;
  _groups.clear();
}

Map::blocks_type&
Map::getBlocks()
{
  return _blocks;
}

const Map::blocks_type&
Map::getBlocks() const
{
  return _blocks;
}

const Map::groups_type&
Map::getGroups() const
{
  return _groups;
}



