#include "Game.hh"
#include "TextureManager.hh"
#include "ShadersManager.hh"
#include "Architecte.hh"

#include <ctime>
#include <sstream>

bool
Game::load()
{
  std::cout << "SIZE: " << Chunk::SIZE << std::endl
            << "QUALITY: " << Chunk::QUALITY << std::endl
            << "TEXTURE_SIZE: " << Chunk::TEXTURE_SIZE << std::endl
            << "OpenGL v: " << glGetString(GL_VERSION) << std::endl;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)WINDOW_WIDTH / WINDOW_HEIGHT, 0.001, 1000);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  _map.loadBlocks("data/map/block.txt");
  _map.InitGroundBlocks(50);
  loadtextures();
  loadShaders();

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
      current_time = SDL_GetTicks();
      elapsed_time = current_time - last_time;
      last_time = current_time;

      _map.chunkLazyLoading(_camera.getCurrentPosition(), _map.getChunks());
      _camera.animate(elapsed_time);
      Chunk::Coord* pickedCoord = _camera.picking(_map.getChunks());
      std::pair<Block*, Block::FaceType> pickedBlock = _camera.picking(_map);
      if (pickedBlock.first)
        //pickedBlock.first->highlight(Block::up, true);
        pickedBlock.first->highlight(pickedBlock.second, true);


       //Architecte::InitGroundBlocks(_map);

      drawAxis(100);

      drawGL(pickedCoord);

      stop_time = SDL_GetTicks();
      if ((stop_time - last_time) < time_per_frame)
        SDL_Delay(time_per_frame - (stop_time - last_time));

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
              {
                std::ostringstream buff;
                buff << "screenshot-" << time(0) << ".bmp";
                takeScreenshot(buff.str().c_str());
                break;
              }
          case SDLK_g:
              _map.insertBlockfromBlock(pickedBlock.first, pickedBlock.second);
              break;
            case SDLK_f:
              _map.eraseBlock(pickedBlock.first);
              break;
            case SDLK_w:
              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
              break;
            case SDLK_x:
              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
              break;
            case SDLK_ESCAPE:
              exit(0);
              break;
            default:
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
  }
}

void
Game::loadtextures()
{
  TextureManager& textures = TextureManager::getInstance();

  textures.load("data/images/font.png", "font");
  textures.BuildFont();

  textures.load("data/images/metal091.jpg", "metal");
  textures.load("data/images/rocket_motor.jpg", "rocketMotor");
  textures.load("data/images/rocket_bottom.jpg", "rocketBottom");
  textures.load("data/images/rocket_middle.jpg", "rocketMiddle");
  textures.load("data/images/rocket_top.jpg", "rocketTop");
  //autre texture
  textures.load("data/images/concrete001.jpg", "concrete");
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
}

void
Game::loadShaders()
{
  ShadersManager& shaders = ShadersManager::getInstance();
  shaders.load("identity", "data/shaders/identity.vert.c", "data/shaders/identity.frag.c");
  shaders.load("texture", "data/shaders/texture.vert.c", "data/shaders/texture.frag.c");
  shaders.load("cube", "data/shaders/cube.vert.c", "data/shaders/cube.frag.c");
  shaders.load("texture_invert_color", "data/shaders/texture.vert.c", "data/shaders/texture_invert_color.frag.c");
  shaders.load("phong_lightning", "data/shaders/phong_lightning.vert.c", "data/shaders/phong_lightning.frag.c");
  shaders.load("terrain", "data/shaders/terrain.vert.c", "data/shaders/terrain.frag.c");
}

void
Game::drawGL(const Chunk::Coord* selectedCoord)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  _camera.look();

  _drawer.drawBlocks(_map.getBlocks());
  _drawer.drawChunks(_map.getChunks(), selectedCoord);
  showCoord(selectedCoord);

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


  // glEnable(GL_FOG) ;
  // GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
  // GLint fogmode = GL_LINEAR;//GL_EXP ;
  // glFogi (GL_FOG_MODE, fogmode) ;
  // glFogfv(GL_FOG_COLOR, fogcolor) ;
  // glFogf(GL_FOG_DENSITY, 0.1) ;
  // glFogf(GL_FOG_START, 10.0) ;
  // glFogf(GL_FOG_END, 20.0) ;

  //glFrustum( 5,   5,   5,   5,   2,  10);

  // glColor3f(1.0f,1.0f,1.0f);
  // TextureManager& textures = Singleton<TextureManager>::getInstance();
  // glBindTexture(GL_TEXTURE_2D, textures["eau"]);
  // glBegin(GL_QUADS);
  // glTexCoord2f(0,0);
  // glVertex3d(0,0,-2);

  // glTexCoord2f(2,0);
  // glVertex3d(0, 60,-2);

  // glTexCoord2f(2,2);
  //glVertex3d(60,60,-2);

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

  glFlush();
  SDL_GL_SwapBuffers();
}

void
Game::showCoord(const Chunk::Coord* selectedCoord)
{
  auto pos = _camera.getCurrentPosition();
  std::stringstream buff;

  Vector3D look = _camera.getCurrentLook();
  const int x = Chunk::absoluteToChunkCoord(pos._x);
  const int y = Chunk::absoluteToChunkCoord(pos._y);
  buff << "World coord: " << pos._x << " " << pos._y << " " << pos._z << "\n"
       << "Chunk coord: " << x << " " << y << "\n"
       << "Look: " << look._x << " " << look._y << " " << look._z << "\n";
  if (selectedCoord)
    buff << "Pick: " << selectedCoord->getX() << " "
         << selectedCoord->getY() << " "
         << selectedCoord->getZ() << "\n";

  TextureManager& textures = TextureManager::getInstance();
  std::string line;
  int row = 0;
  while (std::getline(buff, line))
  {
    ++row;
    if (!line.empty())
      textures.glPrint(0, WINDOW_HEIGHT - (16 * row), line.c_str(), 0);
  }
}
