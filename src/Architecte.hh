#ifndef ARCHITECTE_H
#define ARCHITECTE_H
#include "Vector3D.hh"
#include "Map.hh"
#include <array>

class Architecte
{
public:
    Architecte();
    void generateRandomGround(Chunk& tmp, const Vector3D& where);
    void building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur);
    void mountain(Map::triangles_type& tmp,const Vector3D& where, double peak, int size);
    void mergeGround(Map::triangles_type& generateRandomGround, const Map::triangles_type& deformation);
    /*static void interpolateCoords(std::vector<Chunk::Coord*> destination , const std::vector<Chunk::Coord*>& source);*/
    std::array<double, Chunk::TEXTURE_SIZE * Chunk::TEXTURE_SIZE > && generateGround();
};

#endif // ARCHITECTE_H
