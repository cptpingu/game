#include "SolTriangle.hh"
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>

SolTriangle::SolTriangle()
    : _x(0), _y(0), z_(0)

{
}


SolTriangle::SolTriangle(int x, int y, int z)
    :_x(x), _y(y), _z(z)
{
}



SolTriangle::draw()
{
    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["test"]);

    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(_x,_y,z);
    glVertex3d(_x+1,_y,z);
    glVertex3d(_x,_y+1,z);

    glEnd();

    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(_x+1,_y+1,0);
    glVertex3d(_x,_y+1,0);
    glVertex3d(_x+1,_y+1,0);

    glEnd();
    glPopMatrix();
}













