#include "Game.hh"
#include <sstream>

bool
Game::load()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)WINDOW_WIDTH / WINDOW_HEIGHT, 0.001, 1000);

  loadtextures();
/*
  static const std::string filename = "Carte.txt";
  if (!_map.loadBlocks(filename))
  {
    std::cerr << "Unable to load " << filename << std::endl;
    return false;
  }

  static const std::string terrain = "Terrain.txt";
  if (!_map.loadTriangles(terrain))
  {
    std::cerr << "Unable to load " << terrain << std::endl;
    return false;
  }
*/

  Chunk* chunk = new Chunk;
  _architecte.generateRandomGround(*chunk,
                                   Vector3D(-Chunk::SIZE / 2, -Chunk::SIZE / 2, 0),
                                   Chunk::SIZE);
  chunk->meshAllCoord();
  _map.getChunks().insert(Map::chunks_type::value_type(std::make_pair(0, 0), chunk));

  Map::triangles_type tmp2;
  //TEST.Ground(Vector3D (150,0,0),150);
  _architecte.mountain(tmp2, Vector3D (20,10,0), 200,20 );
  _architecte.mergeGround(*chunk, tmp2);
  //TEST.Building(Vector3D(10,10,0), 5, 4, 5);
  //MapWriter Chocopops;
  // Chocopops.Debut();
  //Chocopops.Sol(150);
  //Chocopops.Montagne(Vector3D(30,30,1),30,20);
  //Chocopops.Building(Vector3D(10,10,1), 5, 0, 5);




  return true;
}

void
Game::play()
{
  SDL_Event event;
  const Uint32 time_per_frame = 1000 / FPS;
  Uint32 last_time,current_time,elapsed_time; //for time animation
  Uint32 stop_time; //for frame limit

  last_time = SDL_GetTicks();
  for (;;)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          exit(0);
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
            case SDLK_p:
              takeScreenshot("test.bmp");
              break;
            case SDLK_ESCAPE:
              exit(0);
              break;
            default :
              _camera.OnKeyboard(event.key);
          }
          break;
        case SDL_KEYUP:
          _camera.OnKeyboard(event.key);
          break;
        case SDL_MOUSEMOTION:
          _camera.OnMouseMotion(event.motion);
          break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
          _camera.OnMouseButton(event.button);
          break;
      }
    }

    current_time = SDL_GetTicks();
    elapsed_time = current_time - last_time;
    last_time = current_time;

    _map.lazyChunkLoading(_camera.getCurrentPosition());
    _camera.animate(elapsed_time);

    drawAxis(2);
    drawGL();


    stop_time = SDL_GetTicks();
    if ((stop_time - last_time) < time_per_frame)
      SDL_Delay(time_per_frame - (stop_time - last_time));
  }
}

void
Game::loadtextures()
{
  TextureManager& textures = Singleton<TextureManager>::getInstance();
  //TextureManager& textures = TextureManager::getInstance();

  textures.load("data/images/font.png", "font");
  textures.BuildFont();

  textures.load("data/images/metal091.jpg", "metal");
  textures.load("data/images/rocket_motor.jpg", "rocketMotor");
  textures.load("data/images/rocket_bottom.jpg", "rocketBottom");
  textures.load("data/images/rocket_middle.jpg", "rocketMiddle");
  textures.load("data/images/rocket_top.jpg", "rocketTop");
  //autre texture
  textures.load("data/images/concrete001.jpg", "concrete");
  textures.load("data/images/neige.jpg", "neige");
  textures.load("data/images/floor032.jpg", "floor1");
  textures.load("data/images/brick009.jpg", "brick1");
  textures.load("data/images/wood002.jpg", "wood1");
  textures.load("data/images/wood006.jpg", "wood2");
  //porte
  textures.load("data/images/door009.jpg", "door");
  //pour les caisse
  textures.load("data/images/crate03.jpg", "crate");
  //toit
  textures.load("data/images/roof05.jpg", "roof");
  //fenetre
  textures.load("data/images/window031_alpha.png", "window");
  //Herbe
  textures.load("data/images/veg008.jpg", "veg1");
  //Eau de la piscine
  textures.load("data/images/eau.jpg", "eau");
  // Dalle de la piscine
  textures.load("data/images/floor006b.jpg", "floor2");
  // Fond du puit
  textures.load("data/images/veg010.jpg", "veg2");
  // puit
  textures.load("data/images/brick077.jpg", "brick2");
  textures.load("data/images/test.jpg", "test");
}

