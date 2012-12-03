#include "Basic.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include "../IdManager.hh"
#include "../Core/Random.hh"

#include <iostream>

namespace Block
{
  Basic::Basic(int x, int y, int z)
    : super(x, y, z),
      _highlights()
  {
    registerBlock();
  }

  Basic::~Basic()
  {
    unregisterBlock();
  }

  std::string
  Basic::getShaderName() const
  {
    return "textures";
  }

  void
  Basic::registerBlock()
  {
    _id = IdManager::getInstance().getNewIdForBlock(this);
  }

  void
  Basic::unregisterBlock()
  {
    IdManager::getInstance().deleteId(_id);
  }

  void
  Basic::highlight(FaceType face, bool highlight)
  {
    assert(face >= none && face <= back && "Index out of bound!");
    _highlights[face] = highlight;
  }

  bool
  Basic::isHighlighted(FaceType face) const
  {
    assert(face >= none && face <= back && "Index out of bound!");
    return _highlights[face];
  }

  bool
  Basic::isHighlight() const
  {
    return isHighlighted(Block::up) || isHighlighted(Block::down) ||
        isHighlighted(Block::left) || isHighlighted(Block::right) ||
        isHighlighted(Block::front) || isHighlighted(Block::back);
  }

  void
  Basic::resetHighlight()
  {
    auto end = _highlights.end();
    for (auto it = _highlights.begin(); it != end; ++it)
      *it = false;
  }

  void
  Basic::draw(const NeighbourMatrix& neighbours) const
  {
    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable(getShaderName());
    assert(neighbours(0, 0, 0) == this && "Neighbours (0,0,0) must be the block itself!");
    specificDraw(neighbours);
    shaders.disable();
    //drawPickingBox();
    if (isHighlight())
      selectionDraw();
  }

  void
  Basic::drawPickingBox() const
  {
#define DRAW_FACE(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X4, Y4, Z4, FACE)           \
    {                                                                             \
      glColor3f(_id._x / 255.0, _id._y / 255.0, FACE / 255.0);                    \
      glVertex3d(X1 * Block::HALF_SIZE, Y1 * Block::HALF_SIZE, Z1 * Block::SIZE); \
      glColor3f(_id._x / 255.0, _id._y / 255.0, FACE / 255.0);                    \
      glVertex3d(X2 * Block::HALF_SIZE, Y2 * Block::HALF_SIZE, Z2 * Block::SIZE); \
      glColor3f(_id._x / 255.0, _id._y / 255.0, FACE / 255.0);                    \
      glVertex3d(X3 * Block::HALF_SIZE, Y3 * Block::HALF_SIZE, Z3 * Block::SIZE); \
      glColor3f(_id._x / 255.0, _id._y / 255.0, FACE / 255.0);                    \
      glVertex3d(X4 * Block::HALF_SIZE, Y4 * Block::HALF_SIZE, Z4 * Block::SIZE); \
    }

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);

    glBegin(GL_QUADS);

    //par terre
    DRAW_FACE(-1, -1, 0,
              +1, -1, 0,
              +1, +1, 0,
              -1, +1, 0,
              Block::down);

    //face droite
    DRAW_FACE(-1, -1, 1,
              -1, +1, 1,
              -1, +1, 0,
              -1, -1, 0,
              Block::right);

    //face gauche
    DRAW_FACE(+1, -1, 1,
              +1, +1, 1,
              +1, +1, 0,
              +1, -1, 0,
              Block::left);

    //face face
    DRAW_FACE(-1, +1, 1,
              +1, +1, 1,
              +1, +1, 0,
              -1, +1, 0,
              Block::front);

    //face derriere
    DRAW_FACE(-1, -1, 1,
              +1, -1, 1,
              +1, -1, 0,
              -1, -1, 0,
              Block::back);

    //face au ciel
    DRAW_FACE(-1, -1, 1,
              +1, -1, 1,
              +1, +1, 1,
              -1, +1, 1,
              Block::up);
#undef DRAW_FACE

    glEnd();

    glPopMatrix();
  }

  void
  Basic::selectionDraw() const
  {
#define DRAW_LINE(X, Y, Z) \
  glVertex3d(X * Block::HALF_SIZE, Y * Block::HALF_SIZE, Z * Block::SIZE)

    glLineWidth(2.0);

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);
    glColor3d(1, 1, 1);

    glBegin(GL_LINES);

    DRAW_LINE(-1, -1, 0);
    DRAW_LINE(-1, -1, 0);
    DRAW_LINE(+1, +1, 0);
    DRAW_LINE(-1, +1, 0);

    DRAW_LINE(-1, -1, 1);
    DRAW_LINE(-1, +1, 1);
    DRAW_LINE(-1, +1, 0);
    DRAW_LINE(-1, -1, 0);

    DRAW_LINE(+1, -1, 1);
    DRAW_LINE(+1, +1, 1);
    DRAW_LINE(+1, +1, 0);
    DRAW_LINE(+1, -1, 0);

    DRAW_LINE(-1, +1, 1);
    DRAW_LINE(+1, +1, 1);
    DRAW_LINE(+1, +1, 0);
    DRAW_LINE(-1, +1, 0);

    DRAW_LINE(-1, -1, 1);
    DRAW_LINE(+1, -1, 1);
    DRAW_LINE(+1, -1, 0);
    DRAW_LINE(-1, -1, 0);

    DRAW_LINE(-1, -1, 1);
    DRAW_LINE(+1, -1, 1);
    DRAW_LINE(+1, +1, 1);
    DRAW_LINE(-1, +1, 1);

    DRAW_LINE(-1, -1, 0);
    DRAW_LINE(-1, -1, 1);

    DRAW_LINE(+1, +1, 0);
    DRAW_LINE(+1, +1, 1);

    DRAW_LINE(-1, +1, 0);
    DRAW_LINE(-1, +1, 1);

    DRAW_LINE(+1, -1, 0);
    DRAW_LINE(+1, -1, 1);
#undef DRAW_FACE

    glEnd();

    glPopMatrix();

    glLineWidth(1.0);
  }
} // Block
