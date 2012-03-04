#ifndef SDLGLUTILS_HH_
# define SDLGLUTILS_HH_

# include "Opengl.hh"
# include <SDL/SDL.h>

# ifndef GL_CLAMP_TO_EDGE
#  define GL_CLAMP_TO_EDGE 0x812F
# endif

/*!
** Load an image and create an OpenGL texture with it.
**
** @param filename The name of the file.
** @param useMipMap If mimap has to be used (default is true).
**
** @return OpenGL identifiant, or 0 if load failed.
*/
GLuint loadTexture(const char* filename, bool useMipMap = true);

/*!
** Take a screenshot and save it into the given file.
**
** @param filename The name of the destination file.
**
** @return If operation succeed.
*/
bool takeScreenshot(const char* filename);
void drawAxis(double scale = 1);
bool initFullScreen(unsigned int* width = 0, unsigned int* height = 0);
int XPMFromImage(const char* imagefile, const char* XPMfile);
SDL_Cursor* cursorFromXPM(const char* xpm[]);
SDL_Surface* createSurface(int width, int height, const SDL_Surface* display);
SDL_Surface* createDefaultSurface(int width, int height);

#endif /* !SDLGLUTILS_HH_ */
