#include "InputManager.hh"
#include "ConfigManager.hh"

#include <cassert>
#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool
InputManager::key(const std::string& name) const
{
  ConfigManager& config = ConfigManager::getInstance();
  auto found = _input_states.find(config[name]);
  return found != _input_states.cend() && found->second;
}

bool
InputManager::mouse(const std::string& name) const
{
  ConfigManager& config = ConfigManager::getInstance();
  auto found = _mouse_states.find(config[name]);
  return found != _mouse_states.cend() && found->second;
}

unsigned int
InputManager::x() const
{
  return _motion_info.x;
}

unsigned int
InputManager::y() const
{
  return _motion_info.y;
}

int
InputManager::xrel() const
{
  return _motion_info.xrel;
}

int
InputManager::yrel() const
{
  return _motion_info.yrel;
}

bool
InputManager::handleInput()
{
  SDL_Event event;
  bool mouseChange = false;
//  _motion_info.xrel = 0;
//  _motion_info.yrel = 0;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_KEYDOWN:
        _input_states[event.key.keysym.sym] = true;
        break;
      case SDL_KEYUP:
        _input_states[event.key.keysym.sym] = false;
        break;
      case SDL_MOUSEMOTION:
        _motion_info = event.motion;
        mouseChange = true;
        break;
      case SDL_MOUSEBUTTONUP:
        _mouse_states[SDL_BUTTON_LEFT] = false;
        _mouse_states[SDL_BUTTON_RIGHT] = false;
        _mouse_states[SDL_BUTTON_WHEELUP] = false;
        _mouse_states[SDL_BUTTON_WHEELDOWN] = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        _mouse_states[SDL_BUTTON_LEFT] = true;
        _mouse_states[SDL_BUTTON_RIGHT] = true;
        _mouse_states[SDL_BUTTON_WHEELUP] = true;
        _mouse_states[SDL_BUTTON_WHEELDOWN] = true;
        break;
    }
  }

  std::cout << "Left:  " << std::boolalpha << _mouse_states[SDL_BUTTON_LEFT] << std::endl
            << "Right: " << std::boolalpha << _mouse_states[SDL_BUTTON_RIGHT] << std::endl
            << "Up:    " << std::boolalpha << _mouse_states[SDL_BUTTON_WHEELUP] << std::endl
            << "Down:  " << std::boolalpha << _mouse_states[SDL_BUTTON_WHEELDOWN] << std::endl;

  return mouseChange;
}
