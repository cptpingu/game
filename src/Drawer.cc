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
//Il n'est pas censé échanger quoi que ce soit avec le reste , c'est le côté open GL du programme.
namespace
{
  void draw(const Map::blocks_type& blocks)

  {
    TextureManager& textures = Singleton<TextureManager>::getInstance();
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    auto end = blocks.end();
    for (auto it = blocks.begin(); it != end; ++it)
    {
      glPushMatrix();
      glTranslatef((*it)->_x * Block::SIZE, (*it)->_y * Block::SIZE, (*it)->_z * Block::SIZE);
      glBegin(GL_QUADS);

      //par terre
      if ((*it)->_down)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
      }

      //face droite
      if ((*it)->_right)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2,-Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, 0);
      }

      //face gauche
      if ((*it)->_left)
      {
        glTexCoord2d(0, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, 0);
      }

      //face face
      if ((*it)->_front)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
      }

      //face derriere
      if ((*it)->_back)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
      }

      //face au ciel
      if ((*it)->_up)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
      }

      glEnd();

      glPopMatrix();
    }
  }

  void draw(const Map::triangles_type& triangles)

  {
    glPushMatrix();

    TextureManager& textures = Singleton<TextureManager>::getInstance();
    glBindTexture(GL_TEXTURE_2D, textures["veg2"]);
    glBegin(GL_TRIANGLE_STRIP);

    int Prout=0;
    int k = 0;
    auto end = triangles.end();
    for (auto it = triangles.begin(); it != end; ++it)
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
    glEnd();
    glPopMatrix();
  }
} // namespace

Drawer::Drawer()
{
}

void Drawer::drawMap(const Map& map) const
{
  draw(map.getBlocks());
  draw(map.getTriangles());
}
