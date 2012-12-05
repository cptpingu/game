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

    virtual Chunk::Coord* picking(const Map::chunks_type& chunks) const;
    virtual std::pair<Block::Basic*, Block::FaceType> picking(const Map& blocks) const;
    virtual std::pair<Block::Basic*, Block::FaceType> picking2(const Map& map, const Drawer& drawer, int x, int y) const;

    virtual void animate(Uint32 timestep) = 0;

    virtual void setPosition(const Core::Vector3D& position);

    virtual void look();

    Core::Vector3D getCurrentPosition() const;
    Core::Vector3D getCurrentLook() const;

  protected:
    //vertical motion stuffs
    Uint32 _timeBeforeStoppingVerticalMotion;
    bool _verticalMotionActive;
    int _verticalMotionDirection;
    Core::Vector3D _position;
    Core::Vector3D _target;
    Core::Vector3D _forward;
    Core::Vector3D _left;
    double _theta;
    double _phi;

    void VectorsFromAngles();
    std::pair<int, int> innerCoordChunktoAbsolute(const std::pair<int, int>& coord,
                                                  const std::pair<int, int>& selectedCoord);
  };
} // Camera

#endif /* !CAMERA_BASIC_HH_ */
