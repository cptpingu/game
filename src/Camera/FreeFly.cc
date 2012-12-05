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
  {
  }

  FreeFly::~FreeFly()
  {
  }

  void
  FreeFly::animate(Uint32 timestep)
  {
    ConfigManager& config = ConfigManager::getInstance();
    InputManager& input = InputManager::getInstance();

    const double speed = config["speed"] / 1000.0;
    const double realspeed = input.key("boost") ? 10 * speed : speed;
    if (input.key("forward"))
      _position += _forward * (realspeed * timestep);
    if (input.key("backward"))
      _position -= _forward * (realspeed * timestep);
    if (input.key("strafe_left"))
      _position += _left * (realspeed * timestep);
    if (input.key("strafe_right"))
      _position -= _left * (realspeed * timestep);
    if ((input.mouse("fly_down") || input.mouse("fly_up")) && !_verticalMotionActive)
    {
      _verticalMotionActive = true;
      _verticalMotionDirection = input.mouse("fly_up") ? 1 : -1;
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
      _theta -= input.xrel(); //* _sensivity;
      _phi -= input.yrel(); //* _sensivity;
      VectorsFromAngles();
    }
    else
      _target = _position + _forward;
  }
} // Camera
