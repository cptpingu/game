#include "Chunk.hh"
#include "Core/PairHash.hh"
#include "GLUtils.hh"

#include <unordered_map>
#include <tuple>
#include <SDL/SDL_image.h>

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
  const int sign = absolute < 0 ? -1 : 1;
  return absolute / SIZE + sign * 0.5;
}

void
Chunk::generateTexture(const std::string& filename) const
{
  // FIXME Possible memory leak ! (Temporary)
  // FIXME Check error ! This code doesn't check anything !!!

  SDL_Surface* vegSurface = IMG_Load("data/images/veg008.jpg");
  SDL_Surface* woodSurface = IMG_Load("data/images/wood002.jpg");
  SDL_Surface* brickSurface = IMG_Load("data/images/brick077.jpg");
  SDL_Surface* resSurface = createSurface(10 * SIZE, 10 * SIZE, vegSurface);

  SDL_LockSurface(resSurface);
  resSurface->pitch = 768;
  for (int x = 0; x < resSurface->w; ++x)
  {
    for (int y = 0; y < resSurface->h; ++y)
    {
      unsigned char* r = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 0;
      unsigned char* g = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 1;
      unsigned char* b = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 2;
      int localX = x % vegSurface->w;
      int localY = y % vegSurface->h;

      const unsigned char* localR = (static_cast<unsigned char*>(vegSurface->pixels)) +
        localX * 3 * vegSurface->w + localY * 3 + 0;
      const unsigned char* localG = (static_cast<unsigned char*>(vegSurface->pixels)) +
        localX * 3 * vegSurface->w + localY * 3 + 1;
      const unsigned char* localB = (static_cast<unsigned char*>(vegSurface->pixels)) +
        localX * 3 * vegSurface->w + localY * 3 + 2;

      *r = *localR;
      *g = *localG;
      *b = *localB;
    }
  }
  SDL_UnlockSurface(resSurface);

  SDL_SaveBMP(resSurface, filename.c_str());

  SDL_FreeSurface(resSurface);
  SDL_FreeSurface(brickSurface);
  SDL_FreeSurface(woodSurface);
  SDL_FreeSurface(vegSurface);
}
