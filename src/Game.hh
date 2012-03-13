#ifndef GAME_HH_
# define GAME_HH_

# include "Opengl.hh"
# include "Map.hh"
# include "GLUtils.hh"
# include "FreeFlyCamera.hh"
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
  static const unsigned int FPS = 50;
  static const unsigned int WINDOW_WIDTH  = 640;
  static const unsigned int WINDOW_HEIGHT = 480;

public:
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
  void drawGL(const Chunk::Coord* selectedCoord);
  void showCoord(const Chunk::Coord* selectedCoord);

private:
  FreeFlyCamera  _camera;
  Map            _map;
  Drawer         _drawer;
};

#endif /* !GAME_HH_ */
