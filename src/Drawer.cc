#include "Map.hh"
#include "Drawer.hh"
#include "SolTriangle.hh"
#include "Block.hh"
#include <vector>
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "Vector3D.hh"

//Le fonctionnement idéal du drawer => il recoit des listes d'objets typés et dessine les objets OPEN_GL correspondants

namespace
{
void draw(const Map::blocks_type::const_iterator& from,
          const Map::blocks_type::const_iterator& to)

{
    TextureManager& textures = Singleton<TextureManager>::getInstance();
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    for (Map::blocks_type::const_iterator it = from; it != to; ++it)
    {
        glPushMatrix();
        glTranslatef((*it)->_x * (*it)->_size, (*it)->_y * (*it)->_size, (*it)->_z * (*it)->_size);
        glBegin(GL_QUADS);

        //par terre
        glTexCoord2d(0, 0);
        glVertex3d(-(*it)->_size / 2, -(*it)->_size / 2,0);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2,0);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2,0);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2,0);

        //face droite
        glTexCoord2d(0, 0);
        glVertex3d(-(*it)->_size / 2,-(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2, 0);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, -(*it)->_size / 2, 0);

        //face gauche
        glTexCoord2d(0, 0);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2, 0);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2, 0);

        //face face
        glTexCoord2d(0, 0);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2,0);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2,0);

        //face derriere
        glTexCoord2d(0, 0);
        glVertex3d(-(*it)->_size / 2, -(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2, 0);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, -(*it)->_size / 2,0);
        //face au ciel
        glTexCoord2d(0, 0);
        glVertex3d(-(*it)->_size / 2, -(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, 0);
        glVertex3d((*it)->_size / 2, -(*it)->_size / 2, (*it)->_size);
        glTexCoord2d((*it)->_size, (*it)->_size);
        glVertex3d((*it)->_size / 2, (*it)->_size / 2, (*it)->_size);
        glTexCoord2d(0, (*it)->_size);
        glVertex3d(-(*it)->_size / 2, (*it)->_size / 2, (*it)->_size);

        glEnd();

        glPopMatrix();
    }
}

void draw(const Map::solTriangle_type::const_iterator& from,
          const Map::solTriangle_type::const_iterator& to)

{
    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["test"]);

    glBegin(GL_TRIANGLE_STRIP);

    for (Map::solTriangle_type::const_iterator it = from; it != to; ++it)
        glVertex3d((*it)->_x,(*it)->_y,(*it)->_z);

    glEnd();
    glPopMatrix();
}

} // namespace

Drawer::Drawer()
{
}

void Drawer::drawMap(const Map & map) const
{
    draw(map.begin(), map.end());
    draw(map.Tbegin(), map.Tend());
}


