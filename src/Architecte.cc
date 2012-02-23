#include <iostream>
#include <cmath>

#include "Architecte.hh"
#include "Vector3D.hh"
#include "Map.hh"
#include "Random.hh"

namespace Architecte
{
  namespace
  {
    void apply(Chunk::Coord* original, const Chunk::Coord* deformation)
    {
      original->setZ((original->getZ() + deformation->getZ()) / 2);
    }
  } //namespace

  void generateRandomGround(Chunk& tmp, const Vector3D& where)
  {
    std::vector<double> height;
    int loopSize = Chunk::SIZE * Chunk::SIZE;
    height.reserve(loopSize);
    double heightMean=0;

    for (int i = 0; i < loopSize; ++i)
    {
      height[i] = rand() % Chunk::SIZE;
      heightMean = heightMean + height[i];
    }
    heightMean = heightMean / loopSize;
    for (int k = 0; k <= 30; ++k)
    {
      for (int i = 0; i < Chunk::SIZE - 1; ++i)
      {
        for (int j = 0; j < Chunk::SIZE - 1; ++j)
        {
          height[i + j * Chunk::SIZE] = (height[i + 1 + j * Chunk::SIZE] +
                                         height[i + (j + 1) * Chunk::SIZE] +
                                         height[i + 1 +( j + 1) * Chunk::SIZE] +
                                         height[i + j * Chunk::SIZE]) / 4;
          if (i == Chunk::SIZE - 2)
            height[i + 1 + j * Chunk::SIZE] = height[i + j * Chunk::SIZE];

          if (j == Chunk::SIZE - 2)
            height[i + (j + 1) * Chunk::SIZE] = height[i + j * Chunk::SIZE];
        }
      }
    }

    int k = 0;
    for (int i = 0; i < Chunk::SIZE ; i++)
    {
      for(int j = 0; j < Chunk::SIZE ; j++)
      {
        if (j != Chunk::SIZE - 1)
        {
          tmp.add(i+k + where._x,
                  k * (Chunk::SIZE - 1- 2*j) + j  + where._y,
                  height[i+k +Chunk::SIZE * (k * (Chunk::SIZE - 1- 2*j) + j )] + where._z - heightMean);
          tmp.add(i + (1-k) + where._x,
                  k * (Chunk::SIZE - 1) + j - 2 * j * k + where._y,
                  height[i + (1-k) + Chunk::SIZE*(k * (Chunk::SIZE - 1- 2*j) + j )] + where._z - heightMean);
        }
        else
        {
          k= (k + 1) % 2;
          tmp.add(i + (1-k) + where._x,
                  k*(Chunk::SIZE-1) + where._y ,
                  height[i + (1-k) + Chunk::SIZE*(k*(Chunk::SIZE - 1) )] + where._z- heightMean);

          tmp.add(i+k + where._x,
                  k * (Chunk::SIZE-1) + where._y,
                  height[i+k + Chunk::SIZE *(k *(Chunk::SIZE - 1) )] + where._z - heightMean);
        }
      }
    }
  }

