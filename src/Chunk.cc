#include "Chunk.hh"

#include <tuple>
#include <fstream>
#include <sstream>

Chunk::Chunk(int x, int y)
    : _x(x), _y(y)
{
  std::ostringstream buff;
  buff << "data/map/chunk_" << x << "_" << y << ".map";
  _filename = buff.str();
}

Chunk::~Chunk()
{
  clear();
}

void
Chunk::add(double x, double y, double z)
{
  _chunk.push_back(new Coord(x, y, z));
  _fast_access_chunk.insert(fast_access_chunk_type::value_type(std::make_pair(x, y), z));
}

void
Chunk::meshAllCoord()
{
  typedef std::pair<double, double> pair_type;
  typedef Core::PairHash<double, double> hash_type;
  typedef std::unordered_multimap<pair_type, Coord*, hash_type> map_type;
  map_type map;

  auto end = _chunk.end();
  for (auto it = _chunk.begin(); it != end; ++it)
    map.insert(map_type::value_type(std::make_pair((*it)->getX(), (*it)->getY()), *it));

  auto mapEnd = map.end();
  for (auto it = map.begin(); it != mapEnd; ++it)
  {
    map_type::iterator first;
    map_type::iterator tmpEnd;
    std::tie(first, tmpEnd) = map.equal_range(it->first);
    if (first == tmpEnd)
      continue;

    map_type::iterator second = first;
    ++second;
    if (second != tmpEnd && first != second)
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

int
Chunk::absoluteToChunkCoord(double absolute)
{
  //const int sign = absolute < 0 ? -1 : 1;

  return absolute / (Chunk::SIZE-1);// + sign * 0.5;
}

int
absoluteToTextureCoord(double absolute)
{
  return absolute - Chunk::SIZE / 2;
}

double
Chunk::operator()(double x, double y) const
{
  auto found = _fast_access_chunk.find(fast_access_chunk_type::key_type(x, y));
  if (found == _fast_access_chunk.cend())
    assert(false && "Chunk: Index out of bound");

  return found->second;
}

Chunk::Coord*
Chunk::getCoord(double x, double y, double z) const
{
  auto end = _chunk.cend();
  for (auto it = _chunk.cbegin(); it != end; ++it)
    if ((*it)->getX() == x && (*it)->getY() == y && (*it)->getZ() == z)
      return *it;

  return 0;
}

const Chunk::chunk_mesh_type&
Chunk::getCoords() const
{
  return _chunk;
}

Chunk::chunk_mesh_type&
Chunk::getCoords()
{
  return _chunk;
}

void
Chunk::createRealCoord(const chunk_coord_type& coords)
{
  int k = 0;
  for (int i = 0; i < SIZE - 1; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      const int x1 = i + k;
      const int y1 = k * (SIZE - 1 - 2 * j) + j;
      add(x1, y1, coords(x1, y1));

      const int x2 = i + 1 - k;
      const int y2 = k * (SIZE - 1) + j - (2 * j * k);
      add(x2, y2, coords(x2, y2));
    }
    k = (k + 1) % 2;
  }

  meshAllCoord();
}

bool
Chunk::saveToFile(const chunk_coord_type& coords) const
{
  assert(coords.size() == SIZE * SIZE && "Number of points is incorrect!");
  std::ofstream file(_filename.c_str(), std::ios::binary);
  if (!file)
    return false;

  int i = 0;
  double* v = new double[SIZE * SIZE];
  for (int x = 0; x < SIZE; ++x)
    for (int y = 0; y < SIZE; ++y)
      v[i++] = coords(x, y);

  file.write(reinterpret_cast<const char*>(v), SIZE * SIZE * sizeof(double));
  delete[] v;

  return true;
}

bool
Chunk::loadFromFile()
{
  std::ifstream file(_filename.c_str(), std::ios::binary);
  if (!file)
    return false;

  double* v = new double[SIZE * SIZE];
  file.read(reinterpret_cast<char*>(v), SIZE * SIZE * sizeof(double));

  int i = 0;
  chunk_coord_type coords;
  for (int x = 0; x < SIZE; ++x)
    for (int y = 0; y < SIZE; ++y)
      coords(x, y) = v[i++];
  delete[] v;

  createRealCoord(coords);

  return true;
}


