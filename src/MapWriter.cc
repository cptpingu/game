#include "MapWriter.hh"
#include "SolTriangle.hh"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Vector3D.hh"
#include "Math.h"
MapWriter::MapWriter()
{}



void MapWriter::Debut()
{

std::ofstream fichier("Carte.txt");  // ouverture en écriture avec effacement du fichier ouvert


 for(int i=0; i<=0 ;i++)
 {
         for(int j = 0;j <= 0; j++)
    {
             fichier << i  << " " << j <<" "<< 1 << std::endl;
    }

 }
}



void MapWriter::Sol(int size)

{

    std::vector<double> Altitude;
     int loopSize = (size+3) * (size+3);
    Altitude.reserve(loopSize);
    for  (int i=0;i<loopSize;++i)
    {

                Altitude[i] = rand()%50;

    }

    for (int k=0;k<=30;++k)
    {
        for (int i=0;i <= size-2;++i)
        {
            for (int j=0; j <= size-2;++j)
            {

            Altitude[i+j*size]= (Altitude[i+1+j*size]+Altitude[i+(j+1)*size]+Altitude[i+1+(j+1)*size]+Altitude[i+j*size])/4;
            }
        }
}
    std::ofstream fichier("Terrain.txt");

int k=0;
        for(int i = 0; i <= size-1; i++)
            {
            for(int j = 0; j <= size-1; j++)
                {

                if ( j != size-1)

                {
                fichier << i  << " " << k*(size-1)+j -2*j*k <<" "<< Altitude[i+size*(k*(size-1)+j -2*j*k)]  << std::endl;
                fichier << i+1  << " " << k*(size-1)+j -2*j*k<<" "<< Altitude[i+1+size*(k*(size-1)+j -2*j*k)]   << std::endl;
                }
        else
{
                k=(k+1)%2;

                fichier <<  i  << " " << k*(size) -k  << " " << Altitude[i+1+size*(k*(size-1) -k)] << std::endl;
                //fichier <<  i  << " " << k*(size-) -k  << " " << Altitude[i+1+size*(k*(size-1) -k)] << std::endl;


}
}
            }




}

void MapWriter::Building(Vector3D where ,int Longueur,int Hauteur,int Largeur)
{

    Longueur = Longueur + rand()%(Longueur+1);
    Hauteur = 4+4*rand()%4;

    std::ofstream fichier("Carte.txt",std::ios::app);




    fichier << where._x<<" " << where._y <<" "<< where._z << std::endl;


    for (int j=0;j<=Hauteur;++j)
    {for (int i=0;i<=Longueur;++i)
        {fichier << where._x <<" "<< where._y+i<<" " << where._z+j << std::endl;
            fichier << where._x+Largeur <<" "<< where._y+i<<" " << where._z+j << std::endl;
        }
    }
    for (int j=1;j<Largeur;++j)
    {for (int i=0;i<=Hauteur;++i)
        {fichier << where._x+j <<" "<< where._y<<" " << where._z+i << std::endl;
            fichier << where._x+j<<" " << where._y+Longueur<<" " << where._z+i << std::endl;}
}

}








void MapWriter::Montagne(Vector3D where ,double Sommet,int size)

{
    std::vector<double> Altitude;
     int loopSize = size * size;
    Altitude.reserve(loopSize);

    for (int k=0;k<=10;++k)
    {
        for (int i=0;i < size;++i)
        {
            for (int j=0; j < size;++j)
            {

            Altitude[i+j*size]=  Sommet*exp(-((i-size/2)*(i-size/2)+(j-size/2)*(j-size/2)));
                //Altitude[i+j*size]= Sommet*fabs(size/2i/size
            }
        }
}
 std::ofstream fichier("Terrain.txt",std::ios::app);

int k=0;
        for(int i = 0; i <= size-1; i++)
            {
            for(int j = 0; j <= size-1; j++)
                {

                if ( j != size-1)

                {
                fichier << i  << " " << k*(size-1)+j -2*j*k <<" "<< Altitude[i+size*(k*(size-1)+j -2*j*k)]  << std::endl;
                fichier << i+1  << " " << k*(size-1)+j -2*j*k<<" "<< Altitude[i+1+size*(k*(size-1)+j -2*j*k)]   << std::endl;
                }
        else
{
                k=(k+1)%2;

                fichier <<  i  << " " << k*(size) -k  << " " << Altitude[i+1+size*(k*(size-1) -k)] << std::endl;
                //fichier <<  i  << " " << k*(size-) -k  << " " << Altitude[i+1+size*(k*(size-1) -k)] << std::endl;


}
}
            }





}
































/*
    void MapWriter::Village(Vector3D where ,int Longueur,int Hauteur,int Largeur)
{
for int i=0;i<10;++i)
{
    }
*/

/*
void MapWriter::Objet(Vector3D where ,int Longueur,int Hauteur,int Largeur)
{
ImageFile Imageface;
ImageFile Imageprofile;
double Diff;


vector::Objet<Vector3D*>

for int (i=0;i<   ;++i)
        for int (j=0;j<  ;++j)
{
    {
        Diff = (ImageFace(i+1,j).red-ImageFace(i,j).red +ImageFace(i+1,j).blue-ImageFace(i,j).blue+ImageFace(i+1,j).green-ImageFace(i,j).green)/3;
        if (Diff>Seuil)
        {ObjectPoints.new(Point(i,j,1));

        Diff = (ImageFace(i,j+1).red-ImageFace(i,j).red +ImageFace(i+1,j).blue-ImageFace(i,j).blue+ImageFace(i+1,j).green-ImageFace(i,j).green)/3;

        if (Diff>Seuil)
        {ObjectPoints.new(Point(i,j,1));
        }

    }
for (int k=0;k<size ;++k)
{
Gravitycenter = Gravitycenter + ObjectPoints.Point(k)/size;
}
for (int k=0;k<size ;++k)
{
if Distance(Gravitycenter,ObjectPoints.Point(k))>Seuil
{ObjectPoints.Point(k)==NULL;}
}




*/
