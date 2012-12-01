#include "Game.hh"
#include "TextureManager.hh"
#include "ShadersManager.hh"
#include "Architecte.hh"

#include <ctime>
#include <sstream>
#include <chrono>

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
    //std::pair<Block::Basic*, Block::FaceType> pickedBlock = _camera.picking(_map);
    std::pair<Block::Basic*, Block::FaceType> pickedBlock = _camera.picking2(_map, _drawer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    if (pickedBlock.first)
      pickedBlock.first->highlight(pickedBlock.second, true);

    //float fps = ( numFrames/(float)(SDL_GetTicks() - startTime) )*1000;
    stop_time = SDL_GetTicks();
    drawGL(pickedCoord, elapsed_time);
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
              _map.insertBlockNearBlock(pickedBlock.first, pickedBlock.second);
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
Game::drawGL(const Chunk::Coord* selectedCoord,
             int fpsFromSDL)
{
  //glEnable(GL_TEXTURE_2D);
  //glEnable(GL_FOG);
  //glEnable(GL_LIGHTING);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  _camera.look();

  _drawer.drawBlocks(_map);
  _drawer.drawChunks(_map.getChunks(), selectedCoord);

  showCoord(selectedCoord);
  drawAxis(10000);
  drawFPS(fpsFromSDL);
  drawHUD();

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

void
Game::drawFPS(int fpsFromSDL)
{
  typedef std::chrono::time_point<std::chrono::high_resolution_clock> chrono;

  static unsigned int frames = 0;
  static chrono lastTime;
  static char strFrameRate[50] = {0};

  const chrono currentTime =  std::chrono::high_resolution_clock::now();
  ++frames;
  const int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>
      (currentTime - lastTime).count();

  if (elapsedTime > 1000)
  {
    lastTime = currentTime;
    sprintf(strFrameRate, "FPS: %d %d", frames, fpsFromSDL);
    frames = 0;
  }

  TextureManager& textures = TextureManager::getInstance();
  textures.glPrint(0, WINDOW_HEIGHT - (16 * 10), strFrameRate, 0);
}

void
Game::drawHUD()
{
  static const double cursorSize = 20.0;

  viewOrtho(WINDOW_WIDTH, WINDOW_HEIGHT);

  glColor3d(1, 0, 0);
  glBegin(GL_LINES);
  glVertex2f((WINDOW_WIDTH / 2) - (cursorSize / 2), WINDOW_HEIGHT / 2);
  glVertex2f((WINDOW_WIDTH / 2) + (cursorSize / 2), WINDOW_HEIGHT / 2);

  glVertex2f(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2) - (cursorSize / 2));
  glVertex2f(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2) + (cursorSize / 2));
  glEnd();

  viewPerspective();
}
