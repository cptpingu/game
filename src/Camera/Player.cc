#include "Player.hh"
#include "../IdManager.hh"
#include "../ConfigManager.hh"
#include "../InputManager.hh"
#include "../Opengl.hh"
#include "../Chunk.hh"
#include "../Map.hh"
#include "../Core/Assert.hh"

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

  Core::Vector3D
  Player::collide(const Core::Vector3D& next) const
  {
    ASSERT_MSG(!_map.findBlock(_position._x / Block::SIZE,
                               _position._y / Block::SIZE, _position._z / Block::SIZE),
               "Current pos is in a cube: (" << _position._x / Block::SIZE << ", "
               << _position._y / Block::SIZE << ", " << _position._z / Block::SIZE << ")");

    Core::Container3D<int> blockPos;
    blockPos._x = next._x / Block::SIZE;
    blockPos._y = next._y / Block::SIZE;
    blockPos._z = next._z / Block::SIZE;

    Block::Basic* nextPos = _map.findBlock(blockPos);
    if (!nextPos)
      return next;
    return nextPos->collision(_position, next);
  }

  void
  Player::fall(double speed, unsigned int timestep, Core::Vector3D& nextPos)
  {
    _isFalling = true;
    _isJumping  = false;

    Core::Container3D<int> tmp;
    tmp._x = nextPos._x / Block::SIZE;
    tmp._y = nextPos._y / Block::SIZE;
    tmp._z = nextPos._z / Block::SIZE;
    Block::Basic* blockPos = _map.findBlock(tmp);

    if (!blockPos)
    {
      if (nextPos._z <= 0)
      {
        nextPos._z = 0;
        _isFalling = false;
      }
      else
        nextPos._z -= speed * timestep;
      return;
    }

    nextPos._z = blockPos->_z;
    _isFalling = false;
  }

  bool
  Player::jump(bool jumping, double speed,
               unsigned int timestep, Core::Vector3D& nextPos)
  {
    if (!jumping)
    {
      _isJumping  = false;
      return false;
    }
    if (!_isJumping)
      _heightBeforeJump = nextPos._z;

    double nextHeight = nextPos._z + speed * timestep;
    if (nextHeight - _heightBeforeJump < 6)
    {
      nextPos._z = nextHeight;
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
      jump(input.isPressed("jump"), speed, timestep, nextPos);
    if (!_isJumping)
      fall(speed, timestep, nextPos);

    _position = collide(nextPos);

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