void
Game::drawGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  _camera.look();

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);

  // double a=0;
  // int LightPos[4] = {10,10,30,1};
  // int MatSpec [4] = {1,1,1,1};


  // glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
  // glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);


  // glRotated(a,0,1,0);
  // glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
  // a=+1;
  //float Light1Pos[4] = {15.0f, 15.0f, 20.0f, 1.0f};
  // float Light1Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
  // float Light1Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
  // float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  //float Spot1Dir[3] = {0.0f, 0.0f, -1.0f};

  // glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Dif); 	//Et ceux de la lumière
  // glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Spec);
  // glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Amb);
  // glEnable(GL_LIGHTING); 	//Et on allume la lumière
  // glEnable(GL_LIGHT1);
  // glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
  // float Light1Dir[3] = {0.0f, 0.0f, -1.0f};
  // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);

  _drawer.drawMap(_map);
  // glEnable(GL_FOG) ;
  // GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
  // GLint fogmode = GL_LINEAR;//GL_EXP ;
  // glFogi (GL_FOG_MODE, fogmode) ;
  // glFogfv(GL_FOG_COLOR, fogcolor) ;
  // glFogf(GL_FOG_DENSITY, 0.1) ;
  // glFogf(GL_FOG_START, 10.0) ;
  // glFogf(GL_FOG_END, 20.0) ;


  glFrustum( 5,   5,   5,   5,   2,  10);


  // glColor3f(1.0f,1.0f,1.0f);
  // TextureManager& textures = Singleton<TextureManager>::getInstance();
  // glBindTexture(GL_TEXTURE_2D, textures["eau"]);
  // glBegin(GL_QUADS);
  // glTexCoord2f(0,0);
  // glVertex3d(0,0,-2);

  // glTexCoord2f(2,0);
  // glVertex3d(0, 60,-2);

  // glTexCoord2f(2,2);
  // glVertex3d(60,60,-2);

  // glTexCoord2f(0,2);
  // glVertex3d(60,0,-2);
  // glEnd();

  // glColor4f(1.0f,1.0f,1.0f,0.55f);  // alpha 55%
  // // on active la transparence
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA,GL_ONE);


  // glBindTexture(GL_TEXTURE_2D, textures["eau"]);
  // glBegin(GL_QUADS);
  // glTexCoord2f(0,0);
  // glVertex3d(0,0,-2);

  // glTexCoord2f(2,0);
  // glVertex3d(0, 60,-2);

  // glTexCoord2f(2,2);
  // glVertex3d(60,60,-2);

  // glTexCoord2f(0,2);
  // glVertex3d(60,0,-2);
  // glEnd();
  // // désactive transparence
  // glDisable(GL_BLEND);

  showCoord();

  glFlush();

  SDL_GL_SwapBuffers();
}

void
Game::showCoord()
{
  auto pos = _camera.getCurrentPosition();
  std::stringstream buff;

  int xsign = pos._x < 0 ? -1 : 1;
  int ysign = pos._y < 0 ? -1 : 1;
  const int x = (static_cast<double>(pos._x) / Chunk::SIZE) + xsign * 0.5;
  const int y = (static_cast<double>(pos._y) / Chunk::SIZE) + ysign * 0.5;
  buff << "Coord\n"
       << "X: " << pos._x << "\n"
       << "Y: " << pos._y << "\n"
       << "Z: " << pos._z << "\n\n"
       << "Chunk coord\n"
       << "X: " << x << "\n"
       << "Y: " << y << "\n";

  TextureManager& textures = Singleton<TextureManager>::getInstance();

  std::string line;
  int row = 0;
  while (std::getline(buff, line))
  {
    ++row;
    if (!line.empty())
      textures.glPrint(0, 480 - (16 * row), line.c_str(), 0);
  }

  // textures.glPrint(0, 480 - (16 * 1), " !\"#$%&'()*+,-./", 0);
  // textures.glPrint(0, 480 - (16 * 2), "0123456789:;<=>?", 0);
  // textures.glPrint(0, 480 - (16 * 3), "@ABCDEFGHIJKLMNO", 0);
  // textures.glPrint(0, 480 - (16 * 4), "PQRSTUVWXYZ[\\]^_", 0);
  // textures.glPrint(0, 480 - (16 * 5), "`abcdefghijklmno", 0);
  // textures.glPrint(0, 480 - (16 * 6), "pqrstuvwxyz{|}~ ", 0);
}
