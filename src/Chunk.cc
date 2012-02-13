#include "Chunk.hh"
#include "Core/PairHash.hh"
#include <unordered_map>

#include <iostream>

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
  clear();
}

void
Chunk::add(double x, double y, double z)
{
  _chunk.push_back(new Coord(x, y, z));
}

void
Chunk::meshAllCoord()
{
  typedef std::unordered_multimap<std::pair<double, double>,
      Coord*,
      Core::PairHash<double, double> > map_type;
  map_type map;

  auto end = _chunk.end();
  for (auto it = _chunk.begin(); it != end; ++it)
  {
    map.insert(map_type::value_type(
                 std::make_pair((*it)->getX(), (*it)->getY()), *it));
  }

  auto mapEnd = map.end();
  for (auto it = map.begin(); it != mapEnd; ++it)
  {
    auto pairIt = map.equal_range(it->first);
    auto first = pairIt.first;
    auto second = pairIt.first;
    ++second;

    if (first == pairIt.second)
      continue;

    if (first != second)
    {
      first->second->setLink(second->second);
      second->second->setLink(first->second);
    }
  }
}

void
Chunk::clear()
{
  auto end = _chunk.end();
  for (auto it = _chunk.begin(); it != end; ++it)
    delete *it;
  _chunk.clear();
}

size_t
Chunk::size() const
{
  return _chunk.size();
}

Chunk::iterator
Chunk::begin()
{
  return _chunk.begin();
}

Chunk::iterator
Chunk::end()
{
  return _chunk.end();
}

Chunk::const_iterator
Chunk::cbegin() const
{
  return _chunk.cbegin();
}

Chunk::const_iterator
Chunk::cend() const
{
  return _chunk.cend();
}
