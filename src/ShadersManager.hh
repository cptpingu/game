#ifndef SHADERSMANAGER_HH_
# define SHADERSMANAGER_HH_

# include "Opengl.hh"
# include "Core/Singleton.hh"

# include <unordered_map>
# include <string>

/*!
** @class ShadersManager
**
** Manage shaders. Handle compiling and linking shaders, as well as execute it.
*/
class ShadersManager : public Core::Singleton<ShadersManager>
{
  friend class Core::Singleton<ShadersManager>;
private:
  typedef std::unordered_map<std::string, GLuint> programs_type;

public:
  ShadersManager();
  ~ShadersManager();

  /*!
  ** Load shader source files, compile it and link it.
  **
  ** @param name The identifiant of the shader.
  ** @param vertexShader The file name where the vertex shader source code is.
  ** @param fragmentShader The file name where the fragment shader source code is.
  **
  ** @return If shaders was successfully loaded.
  */
  bool load(const std::string& name,
            const std::string& vertexShader,
            const std::string& fragmentShader);

  /*!
  ** Enable the given shaders. If the shaders doesn't exists, halt the program.
  ** Only one shader can be activated at a time. The last shader will
  ** be activated.
  **
  ** @param name The identifiant of the shader.
  */
  void enable(const std::string& name) const;

  /*!
  ** Disable all active shaders.
  */
  void disable() const;

  /*!
  ** Get the OpenGL identifiant of a given shader.  If the shaders doesn't
  ** exists, halt the program.
  **
  ** @param name The identifiant of the shader.
  ** @return The OpenGL identifiant.
  */
  GLuint get(const std::string& name) const;

  /*!
  ** Delete and release all loaded shaders.
  */
  void clear();

private:
  programs_type _programs;
};

#endif /* !SHADERSMANAGER_HH_ */
