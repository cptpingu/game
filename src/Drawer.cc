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


Drawer::Drawer()
{
}


void Drawer::drawMap(const Map & map) const

{

 draw(map._blocks);
 draw(map._triangles);

}


void Drawer::draw(std::vector<Block*> where)

{

    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    glBegin(GL_QUADS);

    for (int i=0;i<where.size();++i)//Besoin de la taille du vecteur where
    {
    glTranslatef(where[i]->_x * where[i]->_size, where[i]->_y * where[i]->_size, where[i]->_z * where[i]->_size);

    //par terre
    glTexCoord2d(0, 0);
    glVertex3d(-where[i]->_size / 2, -where[i]->_size / 2,0);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2,0);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2,0);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2,0);

    //face droite
    glTexCoord2d(0, 0);
    glVertex3d(-where[i]->_size / 2,-where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2, 0);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, -where[i]->_size / 2, 0);

    //face gauche
    glTexCoord2d(0, 0);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2, 0);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2, 0);

    //face face
    glTexCoord2d(0, 0);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2,0);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2,0);

    //face derriere
    glTexCoord2d(0, 0);
    glVertex3d(-where[i]->_size / 2, -where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2, 0);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, -where[i]->_size / 2,0);
    //face au ciel
    glTexCoord2d(0, 0);
    glVertex3d(-where[i]->_size / 2, -where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, 0);
    glVertex3d(where[i]->_size / 2, -where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(where[i]->_size, where[i]->_size);
    glVertex3d(where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);
    glTexCoord2d(0, where[i]->_size);
    glVertex3d(-where[i]->_size / 2, where[i]->_size / 2, where[i]->_size);


    glPopMatrix();
    }
    glEnd();

}



void Drawer::draw(std::vector<SolTriangle*> where)
{
    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();

    glBindTexture(GL_TEXTURE_2D, textures["test"]);

    glBegin(GL_TRIANGLE_STRIP);

    for (int i=0;i<where.size();++i)//Taille de la liste de triangle, drawer suppose que l utilisateur sait ce qu il fait
    {
    glVertex3d(where[i]->_x,where[i]->_y,where[i]->_z);
    }
    glEnd();
    glPopMatrix();
}



