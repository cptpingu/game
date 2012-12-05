#ifndef CONFIGMANAGER_HH_
# define CONFIGMANAGER_HH_

# include "Opengl.hh"
# include "Core/Singleton.hh"

# include <SDL/SDL.h>
# include <unordered_map>
# include <string>

/*!
** @class ConfigManager
**
** Manage configuration.
*/
class ConfigManager : public Core::Singleton<ConfigManager>
{
  friend class Core::Singleton<ConfigManager>;

private:
  typedef std::unordered_map<std::string, int> binding_type;

private:
  ConfigManager();

public:
  ~ConfigManager();

  bool load(const std::string& filename);
  void dump(std::ostream& out) const;

  int operator[](const std::string& name) const;
  void set(const std::string& name, int value);

private:
  binding_type _bindings;
};

#endif /* !CONFIGMANAGER_HH_ */
