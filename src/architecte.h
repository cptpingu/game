#ifndef ARCHITECTE_H
#define ARCHITECTE_H
#include "Vector3D.hh"
#include "Map.hh"

class Architecte
{
public:
    Architecte();
    void Ground(Map::triangles_type & Tmp,const Vector3D & where,const int & size);
    void Building(Map::blocks_type & Tmp,const Vector3D & where ,int Longueur,int Hauteur,int Largeur);
    void Montagne(Map::triangles_type & Tmp,const Vector3D  & where, double Peak ,int size);
    void MergeGround(Map::triangles_type & ground,const Map::triangles_type & deformation );

};

#endif // ARCHITECTE_H
