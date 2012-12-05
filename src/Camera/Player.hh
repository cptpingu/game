#ifndef CAMERA_PLAYER_HH_
# define CAMERA_PLAYER_HH_

# include "BasicCamera.hh"

namespace Camera
{
  class Player : public Basic
  {
    typedef Basic super;
  public:
    Player();
    virtual ~Player();

    virtual void animate(Uint32 timestep);
    virtual std::pair<Block::Basic*, Block::FaceType>
    picking(const Map& map, const Drawer& drawer) const;
  };
} // Camera

#endif /* !CAMERA_PLAYER_HH_ */
