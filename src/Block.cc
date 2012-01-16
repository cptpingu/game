#include "Block.hh"
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>

Block::Block()
    :_x(0), _y(0), _z(0), _size(10)
{
}

Block::Block(int x, int y, int z, int size)
    :_x(x), _y(y), _z(z), _size(size)
{
}



void Block::draw() const
{
    glPushMatrix();
    glTranslatef(_x * _size, _y * _size, _z * _size);
    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["test"]);

    glBegin(GL_QUADS);
    //par terre
    glTexCoord2d(0, 0);
    glVertex3d(-_size / 2, -_size / 2,0);
    glTexCoord2d(_size, 0);
    glVertex3d(_size / 2, -_size / 2,0);
    glTexCoord2d(_size, _size);
    glVertex3d(_size / 2, _size / 2,0);
    glTexCoord2d(0, _size);
    glVertex3d(-_size / 2, _size / 2,0);

    //face droite
    glTexCoord2d(0, 0);
    glVertex3d(-_size / 2,-_size / 2, _size);
    glTexCoord2d(_size, 0);
    glVertex3d(-_size / 2, _size / 2, _size);
    glTexCoord2d(_size, _size);
    glVertex3d(-_size / 2, _size / 2, 0);
    glTexCoord2d(0, _size);
    glVertex3d(-_size / 2, -_size / 2, 0);

    //face gauche
    glTexCoord2d(0, 0);
    glVertex3d(_size / 2, -_size / 2, _size);
    glTexCoord2d(_size, 0);
    glVertex3d(_size / 2, _size / 2, _size);
    glTexCoord2d(_size, _size);
    glVertex3d(_size / 2, _size / 2, 0);
    glTexCoord2d(0, _size);
    glVertex3d(_size / 2, -_size / 2, 0);

    //face face
    glTexCoord2d(0, 0);
    glVertex3d(-_size / 2, _size / 2, _size);
    glTexCoord2d(_size, 0);
    glVertex3d(_size / 2, _size / 2, _size);
    glTexCoord2d(_size, _size);
    glVertex3d(_size / 2, _size / 2,0);
    glTexCoord2d(0, _size);
    glVertex3d(-_size / 2, _size / 2,0);

    //face derriere
    glTexCoord2d(0, 0);
    glVertex3d(-_size / 2, -_size / 2, _size);
    glTexCoord2d(_size, 0);
    glVertex3d(_size / 2, -_size / 2, _size);
    glTexCoord2d(_size, _size);
    glVertex3d(_size / 2, -_size / 2, 0);
    glTexCoord2d(0, _size);
    glVertex3d(-_size / 2, -_size / 2,0);
    //face au ciel
    glTexCoord2d(0, 0);
    glVertex3d(-_size / 2, -_size / 2, _size);
    glTexCoord2d(_size, 0);
    glVertex3d(_size / 2, -_size / 2, _size);
    glTexCoord2d(_size, _size);
    glVertex3d(_size / 2, _size / 2, _size);
    glTexCoord2d(0, _size);
    glVertex3d(-_size / 2, _size / 2, _size);

    glEnd();
    glPopMatrix();
    glFlush();
}
