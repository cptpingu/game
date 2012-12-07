#ifndef CAMERA_PLAYER_HH_
# define CAMERA_PLAYER_HH_

# include "BasicCamera.hh"
# include "../Map.hh"

namespace Camera
{
  class Player : public Basic
  {
    typedef Basic super;
  public:
    Player(const Map& map);
    virtual ~Player();

    virtual void animate(unsigned int timestep);
    virtual std::pair<Block::Basic*, Block::FaceType>
    picking(const Map& map, const Drawer& drawer) const;

  private:
    Core::Vector3D collide(const Core::Vector3D& next) const;
    void fall(double speed, unsigned int timestep, Core::Vector3D& nextPos);
    bool jump(bool jumping, double speed,
              unsigned int timestep, Core::Vector3D& nextPos);

  private:
    const Map&  _map;
    int         _heightBeforeJump;
    bool        _isJumping;
    bool        _isFalling;
  };
} // Camera

#endif /* !CAMERA_PLAYER_HH_ */
