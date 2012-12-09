#include "Basic.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include "../IdManager.hh"
#include "../Core/Random.hh"

#include <iostream>

// front up

namespace Block
{
  const GLfloat Basic::_vertices[108] =
  {
    +1, +1, +1,  -1, +1, +1,  -1, -1, +1, // v0-v1-v2 (up)
    -1, -1, +1,  +1, -1, +1,  +1, +1, +1, // v2-v3-v0

    +1, +1, +1,  +1, -1, +1,  +1, -1, -1, // v0-v3-v4 (right)
    +1, -1, -1,  +1, +1, -1,  +1, +1, +1, // v4-v5-v0

    +1, +1, +1,   +1, +1,-1,  -1, +1, -1, // v0-v5-v6 (back)
    -1, +1, -1,  -1, +1, +1,  +1, +1, +1, // v6-v1-v0

    -1, +1, +1,  -1, +1, -1,  -1, -1, -1, // v1-v6-v7 (left)
    -1, -1, -1,  -1, -1, +1,  -1, +1, +1, // v7-v2-v1

    -1, -1, -1,  +1, -1, -1,  +1, -1, +1, // v7-v4-v3 (front)
    +1, -1, +1,  -1, -1, +1,  -1, -1, -1, // v3-v2-v7

    +1, -1, -1,  -1, -1, -1,  -1, +1, -1, // v4-v7-v6 (down)
    -1, +1, -1,  +1, +1, -1,  +1, -1, -1  // v6-v5-v4
  };

  // normal array
  const GLfloat Basic::_normals[108] =
  {
    0, 0, 1,   0, 0, 1,   0, 0, 1,        // v0-v1-v2 (up)
    0, 0, 1,   0, 0, 1,   0, 0, 1,        // v2-v3-v0

    1, 0, 0,   1, 0, 0,   1, 0, 0,        // v0-v3-v4 (right)
    1, 0, 0,   1, 0, 0,   1, 0, 0,        // v4-v5-v0

    0, 1, 0,   0, 1, 0,   0, 1, 0,        // v0-v5-v6 (back)
    0, 1, 0,   0, 1, 0,   0, 1, 0,        // v6-v1-v0

    -1, 0, 0,  -1, 0, 0,  -1, 0, 0,       // v1-v6-v7 (left)
    -1, 0, 0,  -1, 0, 0,  -1, 0, 0,       // v7-v2-v1

    0,-1, 0,   0,-1, 0,   0,-1, 0,        // v7-v4-v3 (front)
    0,-1, 0,   0,-1, 0,   0,-1, 0,        // v3-v2-v7

    0, 0,-1,   0, 0,-1,   0, 0,-1,        // v4-v7-v6 (down)
    0, 0,-1,   0, 0,-1,   0, 0,-1         // v6-v5-v4
  };

  // texture array
  const GLfloat Basic::_textures[108] =
  {
    1, 1, 0,  0, 1, 0,  0, 0, 0,          // v0-v1-v2 (up)
    0, 0, 0,  1, 0, 0,  1, 1, 0,          // v2-v3-v0

    1, 1, 0,  0, 1, 0,  0, 0, 0,          // v0-v3-v4 (right)
    0, 0, 0,  1, 0, 0,  1, 1, 0,          // v4-v5-v0

    0, 1, 0,  0, 0, 0,  1, 0, 0,          // v0-v5-v6 (back)
    1, 0, 0,  1, 1, 0,  0, 1, 0,          // v6-v1-v0

    0, 1, 0,  0, 0, 0,  1, 0, 0,          // v1-v6-v7 (left)
    1, 0, 0,  1, 1, 0,  0, 1, 0,          // v7-v2-v1

    0, 0, 0,  1, 0, 0,  1, 1, 0,          // v7-v4-v3 (front)
    1, 1, 0,  0, 1, 0,  0, 0, 0,          // v3-v2-v7

    1, 1, 0,  0, 1, 0,  0, 0, 0,          // v4-v7-v6 (down)
    0, 0, 0,  1, 0, 0,  1, 1, 0           // v6-v5-v4
  };

  Basic::Basic(int x, int y, int z)
    : super(x, y, z),
      _highlights(),
      _pickingVBOId(0)
  {
    registerBlock();
  }

  Basic::~Basic()
  {
    unregisterBlock();
  }

  void
  Basic::init()
  {
    initPickingBox();
    specificInit();
  }

