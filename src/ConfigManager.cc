#include "ConfigManager.hh"

#include <fstream>
#include <sstream>
#include <string>
#include "Core/Assert.hh"

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
  _bindings["insert_block"] = SDL_BUTTON_LEFT;
  _bindings["remove_block"] = SDL_BUTTON_RIGHT;

  _bindings["wireframe_mode"] = SDLK_w;
  _bindings["normal_mode"] = SDLK_x;
  _bindings["take_screenshot"] = SDLK_p;
  _bindings["quit"] = SDLK_ESCAPE;

  _bindings["freefly_state"] = SDLK_F1;
  _bindings["player_state"] = SDLK_F2;


  _bindings["invert_mouse"] = 1;

  _bindings["speed"] = 5;
  _bindings["sensitivity"] = 10;
  _bindings["fps"] = 60;
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
  ASSERT_MSG(found != _bindings.end(),
             "Option \"" << name << "\" not found in configuration!");
  return found->second;
}

void
ConfigManager::set(const std::string& name, int value)
{
  _bindings[name] = value;
}
