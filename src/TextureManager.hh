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
  typedef std::map<std::string, GLuint>::const_iterator const_iterator;
  typedef std::map<std::string, GLuint>::iterator iterator;

public:
  GLvoid BuildFont();
  GLvoid glPrint(GLint x, GLint y, const std::string& s, int set);
  void destroy();
  void load(const std::string& path, const std::string& name);
  GLuint operator[](const std::string& name);
  iterator find(const std::string& name);
  iterator begin();
  iterator end();

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
