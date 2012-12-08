#ifndef STATE_HH_
# define STATE_HH_

# include "Map.hh"
# include "Camera/BasicCamera.hh"

class State
{
public:
  enum Mode
  {
    FreeFly,
    MainMenu,
    Player,
    Inventory
  };

public:
  State(const Map& map);
  ~State();

  void changeState(Mode state);

  Camera::Basic* getCamera() const;
  // FIXME HUD::Basic* getHUD() const ;

private:
  const Map&     _map;
  Mode           _mode;
  Camera::Basic* _camera;
  // FIXME HUD::Basic* _hud;
};

#endif /* !STATE_HH_ */
