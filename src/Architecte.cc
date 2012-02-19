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

  void mountain(Map::triangles_type& tmp, const Vector3D& where, double peak, int size)
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

  void mergeGround(Map::triangles_type& ground, const Map::triangles_type& deformation)
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
  /*

  void NeighbourChunkgenerator(const Map::chunks_type & chunks , Chunk & Tmp , const Vector3D& where, int SIZE)
  {

  Chunk Superchunk;

  auto currentChunk = chunks.find(std::make_pair(Tmp.getX() + 1, Tmp.getY() - 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin()+Chunk::SIZE/2; it != end; ++it)
  {
      currentChunk._fast_access_chunk

  Superchunk.add(*it);
  }
  if (it->getX() == SIZE*Tmp.);


  it->getY();it->getZ();
  CurrentChunk.
  Superchunk.add()


  currentChunk = chunks.find(std::make_pair(Tmp.getX() - 1, Tmp.getY() + 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() - 1, Tmp.getY() - 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() + 1, Tmp.getY() + 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() - 1, Tmp.getY() + 0));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() + 0, Tmp.getY() - 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() + 1, Tmp.getY() + 0));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  currentChunk = chunks.find(std::make_pair(Tmp.getX() + 0, Tmp.getY() + 1));

  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
  Superchunk.add(*it);
  }

  {
  const int x = (static_cast<double>(position._x) / Chunk::SIZE) + 0.5; \
  const int y = (static_cast<double>(position._y) / Chunk::SIZE) + 0.5; \
  std::pair<int, int> current(x + (X), y + (Y));                      \
  if (_chunks.find(current) == _chunks.end())                         \
  _chunks.insert(chunks_type::value_type(current, loadChunk(current.first, current.second))); \
  }
  meshAllCoord()

  }

  void interpolateCoords(std::vector<Chunk::Coord*> destination, const std::vector<Chunk::Coord*>& source)

  {
  auto end = source.end();
  auto it2 = source.begin();
  for ( auto it1 = source.begin(); it1 != end ; ++it1)
  {
  it2 = it1+1;
  destination.push_back(new Chunk::Coord ((*it1)->getX(),(*it1)->getY(),(*it1)->getZ()));
  for (double i=1;i < Chunk::SIZE;++i)
  {
  destination.push_back(new Chunk::Coord ( ((*it1)->getX()+(*it2)->getX())* i/Chunk::SIZE
  ,((*it1)->getY()+(*it2)->getY())*i/Chunk::SIZE
  ,((*it1)->getZ()+(*it2)->getZ())*i/Chunk::SIZE
  ));

  }


  }

  }
*/

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
    //static const float step = Chunk::SIZE;

    int q = i / step;
    int bound1x = (q * step);
    int bound2x = ((q + 1) * step) - 1;
    int tex2x = bound2x + 1 < Chunk::TEXTURE_SIZE ? bound2x + 1 : Chunk::TEXTURE_SIZE - 1;

    int q2 = j / step;
    int bound1y = (q2 * step);
    int bound2y = ((q2 + 1) * step) - 1;
    int tex2y = bound2y + 1 < Chunk::TEXTURE_SIZE ? bound2y + 1 : Chunk::TEXTURE_SIZE - 1;

    int b00 = coords[bound1x + bound1y * Chunk::TEXTURE_SIZE];
    int b01 = coords[bound1x + tex2y * Chunk::TEXTURE_SIZE];
    int b10 = coords[tex2x + bound1y * Chunk::TEXTURE_SIZE];
    int b11 = coords[tex2x + tex2y * Chunk::TEXTURE_SIZE];

    int v1 = interpolate(b00, b01, bound2y - bound1y, j - bound1y);
    int v2 = interpolate(b10, b11, bound2y - bound1y, j - bound1y);
    int res = interpolate(v1, v2, bound2x - bound1x, i - bound1x);

    return res;
  }

  Chunk::texture_coord_type generateGround()
  {
    Chunk::texture_coord_type tabPoints;
    tabPoints.resize(Chunk::TEXTURE_SIZE * Chunk::TEXTURE_SIZE);

    double heightMean = 0;
    for (int i = 0; i < Chunk::TEXTURE_SIZE * Chunk::TEXTURE_SIZE; i += Chunk::SIZE)
    {
      tabPoints[i] = Random::rand() % (Chunk::SIZE * 10);
      heightMean += tabPoints[i];
    }

    heightMean /= Chunk::SIZE * Chunk::SIZE;

    for (int k = 0; k <= 10; ++k)
    {
      for (int i = 0; i < Chunk::TEXTURE_SIZE - Chunk::SIZE; i += Chunk::SIZE)
      {
        for (int j = 0; j < Chunk::TEXTURE_SIZE - Chunk::SIZE; j += Chunk::SIZE)
        {
          tabPoints[i + j * Chunk::TEXTURE_SIZE] = (tabPoints[i + Chunk::SIZE + j * Chunk::TEXTURE_SIZE] +
                                                    tabPoints[i + (j + Chunk::SIZE) * Chunk::TEXTURE_SIZE] +
                                                    tabPoints[i + Chunk::SIZE + (j + Chunk::SIZE) * Chunk::TEXTURE_SIZE] +
                                                    tabPoints[i + j * Chunk::TEXTURE_SIZE]) / 4;
          if (i == Chunk::TEXTURE_SIZE - 2*Chunk::SIZE)
            tabPoints[i + Chunk::SIZE + j * Chunk::TEXTURE_SIZE] = tabPoints[i + j * Chunk::TEXTURE_SIZE];
          if (j == Chunk::TEXTURE_SIZE - 2*Chunk::SIZE)
            tabPoints[i + (j + Chunk::SIZE) * Chunk::TEXTURE_SIZE] = tabPoints[i + j * Chunk::TEXTURE_SIZE];
        }
        tabPoints[i + (Chunk::TEXTURE_SIZE - Chunk::SIZE) * Chunk::TEXTURE_SIZE] =
            tabPoints[i + (Chunk::TEXTURE_SIZE - (2 * Chunk::SIZE)) * Chunk::TEXTURE_SIZE];
      }
      tabPoints[Chunk::TEXTURE_SIZE - Chunk::SIZE + (Chunk::TEXTURE_SIZE - Chunk::SIZE) * Chunk::TEXTURE_SIZE] =
          tabPoints[Chunk::TEXTURE_SIZE - (2 * Chunk::SIZE) + (Chunk::TEXTURE_SIZE - (2 * Chunk::SIZE)) * Chunk::TEXTURE_SIZE];
    }

    for (int i = 0; i < Chunk::TEXTURE_SIZE; ++i)
      for (int j = 0; j < Chunk::TEXTURE_SIZE; ++j)
        if (i % Chunk::SIZE != 0 || j % Chunk::SIZE != 0)
          tabPoints[i + j * Chunk::TEXTURE_SIZE] = interpolation(tabPoints, i, j, Chunk::SIZE);

    return tabPoints;
  }

  const Chunk::chunk_type& generateNeighbor(const std::pair<int, int>& Where, const Map::chunks_type& chunks)
  {
    Chunk::chunk_type coords;
    coords.resize(0); // nb points centre + nbpoints gauche + nbpoints droite
    // + nbpoints haut + nbpoints bas

      //Les points sont initialisés au hasard...
    for (int i = 0; i < Chunk::SIZE * Chunk::SIZE; ++i)
    {
      coords[i] = Random::rand() % (Chunk::SIZE * 10);
    }

        //Corrigés sur les frontières....
    auto currentChunk = chunks.find(std::make_pair(Where.first + 1, Where.second ));
     if (currentChunk != chunks.end())
    {
         fillCoords(coords,currentChunk,Chunk::SIZE-1,Chunk::SIZE-1,0,Chunk::SIZE-1,1,0);
    }

     currentChunk = chunks.find(std::make_pair(Where.first , Where.second +1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,0,Chunk::SIZE-1,Chunk::SIZE-1,Chunk::SIZE-1,0,1);
     }

     currentChunk = chunks.find(std::make_pair(Where.first+1 , Where.second +1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,Chunk::SIZE-1,Chunk::SIZE-1,Chunk::SIZE-1,Chunk::SIZE-1,1,1);
     }

     currentChunk = chunks.find(std::make_pair(Where.first-1 , Where.second ));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,0,0,0,Chunk::SIZE-1,-1,0);
     }

     currentChunk = chunks.find(std::make_pair(Where.first-1 , Where.second -1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,0,0,0,0,-1,-1);
     }

     currentChunk = chunks.find(std::make_pair(Where.first , Where.second -1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,0,Chunk::SIZE-1,0,0,0,-1);
     }

     currentChunk = chunks.find(std::make_pair(Where.first+1 , Where.second -1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,Chunk::SIZE-1,Chunk::SIZE-1,0,0,1,-1);
     }

     currentChunk = chunks.find(std::make_pair(Where.first-1 , Where.second +1));
     if (currentChunk != chunks.end())
     {
        fillCoords(coords,currentChunk,0,0,Chunk::SIZE-1,Chunk::SIZE-1,-1,1);
     }







    // FIXME
    // Ajout taille haut (si non existant, on met des 0 ou de l'alea)
    // ...etc
    // Ajout taille bas (si non existant, on met des 0 ou de l'alea)

    // Remplissage aléatoire centre.
    // Retourne la grande grille.


     //Retourne donc une liste valide de coord pour un chunk , chunk::size*chunk::size !
    return coords;
  }

