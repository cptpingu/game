#include "Triangle.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"

namespace Block
{
  Triangle::Triangle(int x, int y, int z)
    : super(x, y, z)
  {
  }

  Triangle::~Triangle()
  {
  }

  std::string
  Triangle::getShaderName() const
  {
    return "cube"; // FIXME créer un shader pour les triangles
  }

  void
  Triangle::specificDraw(const NeighbourMatrix& neighbours) const
  {
    TextureManager& textures = TextureManager::getInstance();
    ShadersManager& shaders = ShadersManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["metal"]);

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);
    glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), isHighlight() ? 0.2 : 0.0);

    glBegin(GL_TRIANGLE_STRIP);
    //glBegin(GL_TRIANGLE_FAN);

    glTexCoord2d(0, 0);
    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
    glTexCoord2d(Block::SIZE, 0);
    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
    glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
    glTexCoord2d(Block::SIZE, Block::SIZE);
    glVertex3d(0, 0,Block::SIZE);
    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);

    glEnd();

    glPopMatrix();
  }
} // Block
