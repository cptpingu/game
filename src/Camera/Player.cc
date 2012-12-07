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
  Player::Player(const Map& map)
    : super(),
      _map(map),
      _heightBeforeJump(0),
      _isJumping(false),
      _isFalling(false)
  {
  }

  Player::~Player()
  {
  }

  bool
  Player::collide(const Core::Vector3D& pos) const
  {
    //static const int playerSize = 1;
    assert(!_map.findBlock(_position._x, _position._y, 0 * _position._z));
    Core::Container3D<int> blockPos;
    blockPos._x = pos._x / Block::SIZE;
    blockPos._y = pos._y / Block::SIZE;
    blockPos._z = 0;

    Block::Basic* nextPos = _map.findBlock(blockPos);
    if (nextPos)
      return true;

    return false;
    //if (pos._x + playerSize > )
  }

  void
  Player::fall(double speed, unsigned int timestep)
  {
    _isFalling = true;
    _isJumping  = false;
    if (_position._z <= 0)
      _position._z = 0;
    else
      _position._z -= speed * timestep;
  }

  bool
  Player::jump(bool jumping, double speed, unsigned int timestep)
  {
    if (!jumping)
    {
      _isJumping  = false;
      return false;
    }

    if (!_isJumping)
      _heightBeforeJump = _position._z;

    int nextHeight = _position._z + speed * timestep;
    if (nextHeight - _heightBeforeJump < 2500)
    {
      _position._z = nextHeight;
      _isJumping  = true;
      _isFalling = false;
      return true;
    }

    _isJumping  = false;
    _isFalling = true;

    return false;
  }

  void
  Player::animate(unsigned int timestep)
  {
    ConfigManager& config = ConfigManager::getInstance();
    InputManager& input = InputManager::getInstance();

    Core::Vector3D nextPos = _position;
    const double speed = config["speed"] / 1000.0;
    const double realspeed = input.isPressed("boost") ? 10 * speed : speed;
    const double forwardComp = fabs(_forward._x) + fabs(_forward._y);
    const double leftComp = fabs(_left._x) + fabs(_left._y);
    const double forwardX = (_forward._x / forwardComp) * (realspeed * timestep);
    const double forwardY = (_forward._y / forwardComp) * (realspeed * timestep);
    const double leftX = (_left._x / leftComp) * (realspeed * timestep);
    const double leftY = (_left._y / leftComp) * (realspeed * timestep);

    if (input.isPressed("forward"))
      nextPos += Core::Vector3D(forwardX, forwardY, 0);
    if (input.isPressed("backward"))
      nextPos -= Core::Vector3D(forwardX, forwardY, 0);
    if (input.isPressed("strafe_left"))
      nextPos += Core::Vector3D(leftX, leftY, 0);
    if (input.isPressed("strafe_right"))
      nextPos -= Core::Vector3D(leftX, leftY, 0);

    if (!_isFalling)
      jump(input.isPressed("jump"), speed, timestep);
    if (!_isJumping)
      fall(speed, timestep);

    if (!collide(nextPos))
      _position = nextPos;

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
  Player::picking(const Map& map, const Drawer& drawer) const
  {
    ConfigManager& config = ConfigManager::getInstance();
    return super::picking(map, drawer, config["window_width"] / 2, config["window_height"] / 2);
  }
} // Camera
