#ifndef FREEFLYCAMERA_HH_
# define FREEFLYCAMERA_HH_

#include "Vector3D.hh"
#include <SDL/SDL.h>
#include <map>
#include <string>
#include "Chunk.hh"
#include "Map.hh"
#include "Block.hh"


class FreeFlyCamera
{
public:
    FreeFlyCamera();

    virtual void OnMouseMotion(const SDL_MouseMotionEvent & event);
    virtual void OnMouseButton(const SDL_MouseButtonEvent & event);
    virtual void OnKeyboard(const SDL_KeyboardEvent & event);

    virtual Chunk::Coord* picking(const Map::chunks_type& chunks) const;
    virtual std::pair<Block::Block*, Block::FaceType> picking(const Map& blocks) const;

    virtual void animate(Uint32 timestep);
    virtual void setSpeed(double speed);
    virtual void setSensivity(double sensivity);

    virtual void setPosition(const Vector3D& position);

    virtual void look();

    virtual ~FreeFlyCamera();

    Vector3D getCurrentPosition() const;
    Vector3D getCurrentLook() const;





protected:
    double _speed;
    double _sensivity;

    //vertical motion stuffs
    Uint32 _timeBeforeStoppingVerticalMotion;
    bool _verticalMotionActive;
    int _verticalMotionDirection;

    typedef std::map<SDLKey,bool> KeyStates;
    KeyStates _keystates;
    typedef std::map<std::string,SDLKey> KeyConf;
    KeyConf _keyconf;

    Vector3D _position;
    Vector3D _target;
    Vector3D _forward;
    Vector3D _left;
    double _theta;
    double _phi;

    void VectorsFromAngles();
    std::pair<int, int> innerCoordChunktoAbsolute(const std::pair<int, int>& coord,
                         const std::pair<int, int>& selectedCoord);
    //void Init();
};

#endif /* !FREEFLYCAMERA_H */
