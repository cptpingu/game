#include "MapWriter.hh"
#include "SolTriangle.hh"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <vector>

MapWriter::MapWriter()
{}



void MapWriter::Debut()
{

std::ofstream fichier("Carte.txt");  // ouverture en écriture avec effacement du fichier ouvert


 for(int i=0; i<=10 ;i++)
 {
         for(int j = 0;j <= 10; j++)
    {
             fichier << i  << " " << j <<" "<< 1 << std::endl;

    }

 }
}



void MapWriter::Sol(int size)

{

    std::vector<double> Altitude;
    const unsigned int loopSize = size * size;
    Altitude.reserve(loopSize);
    for  (int i=0;i<loopSize;++i)
    {

                Altitude[i] = rand()%50;

    }

    for (int k=0;k<=20;++k)
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
        fichier << 0  << " " << 0 <<" "<<  Altitude[0]  << std::endl;

        for(int i = 0; i <= size-1; i++)
            {
            for(int j = 0; j <= size-1; j++)
                {

                    if(j != size-1)
                    {

                        fichier << i  << " " << k*(size) +   (j+1) -2*k*(j+1) <<" "<<  Altitude[i+size*(k*(size) +   (j+1) -2*k*(j+1))] << std::endl;
                        fichier << i+1  << " " << k*(size)+  (j+1) -2*k*(j+1) <<" "<<  Altitude[i+1+size*(k*(size)+  (j+1) -2*k*(j+1))] << std::endl;
                    }
                    else
                    {
                     k=(k+1)%2;
                     fichier << i+1  << " " << k*size <<" "<< Altitude[i+1 + k*(size-1)*size]  << std::endl;
                     //fichier << i+2  << " " << k*size-1 <<" "<< 0   << std::endl;
                    }
}
}
}




