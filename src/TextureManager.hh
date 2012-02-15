#ifndef TEXTURE_MANAGER_HH_
# define TEXTURE_MANAGER_HH_

# include <iostream>
# include <fstream>
# include <map>
# include <SDL/SDL.h>
# include "Opengl.hh"
# include "Singleton.hh"
# include "GLUtils.hh"

class TextureManager : public Singleton<TextureManager>
{
  friend class Singleton<TextureManager>;

public:
  GLvoid BuildFont();
  GLvoid glPrint(GLint x, GLint y, const std::string& s, int set);
  void destroy();
  void load(const std::string& path, const std::string& name);
  GLuint operator[](const std::string& name);
private:
  TextureManager()
  {
  }
  ~TextureManager()
  {
  }

  GLuint base_;
  std::map<std::string, GLuint>	_texture;
};

#endif /* !TEXTURE_MANAGER_HH_ */
