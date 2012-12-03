#include "FreeFly.hh"
#include "../IdManager.hh"
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
    _position = Core::Vector3D(0,0,0);
    _phi = 0;
    _theta = 0;
    VectorsFromAngles();

    _speed = 0.01;
    _sensivity = 0.02;
    _verticalMotionActive = false;
    _keyconf["forward"] = SDLK_UP;
    _keyconf["backward"] = SDLK_DOWN;
    _keyconf["strafe_left"] = SDLK_LEFT;
    _keyconf["strafe_right"] = SDLK_RIGHT;
    _keyconf["boost"] = SDLK_RSHIFT;
    _keystates[_keyconf["forward"]] = false;
    _keystates[_keyconf["backward"]] = false;
    _keystates[_keyconf["strafe_left"]] = false;
    _keystates[_keyconf["strafe_right"]] = false;
    _keystates[_keyconf["boost"]] = false;

    SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);
  }

  FreeFly::~FreeFly()
  {
    SDL_WM_GrabInput(SDL_GRAB_OFF);
    SDL_ShowCursor(SDL_ENABLE);
  }

  void
  FreeFly::OnMouseButton(const SDL_MouseButtonEvent& event)
  {
    super::OnMouseButton(event);
    if(event.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN )
    {
      std::cout << "KICK OUT" << std::endl;
    }
  }

  void
  FreeFly::OnKeyboard(const SDL_KeyboardEvent& event)
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

  void
  FreeFly::animate(Uint32 timestep)
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
      _position += Core::Vector3D(0, 0, _verticalMotionDirection * realspeed * timestep);
    }
    _target = _position + _forward;
  }
} // namespace
