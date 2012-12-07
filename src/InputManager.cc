#include "InputManager.hh"
#include "ConfigManager.hh"

#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool
InputManager::isPressed(const std::string& name, bool release)
{
  ConfigManager& config = ConfigManager::getInstance();
  auto key_found = _input_states.find(config[name]);
  if (key_found != _input_states.cend())
  {
    bool res = key_found->second;
    if (release)
      key_found->second = false;
    return res;
  }

  auto mouse_found = _input_states.find(config[name] + 1000);
  if (mouse_found != _input_states.cend())
  {
    bool res = mouse_found->second;
    if (release)
      mouse_found->second = false;
    return res;
  }

  return false;
}

void
InputManager::release(const std::string& name)
{
  ConfigManager& config = ConfigManager::getInstance();
  auto key_found = _input_states.find(config[name]);
  if (key_found != _input_states.cend())
  {
    key_found->second = false;
    return;
  }

  auto mouse_found = _input_states.find(config[name] + 1000);
  if (mouse_found != _input_states.cend())
    mouse_found->second = false;
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
  bool anyChange = false;
  _motion_info.xrel = 0;
  _motion_info.yrel = 0;

  _input_states[SDL_BUTTON_WHEELUP + 1000] = false;
  _input_states[SDL_BUTTON_WHEELDOWN + 1000] = false;
  while (SDL_PollEvent(&event))
  {
    anyChange = true;
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
        break;
      case SDL_MOUSEBUTTONUP:
        if (event.button.button != SDL_BUTTON_WHEELUP &&
            event.button.button != SDL_BUTTON_WHEELDOWN)
          _input_states[event.button.button + 1000] = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        _input_states[event.button.button + 1000] = true;
        break;
    }
  }

  return anyChange;
}