  void building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur)
  {
    int L;
    int l;
    int H;
    l = largeur + rand()%(largeur+1);
    L = longueur + rand()%(longueur+1);
    H = hauteur+hauteur*rand()%4;


    for (int j=0;j<=H;++j)
    {
      for (int i=0;i<=L;++i)
      {
        tmp.add(new Block(where._x, where._y+i, where._z+j));
        tmp.add(new Block(where._x+1, where._y+i, where._z+j));
      }
    }
    for (int j=1;j<l;++j)
    {
      for (int i=0;i<=H;++i)
      {
        tmp.add(new Block(where._x+j, where._y, where._z+i));
        tmp.add(new Block(where._x+j, where._y+L, where._z+i));
      }

    }
  }

  void mountain(Chunk& tmp, const Vector3D& where, double peak, int size)
  {
    std::vector<double> height;
    int loopSize = size * size;
    height.reserve(loopSize);

    for (int k = 0; k <= 20; ++k)
      for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
          height[i + j * size] = peak * exp(-((i - size / 2) * (i - size / 2) + (j - size / 2) * (j - size / 2)));

    for (int k = 0; k <= 5; ++k)
      for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - 1; ++j)
          height[i + j * size] = (height[i + 1 + j * size] + height[i + (j + 1) * size] + height[i + 1 + (j + 1)  *size] + height[i + j * size]) / 4;

    int k = 0;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
      {
        if ( j != size - 1)
        {
          tmp.add(i+k + where._x,
                  k*(size-1-2*j)+j + where._y,
                  height[i+k+size*(k*(size-1)+j -2*j*k)]+where._z);

          tmp.add(i + (1-k) + where._x,
                  k*(size-1-2*j)+j + where._y,
                  height[i+(1-k)+size*(k*(size-1)+j -2*j*k)] + where._z);
        }
        else
        {
          k = (k + 1) % 2;

          tmp.add(i + (1-k) + where._x,
                  k*(size-1) + where._y ,
                  height[i + (1-k) + size*(k*(size - 1) )] + where._z);

          tmp.add(i+ k + where._x,
                  k * (size-1) + where._y,
                  height[i+k + size *(k *(size - 1) )] + where._z );


        }
      }
  }

  void mergeGround(Chunk& ground, const Chunk& deformation)
  {
    auto end1 = ground.end();
    auto end2 = deformation.cend();
    auto it1 = ground.begin();
    for (auto it2 = deformation.cbegin(); it2 != end2; ++it2)
    {
      while (it1 != end1 && ((*it1)->getX() != (*it2)->getX() || (*it1)->getY() != (*it2)->getY()))
        ++it1;
      if (it1 == end1)
        break;
      apply(*it1, *it2);
      ++it1;
    }
  }

  int interpolate(int y1, int y2, int n, int delta)
  {
    if (n != 0)
      return y1 + delta * (y2 - y1) / n;

    return y1;
  }

  //int interpolate(int y1, int y2, int n, int delta)
  //{
  //  if (n == 0)
  //    return y1;

  //  if (n == 1)
  //    return y2;

  //  float a = static_cast<float>(delta) / n;
  //  float v1 = 3 * pow(1 - a, 2) - 2 * pow(1 - a,3);
  //  float v2 = 3 * pow(a, 2) - 2 * pow(a, 3);

  //  return y1 * v1 + y2 * v2;
  //}

  int interpolation(const Chunk::texture_coord_type& coords, int i, int j, float step)
  {
    const int q = i / step;
    const int bound1x = (q * step);
    const int bound2x = (q + 1) * step;
    //const int tex2x = bound2x < Chunk::TEXTURE_SIZE ? bound2x : Chunk::TEXTURE_SIZE - 1;
    const int tex2x = bound2x;

    const int q2 = j / step;
    const int bound1y = (q2 * step);
    const int bound2y = (q2 + 1) * step;
    //const int tex2y = bound2y < Chunk::TEXTURE_SIZE ? bound2y : Chunk::TEXTURE_SIZE - 1;
    const int tex2y = bound2y;

    const int b00 = coords(bound1x, bound1y);
    const int b01 = coords(bound1x, tex2y);
    const int b10 = coords(tex2x, bound1y);
    const int b11 = coords(tex2x, tex2y);

    const int v1 = interpolate(b00, b01, bound2y - bound1y, j - bound1y);
    const int v2 = interpolate(b10, b11, bound2y - bound1y, j - bound1y);
    const int res = interpolate(v1, v2, bound2x - bound1x, i - bound1x);

    return res;
  }
  //Lisse le sol sur un chunk ou autre chose, pensée pour les chunks faire gaffe si utilisé pour autre chose
  void smoothGround(Chunk::chunk_coord_type& coords)
  {
    for (int k = 0; k < 20; ++k)
    {
      for (int x = 1; x < Chunk::SIZE - 1; ++x)
      {
        for (int y = 1; y < Chunk::SIZE - 1; ++y)
        {
          coords(x, y) = (coords(x, y) +
                          coords(x + 1, y) +
                          coords(x + 1, y + 1) +
                          coords(x + 1, y - 1) +
                          coords(x - 1, y) +
                          coords(x - 1, y + 1) +
                          coords(x - 1, y - 1) +
                          coords(x, y + 1) +
                          coords(x, y - 1)) / 9;

        }
      }

      //Gére les problémes de frontière de l'algo
     for (int x = 0; x < Chunk::SIZE ; ++x)
      {
        coords(x,0) = (coords(x, 0) + coords(x,1)) / 2;
        coords(0,x) = (coords(0, x) + coords(1,x)) / 2;
        coords(x, Chunk::SIZE- 1) = (coords(x, Chunk::SIZE - 1) + coords(x, Chunk::SIZE - 2)) / 2;
        coords(Chunk::SIZE- 1, x) = (coords(Chunk::SIZE - 1, x) + coords(Chunk::SIZE - 2, x)) / 2;
      }
    }
  }

  //Permet de copier une zone d'un chunk dans une liste de points (un autre chunk en gros,mais pas forcement).
  void fillCoords(Chunk::chunk_coord_type& coords, int whereX, int whereY,
                  Chunk& neighborChunk, int fromX,int toX,int fromY, int toY)
  {
    assert(whereX + (toX - fromX) <= Chunk::SIZE && "X out of bound");
    assert(whereY + (toY - fromY) <= Chunk::SIZE && "Y out of bound");


    int posX = whereX;
    for (int x = fromX; x < toX; ++x, ++posX)
    {
      int posY = whereY;
      for (int y = fromY; y < toY; ++y, ++posY)
        {coords(posX, posY) = neighborChunk(x, y);
      }
    }
  }

  void initChunk(Chunk::chunk_coord_type& coords, const std::pair<int, int>& where, const Map::chunks_type& chunks)
  {
    for (int i = 0; i < Chunk::SIZE; ++i)
      for (int j = 0; j < Chunk::SIZE; ++j)
        coords(i, j) = Random::rand() % 255;

    // Left top corner ?
    smoothGround(coords);
    // Top


    auto neighborChunk = chunks.find(std::make_pair(where.first, where.second + 1));
    if (neighborChunk != chunks.end())
      fillCoords(coords, 0,Chunk::SIZE-1, *neighborChunk->second, 0, Chunk::SIZE, 0, 1);

    // Right top corner ?

    // Left
    neighborChunk = chunks.find(std::make_pair(where.first - 1, where.second));
    if (neighborChunk != chunks.end())
      fillCoords(coords, 0, 0, *neighborChunk->second, Chunk::SIZE - 1, Chunk::SIZE, 0, Chunk::SIZE);

    // Right
    neighborChunk = chunks.find(std::make_pair(where.first + 1, where.second));
    if (neighborChunk != chunks.end())
      fillCoords(coords, Chunk::SIZE - 1, 0, *neighborChunk->second, 0, 1, 0, Chunk::SIZE);

    // Left bottom corner ?

    // Bottom
    neighborChunk = chunks.find(std::make_pair(where.first, where.second - 1));
    if (neighborChunk != chunks.end())    
      fillCoords(coords, 0, Chunk::SIZE - 1, *neighborChunk->second, 0, Chunk::SIZE, Chunk::SIZE-1,Chunk::SIZE);

    // Right bottom corner ?
  }



  void extractCoords(Chunk::texture_coord_type& extracted, const Chunk::chunk_coord_type& coords)
  {
    for (int i = 0; i < Chunk::SIZE; ++i)
      for (int j = 0; j < Chunk::SIZE; ++j)
        extracted(i * Chunk::RATIO, j * Chunk::RATIO) = coords(i, j);

    for (int i = 0; i < Chunk::TEXTURE_SIZE - 1; ++i)
      for (int j = 0; j < Chunk::TEXTURE_SIZE - 1; ++j)
        if (i % Chunk::RATIO != 0 || j % Chunk::RATIO != 0)
          extracted(i, j) = interpolation(extracted, i, j, Chunk::RATIO);
  }
} // Architecte
