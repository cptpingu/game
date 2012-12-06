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
    bool collide(const Core::Vector3D& pos) const;
    void fall(double speed, unsigned int timestep);
    bool jump(bool jumping, double speed, unsigned int timestep);

  private:
    const Map&  _map;
    int         _heightBeforeJump;
    bool        _isJumping;
  };
} // Camera

#endif /* !CAMERA_PLAYER_HH_ */
