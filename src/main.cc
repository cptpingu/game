#include "Opengl.hh"
#include <SDL/SDL.h>

#include <cstdlib>
#include <iostream>
#include "Map.hh"
#include "MapWriter.hh"
#include "TextureManager.hh"

#include <time.h>
#include "GLUtils.hh"
#include "FreeFlyCamera.hh"
#include "Scene.hh"
#include "Drawer.hh"
#include "ImageFile.hh"

#ifdef _WIN32
# define MAIN int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
#else
# define MAIN int main(int, char**)
#endif

#define FPS 50
#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

FreeFlyCamera* camera;

void stop()
{
  delete camera;
  SDL_Quit();
}


void drawGL(const Map& map,const Drawer& Dede)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  camera->look();


  //glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur
  glEnable(GL_LIGHTING); 	// Active l'éclairage
  glEnable(GL_LIGHT0);

  double a=0;
  int LightPos[4] = {10,10,30,1};
  int MatSpec [4] = {1,1,1,1};


  glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);


  glRotated(a,0,1,0);
  glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

  a=+1;

  //float Light1Pos[4] = {15.0f, 15.0f, 20.0f, 1.0f};
  float Light1Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
  float Light1Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
  float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  //float Spot1Dir[3] = {0.0f, 0.0f, -1.0f};

  glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Dif); 	//Et ceux de la lumière
  glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Spec);
  glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Amb);
  glEnable(GL_LIGHTING); 	//Et on allume la lumière
  glEnable(GL_LIGHT1);
  glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
  float Light1Dir[3] = {0.0f, 0.0f, -1.0f};
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);


  Dede.drawMap(map);
  glEnable(GL_FOG) ;
  GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
  GLint fogmode = GL_EXP ;
  glFogi (GL_FOG_MODE, fogmode) ;
  glFogfv(GL_FOG_COLOR, fogcolor) ;
  glFogf(GL_FOG_DENSITY, 0.1) ;
  glFogf(GL_FOG_START, 10.0) ;
  glFogf(GL_FOG_END, 20.0) ;


  glFrustum( 5,   5,   5,   5,   2,  10);


  glColor3f(1.0f,1.0f,1.0f);
  TextureManager& textures = Singleton<TextureManager>::getInstance();
  glBindTexture(GL_TEXTURE_2D, textures["eau"]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex3d(0,0,-2);

  glTexCoord2f(2,0);
  glVertex3d(0, 60,-2);

  glTexCoord2f(2,2);
  glVertex3d(60,60,-2);

  glTexCoord2f(0,2);
  glVertex3d(60,0,-2);
  glEnd();

  glColor4f(1.0f,1.0f,1.0f,0.55f);  // alpha 55%
  // on active la transparence
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);


  glBindTexture(GL_TEXTURE_2D, textures["eau"]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex3d(0,0,-2);

  glTexCoord2f(2,0);
  glVertex3d(0, 60,-2);

  glTexCoord2f(2,2);
  glVertex3d(60,60,-2);

  glTexCoord2f(0,2);
  glVertex3d(60,0,-2);
  glEnd();
  // désactive transparence
  glDisable(GL_BLEND);

  glFlush();

  SDL_GL_SwapBuffers();

}

MAIN
{
  srand(time(0));

  Drawer Konnard;
  MapWriter Chocopops;
  Map map;
  SDL_Event event;
  const Uint32 time_per_frame = 1000/FPS;
  unsigned int width = LARGEUR_FENETRE;
  unsigned int height = HAUTEUR_FENETRE;

  Uint32 last_time,current_time,elapsed_time; //for time animation
  Uint32 stop_time; //for frame limit

  SDL_Init(SDL_INIT_VIDEO);
  atexit(stop);

  SDL_WM_SetCaption("SDL GL Application", 0);
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  //initFullScreen(&width,&height);

  if (!initExtensions())
  {
      SDL_Quit();
      return 1;
  }

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)width/height,0.001,1000);



  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  chargerTextures();
  static const std::string filename = "Carte.txt";
  if (!map.loadBlocks(filename))
  {
    std::cerr << "Unable to load " << filename << std::endl;
    return 1;

  }

  static const std::string terrain = "Terrain.txt";
  if (!map.loadTriangles(terrain))
  {
    std::cerr << "Unable to load " << terrain << std::endl;
    return 1;

  }

  camera = new FreeFlyCamera(Vector3D(0, 0, 2));

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
              camera->OnKeyboard(event.key);
          }
          break;
        case SDL_KEYUP:
          camera->OnKeyboard(event.key);
          break;
        case SDL_MOUSEMOTION:
          camera->OnMouseMotion(event.motion);
          break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
          camera->OnMouseButton(event.button);
          break;
      }
    }

    current_time = SDL_GetTicks();
    elapsed_time = current_time - last_time;
    last_time = current_time;

    camera->animate(elapsed_time);

    //Vector3D where(1,1,1);


    //Chocopops.Debut();
    //Chocopops.Sol(100);
    //Chocopops.Building(where,5,0,5);

    drawAxis(2);
    drawGL(map,Konnard);

   // ImageFile img("data/images/test.jpg");
   // if (!img.loadImage())
   // {
    //  std::cout << "Erreur" << std::endl;
    //  return 0;
    // }



    stop_time = SDL_GetTicks();
    if ((stop_time - last_time) < time_per_frame)
      SDL_Delay(time_per_frame - (stop_time - last_time));
  }

  return 0;
}