void fillCoords(Chunk::chunk_type& coords,Chunk& currentChunk,int Xfrom,int Xto,int Yfrom,int Yto,int PosX,int PosY)
  {
      for (int y = Yfrom; y< Yto;++y)
      for (int i = Xfrom; i< Xto;++i)
      {
      {
              coords[i+y*Chunk::SIZE] = currentChunk(PosX*(Chunk::SIZE-1) - PosX*i + (1-PosX)*i,
                                                     PosY*(Chunk::SIZE-1)- PosY*y + (1-PosY)*y);
      }
      }
  }

  void generateGround(Chunk::chunk_type& coords, int size)
  {
   for (int k = 0;k<20;++k)
   {
    for (int x=0;x<size-1;++x)
    {

       for (int y=0;y<size-1;++y)
       {
           coords[x + size*y] = (coords[x + size*y] +
                                coords[x+1 + size*y]+
                                coords[x+1 + size*(y+1)]+
                                coords[x + size*(y+1)])/4;
       }

   }
 //Gére les problémes de frontière de l'algo
  for (int x=0;x<size-1;++x)
    { coords[x + size*(size-1)] = (coords[x + size*(size-1)]+coords[x + size*(size-2)])/2;
      coords[size-1 + size*x] = (coords[size-1 + size*x]+coords[size-2 + size*x])/2;}
    }

  }

    // size est nécessaire, puisque tu dois connaitre la taille du coté du carré.
    // Agit sur les Z pour lisser.

    // PS: dans chunk.cc, la méthode extractCoords, se chargera de récupérer le centre
    // de cette grande grille.


  const Chunk::texture_coord_type&
  extractCoords(const Chunk::chunk_type& coords, int size, int borderSize)
  {
    Chunk::texture_coord_type extracted;
    extracted.resize(0); // Nb points dans la grille du milieu * Chunk::SIZE.

    // Extraie la grille du milieu.
    // Récupère tout de (0 + borderSize, 0 + borderSize) à (size - borderSize, size - borderSize)
    return extracted;
  }

  // Enfin, generateChunk prendra en argument un const Chunk::texture_coord_type&

} // Architecte
