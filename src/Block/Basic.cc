#include "Basic.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include "../IdManager.hh"
#include "../Core/Random.hh"
#include "../Model/StaticPickingBoxModel.hh"

#include <iostream>

namespace Block
{
  Basic::Basic(int x, int y, int z)
    : super(x, y, z),
      _highlights(),
      _isHighlighted(false),
      _pickingVBOId(0),
      _vboId(0),
      _pickingModelState(0),
      _modelState(0)
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

  unsigned int
  Basic::getState() const
  {
    return _modelState;
  }

  bool
  Basic::isNullIndex(int index) const
  {
    return specificIsNullIndex(index);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(_pickingColors), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    sizeof(_pickingColors),
                    _pickingColors);
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
    _isHighlighted = isHighlighted(Block::up) || isHighlighted(Block::down) ||
        isHighlighted(Block::left) || isHighlighted(Block::right) ||
        isHighlighted(Block::front) || isHighlighted(Block::back);
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
    return _isHighlighted;
  }

  void
  Basic::resetHighlight()
  {
    _isHighlighted = false;
    auto end = _highlights.end();
    for (auto it = _highlights.begin(); it != end; ++it)
      *it = false;
  }

  void
  Basic::draw(const Model::MemoryPiece& mem) const
  {
    specificDraw(mem);
    //drawPickingBox(mem);
    if (isHighlight())
      selectionDraw();
  }

  void
  Basic::changeState(const NeighbourMatrix& neighbours)
  {
#define CLEAR(FROM) states[FROM] = false
#define CLEAR_RANGE(FROM, TO) for (int i = FROM; i <= TO; ++i) states[i] = false

    std::array<bool, 64> states;
    auto end = states.end();
    for (auto it = states.begin(); it != end; ++it)
      *it = true;
    if (neighbours(0, 0, 1)) // up
    {
      CLEAR(0);
      CLEAR_RANGE(2, 6);
      CLEAR_RANGE(12, 21);
      CLEAR_RANGE(32, 41);
      CLEAR_RANGE(52, 56);
      CLEAR(62);
    }
    else
    {
      CLEAR(1);
      CLEAR_RANGE(7, 11);
      CLEAR_RANGE(22, 31);
      CLEAR_RANGE(42, 51);
      CLEAR_RANGE(57, 61);
      CLEAR(63);
    }

    if (neighbours(0, 0, -1)) // down
    {
      CLEAR_RANGE(0, 5);
      CLEAR_RANGE(7, 10);
      CLEAR_RANGE(12, 14);
      CLEAR_RANGE(16, 17);
      CLEAR(19);
      CLEAR_RANGE(22, 24);
      CLEAR_RANGE(26, 27);
      CLEAR(29);
      CLEAR_RANGE(32, 33);
      CLEAR(35);
      CLEAR(38);
      CLEAR_RANGE(42, 43);
      CLEAR(45);
      CLEAR(48);
      CLEAR(52);
      CLEAR(57);
    }
    else
    {
      CLEAR(6);
      CLEAR(11);
      CLEAR(15);
      CLEAR(18);
      CLEAR_RANGE(20, 21);
      CLEAR(25);
      CLEAR(28);
      CLEAR_RANGE(30, 31);
      CLEAR(34);
      CLEAR_RANGE(36, 37);
      CLEAR_RANGE(39, 41);
      CLEAR(44);
      CLEAR_RANGE(46, 47);
      CLEAR_RANGE(49, 51);
      CLEAR_RANGE(53, 56);
      CLEAR_RANGE(58, 63);
    }

    if (neighbours(0, -1, 0)) // front
    {
      CLEAR_RANGE(0, 4);
      CLEAR_RANGE(6, 9);
      CLEAR_RANGE(11, 13);
      CLEAR_RANGE(15, 16);
      CLEAR(18);
      CLEAR(20);
      CLEAR_RANGE(22, 23);
      CLEAR_RANGE(25, 26);
      CLEAR(28);
      CLEAR(30);
      CLEAR(32);
      CLEAR(34);
      CLEAR(36);
      CLEAR(39);
      CLEAR(42);
      CLEAR(44);
      CLEAR(46);
      CLEAR(49);
      CLEAR(53);
      CLEAR(58);
    }
    else
    {
      CLEAR(5);
      CLEAR(10);
      CLEAR(14);
      CLEAR(17);
      CLEAR(19);
      CLEAR(21);
      CLEAR(24);
      CLEAR(27);
      CLEAR(29);
      CLEAR(31);
      CLEAR(33);
      CLEAR(35);
      CLEAR_RANGE(37, 38);
      CLEAR_RANGE(40, 41);
      CLEAR(43);
      CLEAR(45);
      CLEAR_RANGE(47, 48);
      CLEAR_RANGE(50, 52);
      CLEAR_RANGE(54, 57);
      CLEAR_RANGE(59, 63);
    }

    if (neighbours(0, 1, 0)) // back
    {
      CLEAR_RANGE(0, 2);
      CLEAR_RANGE(4, 7);
      CLEAR_RANGE(9, 11);
      CLEAR_RANGE(13, 15);
      CLEAR_RANGE(19, 21);
      CLEAR_RANGE(23, 25);
      CLEAR_RANGE(29, 31);
      CLEAR_RANGE(35, 37);
      CLEAR(41);
      CLEAR_RANGE(45, 47);
      CLEAR(51);
      CLEAR(55);
      CLEAR(60);
    }
    else
    {
      CLEAR(3);
      CLEAR(8);
      CLEAR(12);
      CLEAR_RANGE(16, 18);
      CLEAR(22);
      CLEAR_RANGE(26, 28);
      CLEAR_RANGE(32, 34);
      CLEAR_RANGE(38, 40);
      CLEAR_RANGE(42, 44);
      CLEAR_RANGE(48, 50);
      CLEAR_RANGE(52, 54);
      CLEAR_RANGE(56, 59);
      CLEAR_RANGE(61, 63);
    }

    if (neighbours(-1, 0, 0)) // left
    {
      CLEAR_RANGE(0, 3);
      CLEAR_RANGE(5, 8);
      CLEAR_RANGE(10, 12);
      CLEAR_RANGE(14, 15);
      CLEAR_RANGE(17, 18);
      CLEAR_RANGE(21, 22);
      CLEAR_RANGE(24, 25);
      CLEAR_RANGE(27, 28);
      CLEAR(31);
      CLEAR_RANGE(33, 34);
      CLEAR(37);
      CLEAR(40);
      CLEAR_RANGE(43, 44);
      CLEAR(47);
      CLEAR(50);
      CLEAR(54);
      CLEAR(59);
    }
    else
    {
      CLEAR(4);
      CLEAR(9);
      CLEAR(13);
      CLEAR(16);
      CLEAR_RANGE(19, 20);
      CLEAR(23);
      CLEAR(26);
      CLEAR_RANGE(29, 30);
      CLEAR(32);
      CLEAR_RANGE(35, 36);
      CLEAR_RANGE(38, 39);
      CLEAR_RANGE(41, 42);
      CLEAR_RANGE(45, 46);
      CLEAR_RANGE(48, 49);
      CLEAR_RANGE(51, 53);
      CLEAR_RANGE(55, 58);
      CLEAR_RANGE(60, 63);
    }

    if (neighbours(1, 0, 0)) // right
    {
      CLEAR_RANGE(0, 1);
      CLEAR_RANGE(3, 6);
      CLEAR_RANGE(8, 11);
      CLEAR_RANGE(16, 21);
      CLEAR_RANGE(26, 31);
      CLEAR_RANGE(38, 41);
      CLEAR_RANGE(48, 51);
      CLEAR(56);
      CLEAR(61);
    }
    else
    {
      CLEAR(2);
      CLEAR(7);
      CLEAR_RANGE(12, 15);
      CLEAR_RANGE(22, 25);
      CLEAR_RANGE(32, 37);
      CLEAR_RANGE(42, 47);
      CLEAR_RANGE(52, 55);
      CLEAR_RANGE(57, 60);
      CLEAR_RANGE(62, 63);
    }

#undef CLEAR_RANGE
#undef CLEAR

    unsigned int state = 0;
    auto it = states.cbegin();
    while (it != end && !*it)
      ++it, ++state;
    ASSERT(it != end);
    _pickingModelState = state;

    specificChangeState(neighbours);
  }

  Core::Vector3D
  Basic::collision(const Core::Vector3D& current, const Core::Vector3D& next) const
  {
    return specificCollision(current, next);
  }

  void
  Basic::drawPickingBox(const Model::MemoryPiece& mem) const
  {
    ASSERT_MSG(_pickingVBOId, "Invalid vertex buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, _pickingVBOId);

    glColorPointer(3, GL_FLOAT, 0, (void*) (0));

    glPushMatrix();
    glTranslatef(_x * Block::SIZE + Block::SIZE / 2,
                 _y * Block::SIZE + Block::SIZE / 2,
                 _z * Block::SIZE + Block::SIZE / 2);
    glDrawElements(GL_TRIANGLES, mem.size, GL_UNSIGNED_BYTE,
                   reinterpret_cast<void*>(mem.from));
    glPopMatrix();
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
