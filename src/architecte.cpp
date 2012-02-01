#include "architecte.h"
#include <cstdlib>
#include <iostream>
#include "Vector3D.hh"
#include <vector>
#include <fstream>
#include "Math.h"
#include "Map.hh"

namespace
{

void apply(const SolTriangle*  deformation, SolTriangle* original )
{

original ->_z = original ->_z + deformation ->_z/2;
}
}




Architecte::Architecte()
{

}
//L'architecte fait les plans : les écrits dans un fichier et / ou les stock en memoire.


void Architecte::Ground(Map::triangles_type & Tmp, const  Vector3D & where,const int & size)

{
std::vector<double> Height;
int loopSize = size * size;
Height.reserve(loopSize);
double HeightMean=0;

for  (int i=0;i<loopSize;++i)
    {

    Height[i] = rand()%50;
    HeightMean = HeightMean + Height[i];
    }
    HeightMean = HeightMean / loopSize;
    for (int k=0;k<=30;++k)
    {
        for (int i=0;i < size-1;++i)
        {
            for (int j=0; j < size-1;++j)
            {

            Height[i+j*size]= (Height[i+1+j*size]+Height[i+(j+1)*size]+Height[i+1+(j+1)*size]+Height[i+j*size])/4;
            if (i == size-2)
            { Height[i+1+j*size]=Height[i+j*size];}

            if (j == size -2)
            {Height[i+(j+1)*size] =Height[i+j*size];}

            }
            }
        }


int k=0;

for(int i = 0; i <= size-1; i++)
    {
        for(int j = 0; j <= size-1; j++)
        {

         if ( j != size-1)
            {
             Tmp.add( new SolTriangle(i+where._x,k*(size-1)+j -2*j*k +where._y,Height[i+size*(k*(size-1)+j -2*j*k)]+where._z -HeightMean));
             Tmp.add(new SolTriangle (i+1+where._x, k*(size-1)+j -2*j*k+where._y, Height[i+1+size*(k*(size-1)+j -2*j*k)] +where._z -HeightMean));
            }
        else
            {
            k=(k+1)%2;
            Tmp.add(new SolTriangle(i+where._x,k*(size) -k +where._y ,Height[i+1+size*(k*(size-1) -k)]+where._z -HeightMean));
            }


        }
    }
}

void Architecte::Building(Map::blocks_type & Tmp ,const Vector3D & where ,int Longueur,int Hauteur,int Largeur)
{
    int L;
    int l;
    int H;
    l = Largeur + rand()%(Largeur+1);
    L = Longueur + rand()%(Longueur+1);
    H = Hauteur+Hauteur*rand()%4;


    for (int j=0;j<=H;++j)
    {for (int i=0;i<=L;++i)
         {
          Tmp.add( new Block(where._x, where._y+i, where._z+j));
          Tmp.add( new Block(where._x+1, where._y+i, where._z+j));
         }
    }
    for (int j=1;j<l;++j)
    {for (int i=0;i<=H;++i)
        {
        Tmp.add( new Block(where._x+j, where._y, where._z+i));
        Tmp.add( new Block(where._x+j, where._y+L, where._z+i));
        }

    }
}

void Architecte::Montagne(Map::triangles_type & Tmp,const Vector3D & where ,double Peak,int size)

{
    std::vector<double> Height;
    int loopSize = size * size;
    Height.reserve(loopSize);

    for (int k=0;k<=20;++k)
    {
        for (int i=0;i < size;++i)
        {
            for (int j=0; j < size;++j)
            {

            Height[i+j*size]=  Peak*exp(-((i-size/2)*(i-size/2)+(j-size/2)*(j-size/2)));

            }
        }
}
    for (int k=0;k<=10;++k)
    {
        for (int i=0;i < size-1;++i)
        {
            for (int j=0; j < size-1;++j)
            {

            Height[i+j*size]= (Height[i+1+j*size]+Height[i+(j+1)*size]+Height[i+1+(j+1)*size]+Height[i+j*size])/4;
            }
        }
}
int k=0;
        for(int i = 0; i <= size-1; i++)
            {
            for(int j = 0; j <= size-1; j++)
                {

                if ( j != size-1)

                {
                Tmp.add( new SolTriangle(i+where._x,k*(size-1)+j -2*j*k +where._y,Height[i+size*(k*(size-1)+j -2*j*k)]+where._z));
                Tmp.add(new SolTriangle (i+1+where._x, k*(size-1)+j -2*j*k+where._y, Height[i+1+size*(k*(size-1)+j -2*j*k)] +where._z));
                }
        else
                {
                k=(k+1)%2;
                Tmp.add(new SolTriangle(i+where._x,k*(size) -k +where._y ,Height[i+1+size*(k*(size-1) -k)]+where._z));

                }
}
            }

}


void Architecte::MergeGround(Map::triangles_type & ground,const Map::triangles_type & deformation )

{
    auto end1 = ground.end();
    auto end2 = deformation.end();
    auto it1 = ground.begin();
    for (auto it2 = deformation.begin(); it2 != end2; ++it2)
        {
        while (it1 != end1 && *it1 != *it2)
         ++it1;
        apply(*it1,*it2);
        ++it1;
        }
}




