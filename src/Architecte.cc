#include <iostream>
#include <cmath>

#include "Architecte.hh"
#include "Vector3D.hh"
#include "Map.hh"
#include "Random.hh"


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
      double C1 = 0;
      double C2 = 0;
      double C3 = 0;

      for (int x = 1; x < Chunk::SIZE-2 ; ++x)
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
      }
      /*std::cout << C1 << std::endl;
      std::cout << C2 << std::endl;
      std::cout << C3 << std::endl;*/

      for (int k=0;k<100;++k)
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
  //int a = Random::rand()%100;
    for (int i = 0; i < Chunk::SIZE; ++i)
      for (int j = 0; j < Chunk::SIZE; ++j)
        {
          //coords(i, j) = log(1+Random::rand()% Chunk::SIZE);
          //coords(i, j) = a;
          coords(i, j) = Random::rand()% Chunk::MAX_HEIGHT;


        }

    //Initground(coords,4);
    smoothGround(coords);

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

//Construction d'une branche...
  Chunk::Model_Point Branche(int size, int diffusionX,int diffusionY,const Chunk::Model_Point& where)
  {
      Chunk::Model_Point New(where._x + diffusionX + Random::rand()%diffusionX - diffusionX/2,
             where._y + diffusionY + Random::rand()%diffusionY - diffusionY/2,
             where._z + size + Random::rand()%size);

      /*(where._x + diffusionX + Random::rand()%diffusionX - diffusionX/2,where._y + diffusionY + Random::rand()%diffusionY-diffusionY/2,where._z + size + Random::rand()%size);*/
    return New;
  }
//Processus de branchage....
  void TreeProcess(Chunk::Model & Tree,int size,int Density,const Chunk::Model& where)
  {
      if (size <= 1)
        return;

    Chunk::Model New;

    auto end1 = where.end();

    for (auto it = where.begin(); it != end1; ++it)
        {
      int Nodes = Random::rand()%Density + 1;

      for (int i=0;i<Nodes;++i)
         New.push_back (Branche(size,size/2,size/2,(*it)));


      auto end2 = New.end();
      for (auto it = New.begin(); it != end2; ++it)
      Tree.push_back (*it);
        }

        TreeProcess(Tree, size/2 ,Density+1,New);



    }

  void drawTree(Chunk::Model & Tree)
  {
      TextureManager& textures = TextureManager::getInstance();
      glBindTexture(GL_TEXTURE_2D, textures["wood1"]);

      glPushMatrix();
      glBegin(GL_LINE_STRIP);
      auto end = Tree.end();
      for (auto it = Tree.begin(); it != end; ++it)
      {

        {
          glColor3f(1,1,1);
          glVertex3f((*it)._x,
                     (*it)._y,
                     (*it)._z);
        }
        glEnd();
       glPopMatrix();





  }

/*
//Prends une liste de coordonnées et fait des arbres à ces coordonnées...
void Forest(Chunk::chunk_coord_type TreeList,int size,int Density)

    {
          auto end = TreeList.cend();
          for (auto it = TreeList.cbegin(); it != end; ++it)
          TreeProcess(Chunk::chunk_coord_type TreeList,Chunk::chunk_coord_type New,size,Density,TreeList)

      }


    }

*/




}
  }// Architecte
