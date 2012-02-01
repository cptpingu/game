#ifndef ARCHITECTE_H
#define ARCHITECTE_H
#include "Vector3D.hh"
#include "Map.hh"

class Architecte
{
public:
    Architecte();
    void ground(Map::triangles_type& tmp, const Vector3D& where, int size);
    void building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur);
    void mountain(Map::triangles_type& tmp,const Vector3D& where, double peak, int size);
    void mergeGround(Map::triangles_type& ground, const Map::triangles_type& deformation);
};

#endif // ARCHITECTE_H
