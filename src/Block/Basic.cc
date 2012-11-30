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

  void
  Basic::resetHighlight()
  {
    auto end = _highlights.end();
    for (auto it = _highlights.begin(); it != end; ++it)
      *it = false;
  }

  void
  Basic::draw() const
  {
    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable(getShaderName());
    specificDraw();
    shaders.disable();
  }
} // Block
