#ifndef CAMERA_BASIC_HH_
# define CAMERA_BASIC_HH_

# include "../Core/Vector3D.hh"
# include "../Chunk.hh"
# include "../Map.hh"
# include "../Drawer.hh"
# include "../Block/Basic.hh"

# include <SDL/SDL.h>
# include <map>
# include <string>

namespace Camera
{
  class Basic
  {
  public:
    Basic();
    virtual ~Basic();

    Basic& operator=(const Basic& camera);

    virtual std::pair<Block::Basic*, Block::FaceType>
    picking(const Map& map, const Drawer& drawer, int mouseX, int mouseY) const;
    virtual void setPosition(const Core::Vector3D& position);
    virtual void look();

    virtual void animate(unsigned int timestep) = 0;
    virtual std::pair<Block::Basic*, Block::FaceType>
    picking(const Map& map, const Drawer& drawer) const = 0;


    Core::Vector3D getCurrentPosition() const;
    Core::Vector3D getCurrentLook() const;

  protected:
    void vectorsFromAngles();

  protected:
    Core::Vector3D _position;
    Core::Vector3D _target;
    Core::Vector3D _forward;
    Core::Vector3D _left;
    double _theta;
    double _phi;
  };
} // Camera

#endif /* !CAMERA_BASIC_HH_ */
