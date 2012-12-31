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
Map::createBlock(const Core::Container3D<int>& where, unsigned int state)
{
  if (_blocks.find(where) != _blocks.end())
    return;

  Block::Basic* block = 0;
  //if (Core::Random::rand() % 2 == 0)
  block = new Block::Cube(where._x , where._y, where._z);
  //    else
  //      block = new Block::Triangle(where._x , where._y, where._z);
  block->init();
  _blocks.insert(blocks_type::value_type(where, block));

  if (state > 0)
  {
    auto found = _groups.find(Model::CubeType);
    if (found == _groups.end())
    {
      auto pair =  _groups.insert(groups_type::value_type(Model::CubeType, new Block::GroupBlock));
      ASSERT(pair.second);
      found = pair.first;
    }
    ASSERT_MSG(found != _groups.end(), "Error while adding block!");
    found->second->add(state, block);
  }
}

void
Map::changeBlockState(const Core::Container3D<int>& where, bool propagate)
{
  Block::NeighbourMatrix neighbours;
  Block::Basic* block = findBlock(where._x, where._y, where._z);
  fillNeighbours(where, neighbours);
  neighbours(+0, +0, +0) = block;

  const unsigned int oldState = block->getState();
  block->changeState(neighbours);
  const unsigned int state = block->getState();
  if (oldState == state)
    return;

  auto found = _groups.find(Model::CubeType);
  if (found == _groups.end())
  {
    auto pair =  _groups.insert(groups_type::value_type(Model::CubeType, new Block::GroupBlock));
    ASSERT(pair.second);
    found = pair.first;
  }
  ASSERT_MSG(found != _groups.end(), "Error while adding block!");
  found->second->remove(oldState, block);
  found->second->add(state, block);

  if (propagate)
    changeNeighbourState(where, false);
}

bool
Map::fillNeighbours(const Core::Container3D<int>& where,
                    Block::NeighbourMatrix& neighbours)
{
  const int x = where._x;
  const int y = where._y;
  const int z = where._z;

  neighbours(+0, +0, -1) = findBlock(x + 0, y + 0, z - 1);
  neighbours(+0, +1, +0) = findBlock(x + 0, y + 1, z + 0);
  neighbours(-1, +0, +0) = findBlock(x - 1, y + 0, z + 0);
  neighbours(+0, +0, +0) = 0;
  neighbours(+1, +0, +0) = findBlock(x + 1, y + 0, z + 0);
  neighbours(+0, -1, +0) = findBlock(x + 0, y - 1, z + 0);
  neighbours(+0, +0, +1) = findBlock(x + 0, y + 0, z + 1);

  if (false /* check diagonale */)
  {
    neighbours(-1, +1, -1) = findBlock(x - 1, y + 1, z - 1);
    neighbours(+0, +1, -1) = findBlock(x + 0, y + 1, z - 1);
    neighbours(+1, +1, -1) = findBlock(x + 1, y + 1, z - 1);
    neighbours(-1, +0, -1) = findBlock(x - 1, y + 0, z - 1);
    neighbours(+1, +0, -1) = findBlock(x + 1, y + 0, z - 1);
    neighbours(-1, -1, -1) = findBlock(x - 1, y - 1, z - 1);
    neighbours(+0, -1, -1) = findBlock(x + 0, y - 1, z - 1);
    neighbours(+1, -1, -1) = findBlock(x + 1, y - 1, z - 1);

    neighbours(-1, +1, +0) = findBlock(x - 1, y + 1, z + 0);
    neighbours(-1, -1, +0) = findBlock(x - 1, y - 1, z + 0);
    neighbours(+1, -1, +0) = findBlock(x + 1, y - 1, z + 0);
    neighbours(+1, +1, +0) = findBlock(x + 1, y + 1, z + 0);

    neighbours(-1, +1, +1) = findBlock(x - 1, y + 1, z + 1);
    neighbours(+0, +1, +1) = findBlock(x + 0, y + 1, z + 1);
    neighbours(+1, +1, +1) = findBlock(x + 1, y + 1, z + 1);
    neighbours(-1, +0, +1) = findBlock(x - 1, y + 0, z + 1);
    neighbours(+1, +0, +1) = findBlock(x + 1, y + 0, z + 1);
    neighbours(-1, -1, +1) = findBlock(x - 1, y - 1, z + 1);
    neighbours(+0, -1, +1) = findBlock(x + 0, y - 1, z + 1);
    neighbours(+1, -1, +1) = findBlock(x + 1, y - 1, z + 1);
  }

  return true;
}

void
Map::changeNeighbourState(const Core::Container3D<int>& where, bool propagate)
{
#define CHANGE(X, Y, Z)                                                                            \
  if (neighbours(X, Y, Z))                                                                         \
  {                                                                                                \
    changeBlockState(Core::Container3D<int>(where._x + X, where._y + Y, where._z + Z), propagate); \
  }

  Block::NeighbourMatrix neighbours;
  fillNeighbours(where, neighbours);

  CHANGE(+0, +0, -1);
  CHANGE(+0, +1, +0);
  CHANGE(-1, +0, +0);
  CHANGE(+0, +0, +0);
  CHANGE(+1, +0, +0);
  CHANGE(+0, -1, +0);
  CHANGE(+0, +0, +1);

  // Diagonals
  CHANGE(-1, +1, -1);
  CHANGE(+0, +1, -1);
  CHANGE(+1, +1, -1);
  CHANGE(-1, +0, -1);
  CHANGE(+1, +0, -1);
  CHANGE(-1, -1, -1);
  CHANGE(+0, -1, -1);
  CHANGE(+1, -1, -1);

  CHANGE(-1, +1, +0);
  CHANGE(-1, -1, +0);
  CHANGE(+1, -1, +0);
  CHANGE(+1, +1, +0);

  CHANGE(-1, +1, +1);
  CHANGE(+0, +1, +1);
  CHANGE(+1, +1, +1);
  CHANGE(-1, +0, +1);
  CHANGE(+1, +0, +1);
  CHANGE(-1, -1, +1);
  CHANGE(+0, -1, +1);
  CHANGE(+1, -1, +1);

#undef CHANGE
}

void
Map::changeAllBlockState()
{
  auto end = _blocks.end();
  for (auto it = _blocks.begin(); it != end; ++it)
    if (it->second->getState() == 0)
      changeBlockState(it->first, false);
}

void
Map::insertBlockNearBlock(const Block::Basic* who, const Block::FaceType where)
{
  if (!who)
    return;

  Core::Container3D<int> container;
  switch (where)
  {
    case Block::back:
      container = Core::Container3D<int>(who->_x, who->_y + 1, who->_z);
      break;
    case Block::front:
      container = Core::Container3D<int>(who->_x, who->_y - 1, who->_z);
      break;
    case Block::left:
      container = Core::Container3D<int>(who->_x - 1, who->_y, who->_z );
      break;
    case Block::right:
      container = Core::Container3D<int>(who->_x + 1, who->_y, who->_z );
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
  changeBlockState(container, true);
}

void
Map::eraseBlock(Block::Basic* who)
{
  if (who)
  {
    auto container = Core::Container3D<int>(who->_x, who->_y, who->_z);
    auto group = _groups.find(Model::CubeType);
    ASSERT(group != _groups.end());
    group->second->removeFromAll(who);
    delete _blocks[container];
    _blocks.erase(container);
    changeNeighbourState(container, false);
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
