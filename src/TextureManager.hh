#ifndef TEXTURE_MANAGER_HH_
# define TEXTURE_MANAGER_HH_

# include <string>
# include <map>
# include <SDL/SDL.h>
# include "Opengl.hh"
# include "Core/Singleton.hh"
# include "GLUtils.hh"

/*!
** @class TextureManager
**
** Handle texture loading.
*/
class TextureManager : public Core::Singleton<TextureManager>
{
  friend class Core::Singleton<TextureManager>;
public:
  typedef std::map<std::string, GLuint>::const_iterator const_iterator;
  typedef std::map<std::string, GLuint>::iterator iterator;

public:
  /*!
  ** Load and create the font used to show text on screen.
  */
  void BuildFont();

  /*!
  ** Print a text on screen on given coordinates.
  **
  ** @param x On-screen x coordinate.
  ** @param y On-screen y coordinate.
  ** @param set The style of the text (0: normal or 1: bold).
  */
  void glPrint(GLint x, GLint y, const std::string& s, int set);

  /*!
  ** Release all loaded resources.
  */
  void destroy();

  /*!
  ** Load a texture and assign it an identifiant.
  **
  ** @param path File name of the image to load.
  ** @param name The identifiant of the texture.
  ** @return If load succeed.
  */
  bool load(const std::string& path, const std::string& name);

  /*!
  ** Get the OpenGL identifiant of a texture, given its name.
  **
  ** @param name The identifiant of the texture.
  ** @return The OpenGL identifiant.
  */
  GLuint operator[](const std::string& name);

  /*!
  ** Try to find a texture, given its identifiant.
  **
  ** @param name The identifiant of the texture.
  ** @return An iterator on the OpenGL identifiant, or an "end" iterator if not found.
  */
  iterator find(const std::string& name);

  /*!
  ** Get an iterator on the first texture.
  **
  ** @return An iterator on the OpenGL identifiant.
  */
  iterator begin();

  /*!
  ** Get an iterator after the last texture.
  **
  ** @return An iterator on the OpenGL identifiant.
  */
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
