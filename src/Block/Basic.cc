#include "Basic.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"

namespace Block
{
  Basic::Basic(int x, int y, int z)
    : super(x, y, z),
      _highlights()
  {
  }

  Basic::~Basic()
  {
  }

  std::string
  Basic::getShaderName() const
  {
    return "textures";
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
    if (isHighlight())
      selectionDraw();
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
