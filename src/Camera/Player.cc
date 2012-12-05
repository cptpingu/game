#include "Player.hh"
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
  Player::Player()
    : super(),
      _heightBeforeJump(0),
      _isJumping(false)
  {
  }

  Player::~Player()
  {
  }

  void
  Player::fall(double speed, unsigned int timestep)
  {
    if (_position._z <= 0)
      _position._z = 0;
    else
      _position._z -= speed * timestep;
    _isJumping = false;
  }

  bool
  Player::jump(bool jumping, double speed, unsigned int timestep)
  {
    if (!jumping)
      return false;

    if (!_isJumping)
    {
      _heightBeforeJump = 0;
      _isJumping = true;
      return true;
    }
    int nextHeight = _position._z + speed * timestep;
    if (nextHeight - _heightBeforeJump < 2500)
    {
      _position._z = nextHeight;
      return true;
    }

    return false;
  }

  void
  Player::animate(Uint32 timestep)
  {
    ConfigManager& config = ConfigManager::getInstance();
    InputManager& input = InputManager::getInstance();

    const double speed = config["speed"] / 1000.0;
    const double realspeed = input.isPressed("boost") ? 10 * speed : speed;
    if (input.isPressed("forward"))
      _position += Core::Vector3D(_forward._x, _forward._y, 0) * (realspeed * timestep);
    if (input.isPressed("backward"))
      _position -= Core::Vector3D(_forward._x, _forward._y, 0) * (realspeed * timestep);
    if (input.isPressed("strafe_left"))
      _position += Core::Vector3D(_left._x, _left._y, 0) * (realspeed * timestep);
    if (input.isPressed("strafe_right"))
      _position -= Core::Vector3D(_left._x, _left._y, 0) * (realspeed * timestep);

    if (!jump(input.isPressed("jump"), speed, timestep))
      fall(speed, timestep);


    if (input.xrel() || input.yrel())
    {
      const int sensivity = config["sensivity"] / 10;
      const int invert = config["invert_mouse"] ? - 1 : 1;
      _theta -= input.xrel() * sensivity;
      _phi -= input.yrel() * sensivity * invert;
      VectorsFromAngles();
    }
    else
      _target = _position + _forward;
  }

  std::pair<Block::Basic*, Block::FaceType>
  Player::picking(const Map& map, const Drawer& drawer) const
  {
    ConfigManager& config = ConfigManager::getInstance();
    return super::picking(map, drawer, config["window_width"] / 2, config["window_height"] / 2);
  }
} // Camera
