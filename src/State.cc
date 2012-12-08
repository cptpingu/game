#include "State.hh"
#include "Camera/FreeFly.hh"
#include "Camera/Player.hh"
#include "Core/Assert.hh"

State::State(const Map& map)
  : _map(map), _mode(FreeFly), _camera(new Camera::FreeFly)
{
}

State::~State()
{
  delete _camera;
}

void
State::changeState(Mode state)
{
  Camera::Basic* old = _camera;
  switch (state)
  {
    case FreeFly:
      _camera = new Camera::FreeFly;
      break;
    case Player:
      _camera = new Camera::Player(_map);
      break;
    case MainMenu:
    case Inventory:
    default:
      ASSERT_MSG(false, "Unknow message: " << state);
  }
  *_camera = *old;
  delete old;
}

Camera::Basic*
State::getCamera() const
{
  return _camera;
}

// FIXME HUD::Basic* getHUD() const ;
