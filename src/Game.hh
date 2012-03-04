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

class Game
{
public:
  static const unsigned int FPS = 50;
  static const unsigned int WINDOW_WIDTH  = 640;
  static const unsigned int WINDOW_HEIGHT = 480;

public:
  bool load();
  void play();

private:
  void loadtextures();
  void loadShaders();
  void drawGL();
  void showCoord();

private:
  FreeFlyCamera  _camera;
  Map            _map;
  Drawer         _drawer;
};

#endif /* !GAME_HH_ */
