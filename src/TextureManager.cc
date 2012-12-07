#include "Core/Assert.hh"

#include "TextureManager.hh"
#include "ShadersManager.hh"

void
TextureManager::BuildFont()
{
  static const double FONT_WIDTH = 0.0625;
  static const double FONT_HEIGHT = 16.0;

  base_ = glGenLists(256);
  glBindTexture(GL_TEXTURE_2D, _texture["font"]);
  for (GLuint loop = 0; loop < 256; ++loop)
  {
    float cx = (15 - (float) (loop % 16)) / FONT_HEIGHT;
    float cy = (float) (loop / 16) / FONT_HEIGHT;
    glNewList(base_ + (255 - loop), GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(cx, cy);
    glVertex2i(0, 0);
    glTexCoord2f(cx + FONT_WIDTH, cy);
    glVertex2i(16, 0);
    glTexCoord2f(cx + FONT_WIDTH, cy + FONT_WIDTH);
    glVertex2i(16, 16);
    glTexCoord2f(cx, cy + FONT_WIDTH);
    glVertex2i(0, 16);
    glEnd();
    glTranslated(13, 0, 0);
    glEndList();
  }
}

void
TextureManager::glPrint(GLint x, GLint y, const std::string& s, int set)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texture["font"]);
  ShadersManager& shaders = ShadersManager::getInstance();
  shaders.enable("texture");
  glUniform1i(glGetUniformLocation(shaders.get("texture"), "tex"), 0);

  if (set > 1)
    set = 1;

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, 640, 0, 480, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(x, y, 0);
  glListBase(base_ - 32 + (128 * set));
  glCallLists(s.size(), GL_BYTE, s.c_str());
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  shaders.disable();
}

void
TextureManager::destroy()
{
  glDeleteLists(base_, 256);
  _texture.clear();
}

bool
TextureManager::load(const std::string& path, const std::string& name)
{
  GLuint res = loadTexture(path.c_str ());
  if (!res)
    return false;

  _texture[name] = res;
  return true;
}

GLuint
TextureManager::operator[](const std::string& name)
{
  ASSERT_MSG(find(name) != end(), "Texture not found: " << name);
  return (_texture[name]);
}

TextureManager::iterator
TextureManager::find(const std::string& name)
{
  return _texture.find(name);
}

TextureManager::iterator
TextureManager::begin()
{
  return _texture.begin();
}

TextureManager::iterator
TextureManager::end()
{
  return _texture.end();
}
