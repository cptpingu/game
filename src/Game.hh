#ifndef GAME_HH_
# define GAME_HH_

#include "Opengl.hh"
#include <SDL/SDL.h>

#include <cstdlib>
#include <iostream>
#include "Map.hh"
#include "MapWriter.hh"
#include "TextureManager.hh"
#include "architecte.h"

#include <time.h>
#include "GLUtils.hh"
#include "FreeFlyCamera.hh"
#include "Drawer.hh"
#include "ImageFile.hh"

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
  void drawGL();

private:
  FreeFlyCamera _camera;
  Map           _map;
  Drawer        _drawer;
  Architecte    _architecte;
};

#endif /! *GAME_HH_ */
