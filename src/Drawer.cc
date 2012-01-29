#include "Map.hh"
#include "Drawer.hh"
#include "SolTriangle.hh"
#include "Block.hh"
#include <vector>
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>

//Le fonctionnement id�al du drawer => il recoit des listes d'objets typ�s et dessine les objets OPEN_GL correspondants
//Il n'est pas cens� �changer quoi que ce soit avec le reste , c'est le c�t� open GL du programme.
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
      if (!(*it)->_down)
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
      if (!(*it)->_right)
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
      if (!(*it)->_left)
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
      if (!(*it)->_front)
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
      if (!(*it)->_back)
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
      if (!(*it)->_up)
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glBegin(GL_TRIANGLE_STRIP);

    auto end = triangles.end();
    for (auto it = triangles.begin(); it != end; ++it)
    {
      glTexCoord2i((*it)->_x,(*it)->_y);
      glVertex3d((*it)->_x,(*it)->_y,(*it)->_z);
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
