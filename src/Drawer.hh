#ifndef DRAWER_HH
#define DRAWER_HH

#include "SolTriangle.hh"
#include "Block.hh"
#include <vector>
#include "TextureManager.hh"
# include "Opengl.hh"
#include "Vector3D.hh"
#include "Map.hh"

class Drawer
{
public:
    Drawer();

    void drawMap(const Map &map)const;
};

#endif // DRAWER_HH