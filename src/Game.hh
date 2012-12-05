#ifndef GAME_HH_
# define GAME_HH_

# include "Opengl.hh"
# include "Map.hh"
# include "GLUtils.hh"
# include "Camera/BasicCamera.hh"
# include "Drawer.hh"
# include "ImageFile.hh"

# include <SDL/SDL.h>
# include <iostream>

/*!
** @class Game
**
** This class contains a complete instance of all the game.
*/
class Game
{
public:
  Game();
  ~Game();

  /*!
  ** Load all resources needed for the game, and initialize options.
  */
  bool load();

  /*!
  ** Play the game.
  ** This function is executed at every frame of the game.
  */
  void play();

private:
  void loadtextures();
  void loadShaders();
  void drawGL(const Chunk::Coord* selectedCoord, int fpsFromSDL);
  void showCoord(const Chunk::Coord* selectedCoord);
  void drawFPS(int fpsFromSDL);
  void drawHUD();

private:
  Camera::Basic* _camera;
  Map            _map;
  Drawer         _drawer;
};

#endif /* !GAME_HH_ */
