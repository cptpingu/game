#ifndef DRAWER_HH
#define DRAWER_HH

#include "SolTriangle.hh"
#include "Block.hh"
#include <vector>
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3D.hh"
#include "Map.hh"

class Drawer
{
public:
    Drawer();
    void draw(std::vector<Block*> where);
    void draw(std::vector<SolTriangle*> where);
    void drawMap(const Map & map)const ;
};

#endif // DRAWER_HH
