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
//Il n'est pas sensé échanger quoi que ce soit avec le reste , c'est le côté open GL du programme.
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

    int Prout=0;
    int k = 0;
    for (Map::solTriangle_type::const_iterator it = from; it != to; ++it)
    {
        ++k;

        if (Prout==0)
        glTexCoord2i(0,0);

        if (Prout==1)
        glTexCoord2i(0,1);

        if (Prout==2)
        glTexCoord2i(1,0);

        glVertex3d((*it)->_x,(*it)->_y,(*it)->_z);


        ++Prout;
        Prout=Prout%3;

        if (k == 25)
            glColor3ub(255,0,0);

       if (k == 50)
            glColor3ub(0,0,255);
        if (k == 75)
            glColor3ub(0,255,0);
        k %= 76;

    }
    glColor3ub(255, 255, 255);

    glEnd();

    glPopMatrix();
}

} // namespace

Drawer::Drawer()
{
}

void Drawer::drawMap(const Map & map)const
{
    draw(map.begin(), map.end());
    draw(map.Tbegin(), map.Tend());
}


