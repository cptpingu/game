#ifndef SDLGLUTILS_HH_
# define SDLGLUTILS_HH_

# include "Opengl.hh"
#include <SDL/SDL.h>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLuint loadTexture(const char* filename, bool useMipMap = true);
int takeScreenshot(const char* filename);
void drawAxis(double scale = 1);
int initFullScreen(unsigned int* width = 0, unsigned int* height = 0);
int XPMFromImage(const char* imagefile, const char* XPMfile);
SDL_Cursor* cursorFromXPM(const char* xpm[]);

#endif /* !SDLGLUTILS_HH_ */
