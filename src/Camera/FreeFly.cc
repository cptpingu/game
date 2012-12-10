#include "FreeFly.hh"
#include "../IdManager.hh"
#include "../ConfigManager.hh"
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
  FreeFly::FreeFly()
    : _timeBeforeStoppingVerticalMotion(0),
      _verticalMotionActive(false),
      _verticalMotionDirection(0)
  {
  }

  FreeFly::~FreeFly()
  {
  }

  void
  FreeFly::animate(unsigned int timestep)
  {
    ConfigManager& config = ConfigManager::getInstance();
    InputManager& input = InputManager::getInstance();

    const double speed = config["speed"] / 1000.0;
    const double realspeed = input.isPressed("boost") ? 10 * speed : speed;
    if (input.isPressed("forward"))
      _position += _forward * (realspeed * timestep);
    if (input.isPressed("backward"))
      _position -= _forward * (realspeed * timestep);
    if (input.isPressed("strafe_left"))
      _position += _left * (realspeed * timestep);
    if (input.isPressed("strafe_right"))
      _position -= _left * (realspeed * timestep);
    if ((input.isPressed("fly_down") || input.isPressed("fly_up")) && !_verticalMotionActive)
    {
      _verticalMotionActive = true;
      _verticalMotionDirection = input.isPressed("fly_up") ? 1 : -1;
      _timeBeforeStoppingVerticalMotion = 250;
    }

    if (_verticalMotionActive)
    {
      if (timestep > _timeBeforeStoppingVerticalMotion)
        _verticalMotionActive = false;
      else
        _timeBeforeStoppingVerticalMotion -= timestep;
      _position += Core::Vector3D(0, 0, _verticalMotionDirection * realspeed * timestep);
    }

    if (input.xrel() || input.yrel())
    {
      const int sensitivity = config["sensitivity"] / 10;
      const int invert = config["invert_mouse"] ? - 1 : 1;
      _theta -= input.xrel() * sensitivity;
      _phi -= input.yrel() * sensitivity * invert;
      vectorsFromAngles();
    }
    else
      _target = _position + _forward;
  }

  std::pair<Block::Basic*, Block::FaceType>
  FreeFly::picking(const Map& map, const Drawer& drawer) const
  {
    ConfigManager& config = ConfigManager::getInstance();
    return super::picking(map, drawer, config["window_width"] / 2, config["window_height"] / 2);
  }
} // Camera
