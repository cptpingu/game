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
  int interpolation(const Chunk::chunk_coord_type& coords, int i, int j, float step)
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

  void borderSmooth(Chunk::chunk_coord_type& coords)
  {
      for (int x = 1; x < Chunk::SIZE-1 ; ++x)
      {
        for (int y = 1; y < Chunk::SIZE-1 ; ++y)
        {

            coords(x,y) = (coords(x,y) +
                           coords(x,0)*(Chunk::SIZE - 1 -y)/(Chunk::SIZE - 1) +
                           coords(0,y)*(Chunk::SIZE - 1 -x)/(Chunk::SIZE - 1) +
                           coords(x,Chunk::SIZE - 1)*(y/(Chunk::SIZE - 1)) +
                           coords(Chunk::SIZE - 1,y)*(x/(Chunk::SIZE - 1)))/3;


  }
  }
  }



  double Norm(Vector3D where,int type)
  {
      double norm;
      if (type==2)
      {
      norm = where._x*where._x + where._y*where._y + where._z*where._z;
      }

      if (type==1)
      {
      norm  = fabs(where._x) + fabs(where._y) + fabs(where._z);
      }

      /*if (type==0)
      {
      norm  = Max(Max(fabs(where._x),fabs(where._y)),fabs(where._z));
      }*/
      if (type != 1 && type != 0 && type != 2)
      {
          std::cout << "Incorrect call of Norm , zero value will be return as Norm" << std::endl;
          return 0;
      }

  return norm;
  }



  double Norm(double x,double y,double z,int type)
  {
      double norm;
      if (type==2)
      {
      norm = x*x + y*y + z*z;
      }

      if (type==1)
      {
      norm  = fabs(x) + fabs(y) + fabs(z);
      }

      /*if (type==0)
      {
      norm  = max(max(fabs(x),fabs(y)),fabs(z));
      }*/
      if (type != 1 && type != 0 && type != 2)
      {
          std::cout << "Incorrect call of Norm , zero value will be return as Norm" << std::endl;
          return 0;
      }

  return norm;
  }



  void Initground(Chunk::chunk_coord_type& coords,int Quality)
  {
      int subg = Chunk::SIZE/Quality;
    for (int i = 0; i < Quality; ++i)
      for (int j = 0; j < Quality; ++j)
          coords(i * subg, j * subg) = Random::rand()%Chunk::MAX_HEIGHT;

    for (int i = 0; i < Chunk::SIZE-1; ++i)
      for (int j = 0; j < Chunk::SIZE-1; ++j)
        if (i % subg != 0 || j % subg != 0)
          coords(i,j) = interpolation(coords, i, j, subg);
  }


  void smoothGround(Chunk::chunk_coord_type& coords)
  {
    for (int k = 0; k < 10; ++k)
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
                          coords(x, y - 1) ) / 9;
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
        coords(posX, posY) = neighborChunk(x, y);
    }
  }

  void initChunk(Chunk::chunk_coord_type& coords, const std::pair<int, int>& where, const Map::chunks_type& chunks)
  {
    /*int sign = 0;
    int diff = 0;
    for (int i = 0; i < Chunk::SIZE; ++i)
      for (int j = 0; j < Chunk::SIZE; ++j)
        {//coords(i, j) = Random::rand()% Chunk::MAX_HEIGHT;
          sign = Random::rand()%2;
          diff = Random::rand()% Chunk::MAX_HEIGHT;
          coords(i, j) = (sign)*(diff)
                  - (1 - sign)*(diff);

        }
*/
    Initground(coords,4);
    //smoothGround(coords);

    // Top
    auto neighborChunk = chunks.find(std::make_pair(where.first, where.second + 1));
    if (neighborChunk != chunks.end())
      fillCoords(coords, 0, Chunk::SIZE-1, *neighborChunk->second, 0, Chunk::SIZE, 0, 1);

    // Left
    neighborChunk = chunks.find(std::make_pair(where.first - 1, where.second));
    if (neighborChunk != chunks.end())
      fillCoords(coords, 0, 0, *neighborChunk->second, Chunk::SIZE - 1, Chunk::SIZE, 0, Chunk::SIZE);

    // Right
    neighborChunk = chunks.find(std::make_pair(where.first + 1, where.second));
    if (neighborChunk != chunks.end())
      fillCoords(coords, Chunk::SIZE - 1, 0, *neighborChunk->second, 0, 1, 0, Chunk::SIZE);

    // Bottom
    neighborChunk = chunks.find(std::make_pair(where.first, where.second - 1));
    if (neighborChunk != chunks.end())
      fillCoords(coords, 0, Chunk::SIZE - 1, *neighborChunk->second, 0, Chunk::SIZE, Chunk::SIZE-1,Chunk::SIZE);

    borderSmooth(coords);
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
