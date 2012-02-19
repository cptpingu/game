#ifndef SAVEPNG_HH_
# define SAVEPNG_HH_

# include <png.h>
# include <SDL/SDL.h>

namespace SDL
{
  int savePng(SDL_Surface* surface, const char* filename);
}

#endif /* !SAVEPNG_HH */
