#include <cassert>
#include "TextureManager.hh"

static bool
isReadable(const char* file)
{
  std::ifstream fichier (file);
  return fichier;
}

GLvoid
TextureManager::BuildFont()
{
  GLuint loop;
  float cx;
  float cy;

  base_  = glGenLists (256);
  glBindTexture (GL_TEXTURE_2D, texture_["font"]);
  for (loop = 0; loop < 256; loop++)
  {
    cx = 1 - (float) (loop % 16) / 16.0f;
    cy = 1 - (float) (loop / 16) / 16.0f;
    glNewList (base_ + (255 - loop), GL_COMPILE);
    glBegin (GL_QUADS);
    glTexCoord2f (cx - 0.0625, cy);
    glVertex2i (0, 0);
    glTexCoord2f (cx, cy);
    glVertex2i (16, 0);
    glTexCoord2f (cx, cy - 0.0625f);
    glVertex2i (16, 16);
    glTexCoord2f (cx - 0.0625f, cy - 0.0625f);
    glVertex2i (0, 16);
    glEnd ();
    glTranslated (10, 0, 0);
    glEndList ();
  }
}

GLvoid
TextureManager::glPrint (GLint x, GLint y, const std::string& s, int set)
{
  if (set > 1)
    set = 1;

  glEnable (GL_BLEND);
  glBindTexture (GL_TEXTURE_2D, texture_["font"]);
  glDisable (GL_DEPTH_TEST);
  glMatrixMode (GL_PROJECTION);
  glPushMatrix ();
  glLoadIdentity ();
  glOrtho (0, 640, 0, 480, -1, 1);
  glMatrixMode (GL_MODELVIEW);
  glPushMatrix ();
  glLoadIdentity ();
  glTranslated (x, y, 0);
  glListBase (base_ - 32 + (128 * set));
  glCallLists (s.size (), GL_BYTE, s.c_str ());
  glMatrixMode (GL_PROJECTION);
  glPopMatrix ();
  glMatrixMode (GL_MODELVIEW);
  glPopMatrix ();
  glEnable (GL_DEPTH_TEST);
  glDisable (GL_BLEND);
}

void
TextureManager::destroy()
{
  glDeleteLists(base_, 256);
  texture_.clear();
}

void
TextureManager::load(const std::string& path, const std::string& name)
{
  if (!isReadable (path.c_str ()))
    std::cerr << "Unable to open " << path << std::endl;
  else
    texture_[name] = loadTexture(path.c_str ());
}

GLuint
TextureManager::operator[](const std::string& name)
{
  return (texture_[name]);
}
