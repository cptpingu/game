#include "ConfigManager.hh"
#include "Opengl.hh"
#include <SDL/SDL.h>
#include <iostream>

#include "Game.hh"

#ifdef _WIN32
# define MAIN int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
#else
# define MAIN int main(int, char**)
#endif

namespace
{
  void stop()
  {
    SDL_Quit();
  }
} // namespace

MAIN
{
  ConfigManager& config = ConfigManager::getInstance();
  unsigned int width = config["window_width"];
  unsigned int height = config["window_height"];

  SDL_Init(SDL_INIT_VIDEO);
  atexit(stop);

  SDL_WM_SetCaption("SDL GL Application", 0);
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  if (config["fullscreen"])
  {
    initFullScreen(width, height);
    config.set("window_width", width);
    config.set("window_height", height);
  }

  if (!initExtensions())
  {
    SDL_Quit();
    return 1;
  }

  Game game;
  if (!game.load())
    return 1;
  game.play();

  return 0;
}
