#include "ConfigManager.hh"

#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

namespace
{
  std::string trim(const std::string& s)
  {
    const int size = s.size();
    int start = 0;
    while (start < size && s[start] == ' ')
      ++start;
    int stop = size - 1;
    while (stop > 0 && s[stop] == ' ')
      --stop;

    return s.substr(start, stop - start + 1);
  }
} // namespace

ConfigManager::ConfigManager()
{
  _bindings["forward"] = SDLK_UP;
  _bindings["backward"] = SDLK_DOWN;
  _bindings["strafe_left"] = SDLK_LEFT;
  _bindings["strafe_right"] = SDLK_RIGHT;
  _bindings["jump"] = SDLK_j;

  _bindings["boost"] = SDLK_RSHIFT;
  _bindings["fly_up"] = SDL_BUTTON_WHEELUP;
  _bindings["fly_down"] = SDL_BUTTON_WHEELDOWN;
  _bindings["insert_block"] = SDLK_g;
  _bindings["remove_block"] = SDLK_f;


  _bindings["wireframe_mode"] = SDLK_w;
  _bindings["normal_mode"] = SDLK_x;
  _bindings["take_screenshot"] = SDLK_p;
  _bindings["quit"] = SDLK_ESCAPE;

  _bindings["invert_mouse"] = 1;

  _bindings["speed"] = 10;
  _bindings["sensivity"] = 10;
  _bindings["fps"] = 50;
  _bindings["window_width"] = 640;
  _bindings["window_height"] = 480;
  _bindings["fullscreen"] = 0;

    _bindings["height_jump"] = 250;
}

ConfigManager::~ConfigManager()
{
}

bool
ConfigManager::load(const std::string& filename)
{
  bool change = false;
  std::ifstream file(filename.c_str());
  if (!file)
    return change;

  std::string line;
  while (std::getline(file, line))
  {
    std::string res[2];
    int i = 0;
    std::string word;

    std::istringstream buff(line);
    while (std::getline(buff, word, '=') && i < 2)
      res[i++] = word;

    _bindings[trim(res[0])] = atoi(res[1].c_str());
    change = true;
  }

  return change;
}

void
ConfigManager::dump(std::ostream& out) const
{
  auto end = _bindings.cend();
  for (auto it = _bindings.cbegin(); it != end; ++it)
    out << it->first << " = " << it->second << std::endl;
}

int
ConfigManager::operator[](const std::string& name) const
{
  auto found = _bindings.find(name);
  assert(found != _bindings.end());
  return found->second;
}

void
ConfigManager::set(const std::string& name, int value)
{
  _bindings[name] = value;
}
