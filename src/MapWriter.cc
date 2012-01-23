#include "MapWriter.hh"
#include "SolTriangle.hh"
#include <iostream>
#include <string>
#include <fstream>

MapWriter::MapWriter()
{}



void MapWriter::Debut()
{
int i,j;
using namespace std;

ofstream fichier("Blocks.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert


 for(i=0;i<=10;i++)
 {
         for(j = 0;j <= 10; j++)
    {
             fichier << i  << " " << j <<" "<< 1 << std::endl;
    }

 }
}

void MapWriter::Sol()

{
    using namespace std;

    ofstream fichier("Sol.txt", ios::out | ios::trunc);

        for(i=0;i<=49;i++)
            {
            for(j = 0;j <= 49; j++)
                {
                fichier << i  << " " << j <<" "<< 0 << std::endl;
                }

            }
}




SolTriangle*  MapWriter::Montagne(const & Vector3D ou,int HauteurMax);
{
 int Sommet = rand()%HauteurMax;//hauteur max
 int Largeur = rand()%(2*Sommet);



for (i=0;i<=Largeur;i++)

        {
         while(Sol[i])
         Sol[i]._z= ou_.z + exp(-(ou._x-Sol._x*ou._x-Sol._x+ou._y-Sol._y*ou._y-Sol._y));
        }

 return(Sol)

}

















