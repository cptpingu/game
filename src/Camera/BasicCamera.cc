#include "BasicCamera.hh"
#include "../IdManager.hh"
#include "../InputManager.hh"
#include "../Opengl.hh"
#include "../Chunk.hh"
#include "../Map.hh"

#include <cmath>
#include <limits>
#include <iostream>

#ifndef M_PI
# define M_PI 3.14159265
#endif

namespace Camera
{
  Basic::Basic()
  {
    _position = Core::Vector3D(0, 0, 0);
    _target = Core::Vector3D(1, 1, 0);
    _phi = 0;
    _theta = 0;
    vectorsFromAngles();
  }

  Basic::~Basic()
  {
  }

  Basic&
  Basic::operator=(const Basic& camera)
  {
    _position = camera._position;
    _target = camera._target;
    _forward = camera._forward;
    _left = camera._left;
    _theta = camera._theta;
    _phi = camera._phi;

    return *this;
  }

  void
  Basic::setPosition(const Core::Vector3D& position)
  {
    _position = position;
    _target = _position + _forward;
  }

  void
  Basic::vectorsFromAngles()
  {
    static const Core::Vector3D up(0, 0, 1);
    if (_phi > 89)
      _phi = 89;
    else if (_phi < -89)
      _phi = -89;

    double r_temp = cos(_phi * M_PI / 180);

    _forward._z = sin(_phi * M_PI / 180);
    _forward._x = r_temp * cos(_theta * M_PI / 180);
    _forward._y = r_temp * sin(_theta * M_PI / 180);

    _left = up.crossProduct(_forward);
    _left.normalize();

    _target = _position + _forward;
  }

  void
  Basic::look()
  {
    gluLookAt(_position._x, _position._y, _position._z,
              _target._x, _target._y, _target._z,
              0, 0, 1);
  }

  Core::Vector3D
  Basic::getCurrentPosition() const
  {
    return _position;
  }

  Core::Vector3D
  Basic::getCurrentLook() const
  {
    return _target;
  }

  std::pair<Block::Basic*, Block::FaceType>
  Basic::picking(const Map& map, const Drawer& drawer,
                 int mouseX, int mouseY) const
  {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawer.drawPickingBox(map);

    unsigned char pixel[3];
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(mouseX, viewport[3] - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    const Block::id_type id(pixel[0], pixel[1], pixel[2]);
    Block::Basic* block = IdManager::getInstance().getBlockFromId(id);
    return std::make_pair(block, !block ? Block::none : Block::FaceType(id._z));
  }
} // Camera
