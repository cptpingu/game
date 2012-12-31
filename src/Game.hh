#ifndef GAME_HH_
# define GAME_HH_

# include "Opengl.hh"
# include "Map.hh"
# include "GLUtils.hh"
# include "Drawer.hh"
# include "ImageFile.hh"
# include "State.hh"

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
  void drawGL(const Block::Basic* selectedCoord, const Block::FaceType where, int elapsedTime);
  void showCoord(const Block::Basic* selectedCoord, const Block::FaceType where);
  void drawFPS(int elapsedTime);
  void drawHUD();

private:
  Map    _map;
  Drawer _drawer;
  State  _state;
  Uint32 _fps;
};

#endif /* !GAME_HH_ */
