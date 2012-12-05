#include "ConfigManager.hh"

#include <cassert>

ConfigManager::ConfigManager()
{
  _bindings["forward"] = SDLK_UP;
  _bindings["backward"] = SDLK_DOWN;
  _bindings["strafe_left"] = SDLK_LEFT;
  _bindings["strafe_right"] = SDLK_RIGHT;
  _bindings["boost"] = SDLK_RSHIFT;
  _bindings["speed"] = 10;
  _bindings["sensivity"] = 20;
  _bindings["fly_up"] = SDL_BUTTON_WHEELUP;
  _bindings["fly_down"] = SDL_BUTTON_WHEELDOWN;

  _bindings["insert_block"] = SDLK_g;
  _bindings["remove_block"] = SDLK_f;

  _bindings["wireframe_mode"] = SDLK_w;
  _bindings["normal_mode"] = SDLK_x;
  _bindings["take_screenshot"] = SDLK_p;

  _bindings["quit"] = SDLK_ESCAPE;

  _bindings["invert_mouse"] = 1;
}

ConfigManager::~ConfigManager()
{
}

int
ConfigManager::operator[](const std::string& name) const
{
  auto found = _bindings.find(name);
  assert(found != _bindings.end());
  return found->second;
}
