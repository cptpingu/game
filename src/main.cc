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
  unsigned int width = Game::WINDOW_WIDTH;
  unsigned int height = Game::WINDOW_HEIGHT;

  SDL_Init(SDL_INIT_VIDEO);
  atexit(stop);

  SDL_WM_SetCaption("SDL GL Application", 0);
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  //initFullScreen(&width, &height);

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
