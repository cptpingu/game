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
  }
} // Block
