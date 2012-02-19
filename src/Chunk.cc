#include "Chunk.hh"
#include "Core/PairHash.hh"
#include "GLUtils.hh"
#include "Architecte.hh"
#include "SDL/SavePng.hh"

#include <unordered_map>
#include <tuple>
#include <SDL/SDL_image.h>

#include <array>
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
  const int sign = absolute < 0 ? -1 : 1;
  return absolute / SIZE + sign * 0.5;
}

int
absoluteToTextureCoord(double absolute)
{
  // FIXME: bad
  return absolute - Chunk::SIZE / 2;
}

void
Chunk::generateTexture(const std::string& filename) const
{
  // FIXME Possible memory leak ! (Temporary)
  // FIXME Check error ! This code doesn't check anything !!!

  SDL_Surface* vegSurface = IMG_Load("data/images/veg008.jpg");
  SDL_Surface* woodSurface = IMG_Load("data/images/wood002.jpg");
  SDL_Surface* brickSurface = IMG_Load("data/images/brick077.jpg");
  SDL_Surface* resSurface = createSurface(TEXTURE_SIZE, TEXTURE_SIZE, vegSurface);

  const int adapterSize = TEXTURE_SIZE / SIZE;
  const int halfAdapterSize = adapterSize / 2;
  SDL_LockSurface(resSurface);
  for (int x = halfAdapterSize; x < resSurface->w; x += adapterSize)
  {
    for (int y = halfAdapterSize; y < resSurface->h; y += adapterSize)
    {
      auto it = _fast_access_chunk.find(std::make_pair(absoluteToTextureCoord((x - halfAdapterSize) / adapterSize),
                                                       absoluteToTextureCoord((y - halfAdapterSize) / adapterSize)));
      const int z = it != _fast_access_chunk.cend() ? it->second : 0;

      SDL_Surface* surface1 = 0;
      SDL_Surface* surface2 = 0;
      int coeff1 = 0;
      int coeff2 = 0;

      if (z <= 0)
      {
        coeff1 = 100;
        surface1 = vegSurface;
        surface2 = vegSurface;
      }
      else if (z <= 4)
      {
        coeff1 = ((4 - z) * 100) / 4;
        coeff2 = 100 - coeff1;
        surface1 = vegSurface;
        surface2 = brickSurface;
      }
      else if (z <= 8)
      {
        coeff1 = ((8 - z) * 100) / 8;
        coeff2 = 100 - coeff1;
        surface1 = brickSurface;
        surface2 = woodSurface;
      }
      else
      {
        coeff2 = 100;
        surface1 = woodSurface;
        surface2 = woodSurface;
      }

      const int xFrom = x - halfAdapterSize > 0 ? x - halfAdapterSize : 0;
      const int xTo = x + halfAdapterSize < resSurface->w ? x + halfAdapterSize : resSurface->w;
      const int yFrom = y - halfAdapterSize > 0 ? y - halfAdapterSize : 0;
      const int yTo = y + halfAdapterSize < resSurface->h ? y + halfAdapterSize : resSurface->h;
      for (int xAdapt = xFrom; xAdapt < xTo; ++xAdapt)
      {
        for (int yAdapt = yFrom; yAdapt < yTo; ++yAdapt)
        {
          unsigned char* r = (static_cast<unsigned char*>(resSurface->pixels)) + xAdapt * 3 * resSurface->w + yAdapt * 3 + 0;
          unsigned char* g = (static_cast<unsigned char*>(resSurface->pixels)) + xAdapt * 3 * resSurface->w + yAdapt * 3 + 1;
          unsigned char* b = (static_cast<unsigned char*>(resSurface->pixels)) + xAdapt * 3 * resSurface->w + yAdapt * 3 + 2;

          int localX = xAdapt % surface1->w;
          int localY = yAdapt % surface1->h;
          const unsigned char* localR = (static_cast<unsigned char*>(surface1->pixels)) +
            localX * 3 * surface1->w + localY * 3 + 0;
          const unsigned char* localG = (static_cast<unsigned char*>(surface1->pixels)) +
            localX * 3 * surface1->w + localY * 3 + 1;
          const unsigned char* localB = (static_cast<unsigned char*>(surface1->pixels)) +
            localX * 3 * surface1->w + localY * 3 + 2;

          int local2X = xAdapt % surface2->w;
          int local2Y = yAdapt % surface2->h;
          const unsigned char* localR2 = (static_cast<unsigned char*>(surface2->pixels)) +
            local2X * 3 * surface2->w + local2Y * 3 + 0;
          const unsigned char* localG2 = (static_cast<unsigned char*>(surface2->pixels)) +
            local2X * 3 * surface2->w + local2Y * 3 + 1;
          const unsigned char* localB2 = (static_cast<unsigned char*>(surface2->pixels)) +
            local2X * 3 * surface2->w + local2Y * 3 + 2;

          *r = (*localR * coeff1 + *localR2 * coeff2) / 200;
          *g = (*localG * coeff1 + *localG2 * coeff2) / 200;
          *b = (*localB * coeff1 + *localB2 * coeff2) / 200;

           //*r = z;
           //*g = z;
          // *b = z;
        }
      }

    }
  }

  SDL_UnlockSurface(resSurface);
  SDL_SaveBMP(resSurface, filename.c_str());

  SDL_FreeSurface(resSurface);
  SDL_FreeSurface(brickSurface);
  SDL_FreeSurface(woodSurface);
  SDL_FreeSurface(vegSurface);
}

