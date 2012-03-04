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
** @return OpenGL identifiant, or 0 if load failed.
*/
GLuint loadTexture(const char* filename, bool useMipMap = true);

/*!
** Take a screenshot and save it into the given file.
**
** @param filename The name of the destination file.
** @return If operation succeed.
*/
bool takeScreenshot(const char* filename);

/*!
** Draw the axis.
**
** @param scale The size of the axis.
*/
void drawAxis(double scale = 1);

/*!
** Switch to fullscreen.
**
** @param width The new width of the windows.
** @param width The new height of the windows.
** @return If switching to fullscreen worked.
*/
bool initFullScreen(unsigned int& width, unsigned int& height);

/*!
** Get a XPM image from an image.
**
** @param imagefile The image file name.
** @param XPMfile The output XPM file.
** @return If load succeed.
*/
bool XPMFromImage(const char* imagefile, const char* XPMfile);

/*!
** Get a cursor from a XPM.
**
** @param xpm The xpm memory.
** @return A cursor.
*/
SDL_Cursor* cursorFromXPM(const char* xpm[]);

/*!
** Create a SDL surface using characteristics of a given image.
**
** @param width The width of the surface.
** @param height The height of the surface.
** @param display The SDL surface.
** @return A SDL surface.
*/
SDL_Surface* createSurface(int width, int height, const SDL_Surface* display);

/*!
** Create a default SDL surface.
**
** @param width The width of the surface.
** @param height The height of the surface.
** @return A SDL surface.
*/
SDL_Surface* createDefaultSurface(int width, int height);

#endif /* !SDLGLUTILS_HH_ */
