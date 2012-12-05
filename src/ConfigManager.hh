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

  int operator[](const std::string& name) const;

private:
  binding_type _bindings;
};

#endif /* !CONFIGMANAGER_HH_ */
