#include "Game.hh"
#include "TextureManager.hh"
#include "ShadersManager.hh"
#include "InputManager.hh"
#include "ConfigManager.hh"
#include "Architecte.hh"
#include "Camera/FreeFly.hh"
#include "Camera/Player.hh"
#include "Model/StaticModelManager.hh"

#include <ctime>
#include <sstream>
#include <chrono>

Game::Game()
  : _map(), _drawer(), _state(_map)
{
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
}

Game::~Game()
{
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
}

bool
Game::load()
{
  ConfigManager& config = ConfigManager::getInstance();
  std::cout << "Block size:   " << Block::SIZE << std::endl
            << "Game version: " << "v0.1 alpha" << std::endl
            << "Compile time: " << __DATE__ << " " << __TIME__ << std::endl
            << "TEXTURE_SIZE: " << Chunk::TEXTURE_SIZE << std::endl
            << "OpenGL v:     " << glGetString(GL_VERSION) << std::endl;

  Model::StaticModelManager::init();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const double ratio = static_cast<double>(config["window_width"]) / config["window_height"];
  gluPerspective(70, ratio, 0.001, 1000);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  // Debug function
  _drawer.initVBO(_map);
  //!

  _map.loadBlocks("data/map/block.txt");
  _map.InitGroundBlocks(20);

  loadtextures();
  loadShaders();


  return true;
}

void
Game::play()
{
  ConfigManager& config = ConfigManager::getInstance();
  InputManager& input = InputManager::getInstance();
  const Uint32 timePerFrame = 1000 / config["fps"];
  Uint32 accumulatedTime = 0;
  Uint32 nbFrame = 0;
  Uint32 currentTime = 0;
  Uint32 elapsedTime = 0;
  Uint32 stopTime = 0;
  Uint32 lastTime = SDL_GetTicks();
  bool stop = false;

  while (!stop)
  {
    currentTime = SDL_GetTicks();
    elapsedTime = currentTime - lastTime;
    accumulatedTime += elapsedTime;
    lastTime = currentTime;
    ++nbFrame;

    _state.getCamera()->animate(elapsedTime);
    std::pair<Block::Basic*, Block::FaceType> pickedBlock =
        _state.getCamera()->picking(_map, _drawer);
    if (pickedBlock.first)
      pickedBlock.first->highlight(pickedBlock.second, true);

    drawGL(pickedBlock.first, elapsedTime);

    input.handleInput();

    if (input.isPressed("insert_block", true))
      _map.insertBlockNearBlock(pickedBlock.first, pickedBlock.second);
    else if (input.isPressed("remove_block", true))
      _map.eraseBlock(pickedBlock.first);
    else if (input.isPressed("wireframe_mode", true))
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (input.isPressed("normal_mode", true))
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (input.isPressed("take_screenshot", true))
    {
      std::ostringstream buff;
      buff << "screenshot-" << time(0) << ".bmp";
      takeScreenshot(buff.str().c_str());
    }
    else if (input.isPressed("freefly_state", true))
      _state.changeState(State::FreeFly);
    else if (input.isPressed("player_state", true))
      _state.changeState(State::Player);
    else if (input.isPressed("quit", true))
      stop = true;

    stopTime = SDL_GetTicks();
    if ((stopTime - lastTime) < timePerFrame)
      SDL_Delay(timePerFrame - (stopTime - lastTime));
    if (accumulatedTime >= 1000)
    {
      _fps = nbFrame / (accumulatedTime / 1000.0);
      accumulatedTime = 0;
      nbFrame = 0;
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
  shaders.load("basic_lightning", "data/shaders/basic_lightning.vert.c", "data/shaders/basic_lightning.frag.c");
  shaders.load("tex_lightning", "data/shaders/tex_lightning.vert.c", "data/shaders/tex_lightning.frag.c");
}

void
Game::drawGL(const Block::Basic* selectedCoord, int elapsedTime)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  _state.getCamera()->look();

  _drawer.drawBlocks(_map);
  _drawer.light(elapsedTime);
   _drawer.drawVBO();

  showCoord(selectedCoord);
  drawAxis(100);
  drawFPS(elapsedTime);
  drawHUD();

  glFlush();
  SDL_GL_SwapBuffers();
}

void
Game::showCoord(const Block::Basic* selectedCoord)
{
  ConfigManager& config = ConfigManager::getInstance();
  auto pos = _state.getCamera()->getCurrentPosition();
  std::stringstream buff;

  Core::Vector3D look = _state.getCamera()->getCurrentLook();
  buff << "Current pos: " << pos._x << " " << pos._y << " " << pos._z << "\n"
       << "Look: " << look._x << " " << look._y << " " << look._z << "\n";
  if (selectedCoord)
    buff << "Pick: " << selectedCoord->_x << " "
         << selectedCoord->_y << " "
         << selectedCoord->_z << "\n";

  TextureManager& textures = TextureManager::getInstance();
  std::string line;
  int row = 0;
  while (std::getline(buff, line))
  {
    ++row;
    if (!line.empty())
      textures.glPrint(0, config["window_height"] - (16 * row), line.c_str(), 0);
  }
}

void
Game::drawFPS(int elapsedTime)
{
  ConfigManager& config = ConfigManager::getInstance();
  static char strFrameRate[50] = {0};
  sprintf(strFrameRate, "FPS: %d", _fps);

  TextureManager& textures = TextureManager::getInstance();
  textures.glPrint(0, config["window_height"] - (16 * 10), strFrameRate, 0);
}

void
Game::drawHUD()
{
  static const double cursorSize = 20.0;
  ConfigManager& config = ConfigManager::getInstance();
  const double half_width = config["window_width"] / 2.0;
  const double half_height = config["window_height"] / 2.0;
  viewOrtho(config["window_width"], config["window_height"]);

  glColor3d(1, 0, 0);
  glBegin(GL_LINES);
  glVertex2f(half_width - (cursorSize / 2), half_height);
  glVertex2f(half_width + (cursorSize / 2), half_height);

  glVertex2f(half_width, half_height - (cursorSize / 2));
  glVertex2f(half_width, half_height + (cursorSize / 2));
  glEnd();

  viewPerspective();
}

