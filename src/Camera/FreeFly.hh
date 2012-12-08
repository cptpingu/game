#ifndef CAMERA_FREEFLY_HH_
# define CAMERA_FREEFLY_HH_

# include "BasicCamera.hh"

namespace Camera
{
  class FreeFly : public Basic
  {
    typedef Basic super;
  public:
    FreeFly();
    virtual ~FreeFly();

    virtual void animate(unsigned int timestep);
    virtual std::pair<Block::Basic*, Block::FaceType>
    picking(const Map& map, const Drawer& drawer) const;

  private:
    unsigned int _timeBeforeStoppingVerticalMotion;
    bool _verticalMotionActive;
    int _verticalMotionDirection;
  };
} // Camera

#endif /* !CAMERA_FREEFLY_HH_ */
