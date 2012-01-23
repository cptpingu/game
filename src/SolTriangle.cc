#include "SolTriangle.hh"
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>

SolTriangle::SolTriangle()
    : _x(0), _y(0), _z(0)

{
}


SolTriangle::SolTriangle(int x, int y, int z)
    :_x(x), _y(y), _z(z)
{
}



void SolTriangle::draw() const
{
    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["test"]);

    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(_x,_y,_z);
    glVertex3d(_x+1,_y,_z);
    glVertex3d(_x,_y+1,_z);

    glEnd();

    glBegin(GL_TRIANGLE_STRIP);

    glVertex3d(_x+1,_y+1,_z);
    glVertex3d(_x,_y+1,_z);
    glVertex3d(_x+1,_y,_z);

    glEnd();
    glPopMatrix();
}













