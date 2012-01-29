#include "Map.hh"
#include "Drawer.hh"
#include "SolTriangle.hh"
#include "Block.hh"
#include <vector>
#include "TextureManager.hh"
#include "Opengl.hh"

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
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    glActiveTexture(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glActiveTexture(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures["wood"]);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    int i = 0;
    glBegin(GL_TRIANGLE_STRIP);
    auto end = triangles.end();
    for (auto it = triangles.begin(); it != end; ++it)
    {
      glMultiTexCoord3i(GL_TEXTURE1, 0, 0, 0);
      glTexCoord2i((*it)->_x, (*it)->_y);
      glVertex3d((*it)->_x, (*it)->_y, (*it)->_z);
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
