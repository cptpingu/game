#ifndef MAPWRITER_HH
#define MAPWRITER_HH
#include "Vector3D.hh"

class MapWriter
{



public:
    MapWriter();
    void Debut();
    void Sol(int size);
    void Building(Vector3D where ,int Longueur,int Hauteur, int Largeur);
    void Montagne(Vector3D where ,double Sommet,int size);

};

#endif // MAPWRITER_HH
