#include <iostream>
#include <cmath>

#include "Architecte.hh"
#include "Vector3D.hh"
#include "Map.hh"
#include "Random.hh"

namespace
{
  void apply(Chunk::Coord* original, const Chunk::Coord* deformation)
  {
    original->setZ((original->getZ() + deformation->getZ()) / 2);
  }
} //namespace

Architecte::Architecte()
{
}
//L'architecte fait les plans : les écrits dans un fichier et / ou les stock en memoire.

void
Architecte::generateRandomGround(Chunk& tmp, const Vector3D& where)
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

void
Architecte::mergeGround(Map::triangles_type& ground, const Map::triangles_type& deformation)
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
  Architecte::NeighbourChunkgenerator(const Map::chunks_type & chunks , Chunk & Tmp , const Vector3D& where, int SIZE)
  {

  Chunk Superchunk;

  auto currentChunk = chunks.find(std::make_pair(Tmp.getX() + 1, Tmp.getY() - 1));
  if (currentChunk != chunks.end())
  {
  auto end = currentchunk.cend();
  for (auto it = currentchunk.cbegin(); it != end; ++it)
  {
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

  void Architecte::interpolateCoords(std::vector<Chunk::Coord*> destination, const std::vector<Chunk::Coord*>& source)

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

//int interpolate(int y1, int y2, int n, int delta)
//{
//  if (n != 0)
//    return y1 + delta * (y2 - y1) / n;

//  return y1;
//}

int interpolate(int y1, int y2, int n, int delta)
{
  if (n == 0)
    return y1;

  if (n == 1)
    return y2;

  float a = static_cast<float>(delta) / n;
  float v1 = 3 * pow(1 - a, 2) - 2 * pow(1 - a,3);
  float v2 = 3 * pow(a, 2) - 2 * pow(a, 3);

  return y1 * v1 + y2 * v2;
}

int interpolation(const Chunk::texture_coord_type& coords, int i, int j, int frequence)
{
  const int size = coords.size();
  float step = static_cast<float>(coords.size()) / frequence;

  int q = i / step;
  int bound1x = q * step;
  int bound2x = (q + 1) * step;
  if (bound2x >= size)
    bound2x = size - 1;

  q = j / step;
  int bound1y = q * step;
  int bound2y = (q + 1)*step;

  if (bound2y >= size)
    bound2y = size - 1;

  int b00 = coords[bound1x + bound1y * size];
  int b01 = coords[bound1x + bound2y * size];
  int b10 = coords[bound2x + bound1y * size];
  int b11 = coords[bound2x + bound2y * size];

  int v1  = interpolate(b00, b01, bound2y - bound1y, j - bound1y);
  int v2  = interpolate(b10, b11, bound2y - bound1y, j - bound1y);
  int res = interpolate(v1, v2, bound2x - bound1x , i - bound1x);

  return res;
}

Chunk::texture_coord_type
Architecte::generateGround()
{
  Chunk::texture_coord_type tabPoints;
  tabPoints.resize(Chunk::TEXTURE_SIZE * Chunk::TEXTURE_SIZE);


  tabPoints[0] = 5;//Random::rand()% 10;

  for (int i = 1; i < Chunk::TEXTURE_SIZE; ++i)
  {
      tabPoints[i] = (tabPoints[0] + tabPoints[i-1])/2 + static_cast<float>( Random::rand() % Chunk::TEXTURE_SIZE ) / Chunk::TEXTURE_SIZE;

  }

  for (int i = 1; i < Chunk::TEXTURE_SIZE; ++i)
  {
      tabPoints[i*Chunk::TEXTURE_SIZE] = (tabPoints[0] +tabPoints[(i-1)*Chunk::TEXTURE_SIZE])/2 + static_cast<float>( Random::rand() % Chunk::TEXTURE_SIZE ) / Chunk::TEXTURE_SIZE;
  }




    for (int i = 1; i < Chunk::TEXTURE_SIZE ; ++i )
    {
      for (int j = 1; j < Chunk::TEXTURE_SIZE ; ++j )
      {

        tabPoints[i + j * Chunk::TEXTURE_SIZE] =  (tabPoints[0]+
                                                  tabPoints[(i-1) + (j-1) * Chunk::TEXTURE_SIZE] +
                                                  tabPoints[(i-1) + (j) * Chunk::TEXTURE_SIZE] +
                                                  tabPoints[(i) + (j-1) * Chunk::TEXTURE_SIZE])/4 +
                                                  + static_cast<float>( Random::rand() % Chunk::TEXTURE_SIZE ) / Chunk::TEXTURE_SIZE;

      }
    }



  return tabPoints;
}
