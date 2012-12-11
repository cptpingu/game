#include <iostream>
#include <cmath>

#include "Architecte.hh"
#include "Core/Vector3D.hh"
#include "Map.hh"
#include "Core/Random.hh"
#include "Core/Assert.hh"

#include "TextureManager.hh"
#include "Opengl.hh"

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

  //Lisse le sol sur un chunk ou autre chose, pensée pour les chunks faire gaffe si utilisé pour autre chose

  void borderSmooth(Chunk::chunk_coord_type& coords)
  {

    //C1 = C1 + fabs(coords(x+1,y)-coords(x,y));
    //C2 = C2 + fabs(coords(x,y+1)-coords(x,y));
    //C1/Chunk::SIZE*size;
    //C2/Chunk::SIZE*size;

    //double size = Chunk::SIZE -1;
    double C1 = 1;
    double C2 = 1;
    double C3 = 1;

    /*for (int x = 1; x < Chunk::SIZE-2 ; ++x)
      {
        for (int y = 1; y < Chunk::SIZE-2 ; ++y)
        {
            if (fabs(coords(x+1,y)-coords(x,y))>C1)
                {
                C1 = fabs(coords(x+1,y)-coords(x,y));
                }

            if (fabs(coords(x,y+1)-coords(x,y))>C2)
                {
                C2 = fabs(coords(x,y+1)-coords(x,y));
                }
            if (fabs(coords(x+1,y+1)-coords(x,y))>C3)
                {
                C3 = fabs(coords(x,y+1)-coords(x,y));
                }


        }
      }*/
    /*std::cout << C1 << std::endl;
      std::cout << C2 << std::endl;
      std::cout << C3 << std::endl;*/

    for (int k=0;k<50;++k)
    {
      for (int x = 1; x < Chunk::SIZE-1 ; ++x)
      {
        for (int y = 1; y < Chunk::SIZE-1 ; ++y)
        {

          coords(x,y) = (coords(x,y) +

                         coords(x+1,y+1)*(fabs(coords(x,y)-coords(x+1,y+1)) > C3)+
                         coords(x-1,y+1)*(fabs(coords(x,y)-coords(x-1,y+1)) > C3)+
                         coords(x-1,y-1)*(fabs(coords(x,y)-coords(x-1,y-1)) > C3)+
                         coords(x+1,y-1)*(fabs(coords(x,y)-coords(x+1,y-1)) > C3)+
                         coords(x+1,y)*(fabs(coords(x,y)-coords(x+1,y)) > C1)+
                         coords(x,y+1)*(fabs(coords(x,y)-coords(x,y+1)) > C2)+
                         coords(x-1,y)*(fabs(coords(x,y)-coords(x-1,y)) > C1)+
                         coords(x,y-1)*(fabs(coords(x,y)-coords(x,y-1)) > C2))/
              ( (fabs(coords(x,y)-coords(x+1,y)) > C1)+
                (fabs(coords(x,y)-coords(x,y+1)) > C2)+
                (fabs(coords(x,y)-coords(x-1,y)) > C1)+
                (fabs(coords(x,y)-coords(x,y-1)) > C2)+
                (fabs(coords(x,y)-coords(x+1,y+1)) > C3)+
                (fabs(coords(x,y)-coords(x-1,y+1)) > C3)+
                (fabs(coords(x,y)-coords(x-1,y-1)) > C3)+
                (fabs(coords(x,y)-coords(x+1,y-1)) > C3)+
                1
                );
          /*coords(y,x) = (coords(y,x) +
                     coords(y+1,x)*(fabs(coords(y,x)-coords(y+1,x)) > C1)+
                     coords(y,x+1)*(fabs(coords(y,x)-coords(y,x+1)) > C2)+
                     coords(y-1,x)*(fabs(coords(y,x)-coords(y-1,x)) > C1)+
                     coords(y,x-1)*(fabs(coords(y,x)-coords(y,x-1)) > C2))/
                     ( (fabs(coords(y,x)-coords(y+1,x)) > C1)+
                        (fabs(coords(y,x)-coords(y,x+1)) > C2)+
                        (fabs(coords(y,x)-coords(y-1,x)) > C1)+
                        (fabs(coords(y,x)-coords(y,x-1)) > C2)+
                         1
                        );*/

        }
      }


    }

  }

  double Norm(Core::Vector3D where,int type)
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
      norm = sqrt(x*x + y*y + z*z);
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

  void smoothGround(Chunk::chunk_coord_type& coords)
  {
    for (int k = 0; k < 10; ++k)
    {
      for (int x = 1; x < Chunk::SIZE-1 ; ++x)
      {
        for (int y = 1; y < Chunk::SIZE-1 ; ++y)
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
    ASSERT_MSG(whereX + (toX - fromX) <= Chunk::SIZE, "X out of bound");
    ASSERT_MSG(whereY + (toY - fromY) <= Chunk::SIZE, "Y out of bound");

    int posX = whereX;
    for (int x = fromX; x < toX; ++x, ++posX)
    {
      int posY = whereY;
      for (int y = fromY; y < toY; ++y, ++posY)
        coords(posX, posY) = neighborChunk(x, y);
    }
  }

  void Initground(Chunk::chunk_coord_type&,int)
  {
    /*  int subg = (Chunk::SIZE-1)/Quality;
      for (int i = 0; i < Quality; ++i)
        for (int j = 0; j < Quality; ++j)
            coords(i * subg, j * subg) = Random::rand()%Chunk::MAX_HEIGHT;

      for (int i = 0; i < Chunk::SIZE; ++i)
        for (int j = 0; j < Chunk::SIZE; ++j)
          if (i % subg != 0 || j % subg != 0)
            coords(i,j) = interpolation(coords, i, j, subg);*/
  }
} // Architecte