void computeTextureCoeff(std::array<double, 3>& coeffs, unsigned char z)
{
  if (z < 60)
  {
    coeffs[0] = 1.0;
    coeffs[1] = 0.0;
    coeffs[2] = 0.0;
  }
  else if (z < 130)
  {
    coeffs[0] = 1.0 - (z - 60.0) / 70.0;
    coeffs[1] = (z - 60.0) / 70.0;
    coeffs[2] = 0.0;
  }
  else if (z < 180)
  {
    coeffs[0] = 0.0;
    coeffs[1] = 1.0;
    coeffs[2] = 0.0;
  }
  else if (z < 220)
  {
    coeffs[0] = 0.0;
    coeffs[1] = 1.0 - (z - 180.0) / 40.0;
    coeffs[2] = (z - 180.0) / 40.0;
  }
  else
  {
    coeffs[0] = 0.0;
    coeffs[1] = 0.0;
    coeffs[2] = 1.0;
  }
}

const Core::Container3D<int> getTexturePixelColor(const SDL_Surface* surface, int x, int y)
{
  const int localX = x % surface->w;
  const int localY = y % surface->h;
  const unsigned char* r = (static_cast<unsigned char*>(surface->pixels)) +
    localX * 3 * surface->w + localY * 3 + 0;
  const unsigned char* g = (static_cast<unsigned char*>(surface->pixels)) +
    localX * 3 * surface->w + localY * 3 + 1;
  const unsigned char* b = (static_cast<unsigned char*>(surface->pixels)) +
    localX * 3 * surface->w + localY * 3 + 2;

  return Core::Container3D<int>(*r, *g, *b);
}

int
Chunk::operator()(double x, double y) const
{
  auto found = _fast_access_chunk.find(fast_access_chunk_type::key_type(x, y));
  if (found == _fast_access_chunk.cend())
    assert(false && "Chunk: Index out of bound");

  return found->second;
}

void
Chunk::generateChunk()
{
  const texture_coord_type& coords = Architecte::generateGround();
  double min = coords.empty() ? 0 : coords[0];
  double max = coords.empty() ? 0 : coords[0];
  for (auto it = coords.begin(); it != coords.end(); ++it)
    if (*it > max)
      max = *it;
    else if (*it < min)
      min = *it;

  SDL_Surface* vegSurface = IMG_Load("data/images/veg008.jpg");
  SDL_Surface* brickSurface = IMG_Load("data/images/brick077.jpg");
  SDL_Surface* woodSurface = IMG_Load("data/images/wood002.jpg");
  SDL_Surface* resSurface = createSurface(TEXTURE_SIZE, TEXTURE_SIZE, vegSurface);
  std::array<double, 3> coeffs;

  SDL_LockSurface(resSurface);
  for (int x = 0; x < resSurface->w; ++x)
  {
    for (int y = 0; y < resSurface->h; ++y)
    {
      double coord = coords[x * TEXTURE_SIZE + y];
      double z = (255.0 * (coord - min)) / (max - min);
      computeTextureCoeff(coeffs, z);

      unsigned char* r = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 0;
      unsigned char* g = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 1;
      unsigned char* b = (static_cast<unsigned char*>(resSurface->pixels)) + x * 3 * resSurface->w + y * 3 + 2;

      const Core::Container3D<int> vegColor = getTexturePixelColor(vegSurface, x, y);
      const Core::Container3D<int> brickColor = getTexturePixelColor(brickSurface, x, y);
      const Core::Container3D<int> woodColor = getTexturePixelColor(woodSurface, x, y);

      *r = coeffs[0] * vegColor._x + coeffs[1] * brickColor._x + coeffs[2] * woodColor._x;
      *g = coeffs[0] * vegColor._y + coeffs[1] * brickColor._y + coeffs[2] * woodColor._y;
      *b = coeffs[0] * vegColor._z + coeffs[1] * brickColor._z + coeffs[2] * woodColor._z;

    *r = z;
    *g = z;
    *b = z;
    }
  }

  SDL_UnlockSurface(resSurface);
  SDL_SaveBMP(resSurface, "chunk_0_0.bmp");
  SDL::savePng(resSurface, "chunk_0_0.png");

  SDL_FreeSurface(resSurface);
  SDL_FreeSurface(brickSurface);
  SDL_FreeSurface(woodSurface);
  SDL_FreeSurface(vegSurface);

  createRealCoord(coords);
}

void
Chunk::createRealCoord(const texture_coord_type& coords)
{
#define ADD(X, Y)                                                       \
  add((X) - HALF, (Y) - HALF, coords[((X) * RATIO) * TEXTURE_SIZE + ((Y) * RATIO)] / (10));

  static const int RATIO = TEXTURE_SIZE / SIZE;
  static const int HALF = SIZE / 2;

  int k = 0;
  for (int i = 0; i < SIZE - 1; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      ADD(i + k, k * (SIZE - 1 - 2 * j) + j);
      ADD(i + 1 - k, k * (SIZE - 1) + j - (2 * j * k) /*k * (SIZE - 1 - 2 * j) + j*/);
    }
    k = (k + 1) % 2;
  }

  meshAllCoord();

#undef ADD
}