  void
  Basic::initPickingBox()
  {
#define INIT_COLOR(SHIFT, COLOR)                            \
    for (int i = 18 * SHIFT; i < 18 + (18 * SHIFT); i += 3) \
    {                                                       \
      _pickingColors[0 + i] = _id._x / 255.0;               \
      _pickingColors[1 + i] = _id._y / 255.0;               \
      _pickingColors[2 + i] = COLOR / 255.0;                \
    }

    INIT_COLOR(0, Block::up);
    INIT_COLOR(1, Block::right);
    INIT_COLOR(2, Block::back);
    INIT_COLOR(3, Block::left);
    INIT_COLOR(4, Block::front);
    INIT_COLOR(5, Block::down);
#undef INIT_COLOR

    glGenBuffers(1, &_pickingVBOId);
    ASSERT_MSG(_pickingVBOId, "Vertex buffer initialisation failed!");
    glBindBuffer(GL_ARRAY_BUFFER, _pickingVBOId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices) + sizeof(_normals) + sizeof(_pickingColors), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertices), _vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(_vertices), sizeof(_normals), _normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(_vertices) + sizeof(_normals), sizeof(_pickingColors), _pickingColors);
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
    ASSERT_MSG(face >= none && face <= back, "Index out of bound: " << face);
    _highlights[face] = highlight;
  }

  bool
  Basic::isHighlighted(FaceType face) const
  {
    ASSERT_MSG(face >= none && face <= back, "Index out of bound: " << face);
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
    //ASSERT_MSG(neighbours(0, 0, 0) == this, "Neighbours (0,0,0) must be the block itself!");
    specificDraw(neighbours);
    shaders.disable();
    //drawPickingBox();
    if (isHighlight())
      selectionDraw();
  }

  Core::Vector3D
  Basic::collision(const Core::Vector3D& current, const Core::Vector3D& next) const
  {
    return specificCollision(current, next);
  }

  void
  Basic::drawPickingBox() const
  {
    ASSERT_MSG(_pickingVBOId, "Invalid vertex buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, _pickingVBOId);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 0, (void*)sizeof(_vertices));
    glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(_vertices)+sizeof(_normals)));
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glPushMatrix();
    glTranslatef(_x * Block::SIZE + Block::SIZE / 2,
                 _y * Block::SIZE + Block::SIZE / 2,
                 _z * Block::SIZE + Block::SIZE / 2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void
  Basic::selectionDraw() const
  {
    // FIXME put in a vbo
#define DRAW_LINE(X, Y, Z) \
  glVertex3d(X * Block::SIZE, Y * Block::SIZE, Z * Block::SIZE)

    glLineWidth(2.0);

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);
    glColor3d(1, 1, 1);

    glBegin(GL_LINES);

    DRAW_LINE(0, 0, 0);
    DRAW_LINE(0, 0, 0);
    DRAW_LINE(1, 1, 0);
    DRAW_LINE(0, 1, 0);

    DRAW_LINE(0, 0, 1);
    DRAW_LINE(0, 1, 1);
    DRAW_LINE(0, 1, 0);
    DRAW_LINE(0, 0, 0);

    DRAW_LINE(1, 0, 1);
    DRAW_LINE(1, 1, 1);
    DRAW_LINE(1, 1, 0);
    DRAW_LINE(1, 0, 0);

    DRAW_LINE(0, 1, 1);
    DRAW_LINE(1, 1, 1);
    DRAW_LINE(1, 1, 0);
    DRAW_LINE(0, 1, 0);

    DRAW_LINE(0, 0, 1);
    DRAW_LINE(1, 0, 1);
    DRAW_LINE(1, 0, 0);
    DRAW_LINE(0, 0, 0);

    DRAW_LINE(0, 0, 1);
    DRAW_LINE(1, 0, 1);
    DRAW_LINE(1, 1, 1);
    DRAW_LINE(0, 1, 1);

    DRAW_LINE(0, 0, 0);
    DRAW_LINE(0, 0, 1);

    DRAW_LINE(1, 1, 0);
    DRAW_LINE(1, 1, 1);

    DRAW_LINE(0, 1, 0);
    DRAW_LINE(0, 1, 1);

    DRAW_LINE(1, 0, 0);
    DRAW_LINE(1, 0, 1);
#undef DRAW_FACE

    glEnd();

    glPopMatrix();

    glLineWidth(1.0);
  }
} // Block
