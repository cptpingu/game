#include "FreeFlyCamera.hh"

#include <cmath>
#include <GL/glu.h>

FreeFlyCamera::FreeFlyCamera(const Vector3D& position)
{
  _position = position;
  _phi = 0;
  _theta = 0;
  VectorsFromAngles();

  _speed = 0.01;
  _sensivity = 0.00002;
  _verticalMotionActive = false;
  _keyconf["forward"] = SDLK_UP;
  _keyconf["backward"] = SDLK_DOWN;
  _keyconf["strafe_left"] = SDLK_LEFT;
  _keyconf["strafe_right"] = SDLK_RIGHT;
  _keyconf["boost"] = SDLK_LSHIFT;
  _keystates[_keyconf["forward"]] = false;
  _keystates[_keyconf["backward"]] = false;
  _keystates[_keyconf["strafe_left"]] = false;
  _keystates[_keyconf["strafe_right"]] = false;
  _keystates[_keyconf["boost"]] = false;

  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
}

FreeFlyCamera::~FreeFlyCamera()
{
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
}

void FreeFlyCamera::OnMouseMotion(const SDL_MouseMotionEvent& event)
{
  _theta -= event.xrel * _sensivity;
  _phi -= event.yrel * _sensivity;
  VectorsFromAngles();
}

void FreeFlyCamera::OnMouseButton(const SDL_MouseButtonEvent& event)
{
  //coup de molette vers le haut
  if ((event.button == SDL_BUTTON_WHEELUP)&&(event.type == SDL_MOUSEBUTTONDOWN))
  {
    _verticalMotionActive = true;
    _timeBeforeStoppingVerticalMotion = 250;
    _verticalMotionDirection = 1;

  }
  //coup de molette vers le bas
  else if ((event.button == SDL_BUTTON_WHEELDOWN)&&(event.type == SDL_MOUSEBUTTONDOWN))
  {
    _verticalMotionActive = true;
    _timeBeforeStoppingVerticalMotion = 250;
    _verticalMotionDirection = -1;
  }
}

void FreeFlyCamera::OnKeyboard(const SDL_KeyboardEvent& event)
{
  for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end(); ++it)
  {
    if (event.keysym.sym == it->first)
    {
      it->second = (event.type == SDL_KEYDOWN);
      break;
    }
  }
}

void FreeFlyCamera::animate(Uint32 timestep)
{
  double realspeed = _keystates[_keyconf["boost"]] ? 10 * _speed : _speed;
  if (_keystates[_keyconf["forward"]])
    _position += _forward * (realspeed * timestep);
  if (_keystates[_keyconf["backward"]])
    _position -= _forward * (realspeed * timestep);
  if (_keystates[_keyconf["strafe_left"]])
    _position += _left * (realspeed * timestep);
  if (_keystates[_keyconf["strafe_right"]])
    _position -= _left * (realspeed * timestep);
  if (_verticalMotionActive)
  {
    if (timestep > _timeBeforeStoppingVerticalMotion)
      _verticalMotionActive = false;
    else
      _timeBeforeStoppingVerticalMotion -= timestep;
    _position += Vector3D(0, 0, _verticalMotionDirection * realspeed * timestep);
  }
  _target = _position + _forward;

}

void FreeFlyCamera::setSpeed(double speed)
{
  _speed = speed;
}

void FreeFlyCamera::setSensivity(double sensivity)
{
  _sensivity = sensivity;
}

void FreeFlyCamera::setPosition(const Vector3D & position)
{
  _position = position;
  _target = _position + _forward;
}

void FreeFlyCamera::VectorsFromAngles()
{
  static const Vector3D up(0, 0, 1);
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

void FreeFlyCamera::look()
{
  gluLookAt(_position._x, _position._y, _position._z,
	    _target._x, _target._y, _target._z,
	    0, 0, 1);
}
