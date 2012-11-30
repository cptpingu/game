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
    if (isHighlighted(Block::up) ||
        isHighlighted(Block::down) ||
        isHighlighted(Block::left) ||
        isHighlighted(Block::right) ||
        isHighlighted(Block::front) ||
        isHighlighted(Block::back))
    {
      glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), 0.2);
    }
    else
      glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), 0.0);

    glBegin(GL_TRIANGLE_STRIP);

    //par terre
    glTexCoord2d(0, 0);
    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
    glTexCoord2d(Block::SIZE, 0);
    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
    glTexCoord2d(Block::SIZE, Block::SIZE);
    glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);

    //face droite
    glTexCoord2d(0, 0);
    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
    glTexCoord2d(Block::SIZE, 0);
    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
    glTexCoord2d(Block::SIZE, Block::SIZE);
    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, 0);

    //face gauche
    glTexCoord2d(0, 0);
    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
    glTexCoord2d(Block::SIZE, 0);
    glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
    glTexCoord2d(Block::SIZE, Block::SIZE);
    glVertex3d(Block::SIZE / 2, Block::SIZE / 2, 0);

//    //face face
//    glTexCoord2d(0, 0);
//    CHECK_HIGHLIGHT(Block::front);
//    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, 0);
//    CHECK_HIGHLIGHT(Block::front);
//    glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::front);
//    glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
//    glTexCoord2d(0, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::front);
//    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);

//    //face derriere
//    glTexCoord2d(0, 0);
//    CHECK_HIGHLIGHT(Block::back);
//    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, 0);
//    CHECK_HIGHLIGHT(Block::back);
//    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::back);
//    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, 0);
//    glTexCoord2d(0, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::back);
//    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);

//    //face au ciel
//    glTexCoord2d(0, 0);
//    CHECK_HIGHLIGHT(Block::up);
//    glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, 0);
//    CHECK_HIGHLIGHT(Block::up);
//    glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(Block::SIZE, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::up);
//    glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
//    glTexCoord2d(0, Block::SIZE);
//    CHECK_HIGHLIGHT(Block::up);
//    glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);

    glEnd();

    glPopMatrix();
  }
} // Block
