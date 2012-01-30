#include "Opengl.hh"
#include <SDL/SDL.h>

#include <cstdlib>
#include <iostream>
#include <time.h>

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
  srand(time(0));
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

  // MapWriter Chocopops;
  // Chocopops.Debut();
  // Chocopops.Sol(100);
  // Chocopops.Building(Vector3D(1,1,1), 5, 0, 5);
  Game game;
  if (!game.load())
    return 1;
  game.play();

  return 0;
}
