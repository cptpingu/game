#ifndef INPUTMANAGER_HH_
# define INPUTMANAGER_HH_

# include "Opengl.hh"
# include "Core/Singleton.hh"

# include <SDL/SDL.h>
# include <unordered_map>
# include <string>

/*!
** @class InputManager
**
** Manage input.
*/
class InputManager : public Core::Singleton<InputManager>
{
  friend class Core::Singleton<InputManager>;

private:
  typedef std::unordered_map<int, bool> input_state_type;
  typedef std::unordered_map<int, bool> mouse_state_type;
  typedef SDL_MouseMotionEvent          motion_info_type;

private:
  InputManager();

public:
  ~InputManager();

  bool key(const std::string& name) const;
  bool mouse(const std::string& name) const;
  unsigned int x() const;
  unsigned int y() const;
  int xrel() const;
  int yrel() const;

  bool handleInput();

private:
  input_state_type _input_states;
  mouse_state_type _mouse_states;
  motion_info_type _motion_info;
};

#endif /* !INPUTMANAGER_HH_ */
