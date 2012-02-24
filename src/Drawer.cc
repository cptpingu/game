#include "Map.hh"
#include "Drawer.hh"
#include "SolTriangle.hh"
#include "Block.hh"
#include "TextureManager.hh"
#include "Opengl.hh"

#include <vector>
#include <sstream>

//Le fonctionnement idéal du drawer => il recoit des listes d'objets typés et dessine les objets OPEN_GL correspondants
//Il n'est pas censé échanger quoi que ce soit avec le reste , c'est le côté open GL du programme.
namespace
{
  void draw(const Map::blocks_type& blocks)
  {
    TextureManager& textures = TextureManager::getInstance();
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

  void draw(const std::pair<int, int>& coord, const Chunk& chunk)
  {
    glPushMatrix();
    TextureManager& textures = TextureManager::getInstance();
    std::ostringstream buff;
    buff << "chunk_" << coord.first << "_" << coord.second;
    const std::string textureName = buff.str();
    auto tex = textures.find(textureName);
    if (tex == textures.end())
      tex = textures.find("brick1");

    glBindTexture(GL_TEXTURE_2D, tex->second);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLE_STRIP);
    auto end = chunk.cend();
    for (auto it = chunk.cbegin(); it != end; ++it)
    {
      glTexCoord2f((((*it)->getY()) / Chunk::SIZE),
                   1.0 - ((*it)->getX()) / Chunk::SIZE);
      glVertex3f((*it)->getX() + coord.first * (Chunk::SIZE - 1) - (Chunk::SIZE / 2),
                 (*it)->getY() + coord.second * (Chunk::SIZE - 1) - (Chunk::SIZE / 2),
                 (*it)->getZ());
    }
    glEnd();

    glPopMatrix();
  }

  void draw(const Map::chunks_type& chunks)
  {
    auto end = chunks.cend();
    for (auto it = chunks.cbegin(); it != end; ++it)
      draw(it->first, *it->second);
  }

} // namespace

Drawer::Drawer()
{
}

void Drawer::drawMap(const Map& map) const
{
  draw(map.getBlocks());
  //draw(map.getTriangles());
  draw(map.getChunks());
}
