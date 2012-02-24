#ifndef SHADERSMANAGER_HH_
# define SHADERSMANAGER_HH_

# include "Opengl.hh"
# include "Core/Singleton.hh"

# include <unordered_map>
# include <string>

class ShadersManager : public Core::Singleton<ShadersManager>
{
  friend class Core::Singleton<ShadersManager>;
private:
  typedef std::unordered_map<std::string, GLuint> programs_type;

public:
  ShadersManager();
  ~ShadersManager();

  void load(const std::string& name,
            const std::string& vertexShader,
            const std::string& fragmentShader);

  void enable(const std::string& name) const;
  void disable() const;
  void clear();

private:
  programs_type _programs;
};

#endif /* !SHADERSMANAGER_HH_ */
