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

    virtual void OnMouseButton(const SDL_MouseButtonEvent& event);
    virtual void OnKeyboard(const SDL_KeyboardEvent& event);
    virtual void animate(Uint32 timestep);
  };
} // Camera

#endif /* !CAMERA_FREEFLY_HH_ */
