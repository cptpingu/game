#include "Opengl.hh"
#include <iostream>
#include <SDL/SDL.h>

PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = 0;
PFNGLACTIVETEXTUREARBPROC   glActiveTexture = 0;
PFNGLMULTITEXCOORD3IPROC    glMultiTexCoord3i = 0;

namespace
{
  bool extensionExists(const char* name)
  {
    const unsigned char* exts = glGetString(GL_EXTENSIONS);
    if (strstr((const char*)exts, name) == 0)
    {
      std::cerr << "extension '" << name << "' non supportée" << std::endl;
      return false;
    }
    return true;
  }
} //namespace

bool initExtensions()
{
  if (!(glActiveTexture = (PFNGLACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress("glActiveTextureARB")))
    return false;
  if (!(glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC) SDL_GL_GetProcAddress("glMultiTexCoord3iARB")))
    return false;

  return true;
}
