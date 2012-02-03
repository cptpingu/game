#include "Architecte.hh"
#include <cstdlib>
#include <iostream>
#include "Vector3D.hh"
#include <vector>
#include <fstream>
#include "Math.h"
#include "Map.hh"

namespace
{
  void apply(const SolTriangle* deformation, SolTriangle* original)
  {

    original->_z = (original->_z + deformation->_z)/2;

  }
} //namespace

Architecte::Architecte()
{
}
//L'architecte fait les plans : les écrits dans un fichier et / ou les stock en memoire.

void
Architecte::ground(Map::triangles_type & tmp, const Vector3D& where, int size)
{
  std::vector<double> height;
  int loopSize = size * size;
  height.reserve(loopSize);
  double heightMean=0;

  for (int i = 0; i < loopSize; ++i)
  {
    height[i] = rand() % 50;
    heightMean = heightMean + height[i];
  }
  heightMean = heightMean / loopSize;
  for (int k = 0; k <= 30; ++k)
  {
    for (int i = 0; i < size - 1; ++i)
    {
      for (int j = 0; j < size - 1; ++j)
      {
        height[i + j * size] = (height[i + 1 + j * size] +
                                height[i + (j + 1) * size] +
                                height[i + 1 +( j + 1) * size] +
                                height[i + j * size]) / 4;
        if (i == size - 2)
          height[i + 1 + j * size] = height[i + j * size];

        if (j == size - 2)
          height[i + (j + 1) * size] = height[i + j * size];
      }
    }
  }

  int k = 0;
  for (int i = 0; i < size ; i++)
  {
    for(int j = 0; j < size ; j++)
    {
      if (j != size - 1)
      {
        tmp.add(new SolTriangle(i+k + where._x,
                                k * (size - 1- 2*j) + j  + where._y,
                                height[i+k + size * (k * (size - 1- 2*j) + j )] + where._z - heightMean));
        tmp.add(new SolTriangle(i + (1-k) + where._x,
                                k * (size - 1) + j - 2 * j * k + where._y,
                                height[i + (1-k) + size *(k * (size - 1- 2*j) + j )] + where._z - heightMean));
      }
      else
      {
        k= (k + 1) % 2;
        tmp.add(new SolTriangle(i + (1-k) + where._x,
                                k*(size-1) + where._y ,
                                height[i + (1-k) + size*(k*(size - 1) )] + where._z- heightMean));

        tmp.add(new SolTriangle(i+k + where._x,
                                k * (size-1) + where._y,
                                height[i+k + size *(k *(size - 1) )] + where._z - heightMean));

      }
    }
  }
}

void
Architecte::building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur)
{
  int L;
  int l;
  int H;
  l = largeur + rand()%(largeur+1);
  L = longueur + rand()%(longueur+1);
  H = hauteur+hauteur*rand()%4;


  for (int j=0;j<=H;++j)
  {for (int i=0;i<=L;++i)
    {
      tmp.add( new Block(where._x, where._y+i, where._z+j));
      tmp.add( new Block(where._x+1, where._y+i, where._z+j));
    }
  }
  for (int j=1;j<l;++j)
  {for (int i=0;i<=H;++i)
    {
      tmp.add( new Block(where._x+j, where._y, where._z+i));
      tmp.add( new Block(where._x+j, where._y+L, where._z+i));
    }

  }
}

void
Architecte::mountain(Map::triangles_type& tmp, const Vector3D& where, double peak, int size)
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
        tmp.add(new SolTriangle(i+k + where._x,
                                k*(size-1-2*j)+j + where._y,
                                height[i+k+size*(k*(size-1)+j -2*j*k)]+where._z));

        tmp.add(new SolTriangle(i + (1-k) + where._x,
                                k*(size-1-2*j)+j + where._y,
                                height[i+(1-k)+size*(k*(size-1)+j -2*j*k)] + where._z));
      }
      else
      {
        k = (k + 1) % 2;

        tmp.add(new SolTriangle(i + (1-k) + where._x,
                                k*(size-1) + where._y ,
                                height[i + (1-k) + size*(k*(size - 1) )] + where._z));

        tmp.add(new SolTriangle(i+ k + where._x,
                                k * (size-1) + where._y,
                                height[i+k + size *(k *(size - 1) )] + where._z ));


      }
    }
}

void
Architecte::mergeGround(Map::triangles_type& ground, const Map::triangles_type& deformation)
{
  auto end1 = ground.end();
  auto end2 = deformation.end();
  auto it1 = ground.begin();
  for (auto it2 = deformation.begin(); it2 != end2; ++it2)
  {

    while (it1 != end1 && (*it1)->_x != (*it2)->_x || (*it1)->_y != (*it2)->_y)
    {++it1;}
    if(it1 == end1)
    {break;}



    apply(*it2,*it1);

    ++it1;

  }
}


