#include "FreeFlyCamera.hh"
#include "iostream"
#include <cmath>
#include "Opengl.hh"
#include "Chunk.hh"

#ifndef M_PI
# define M_PI 3.14159265
#endif

namespace
{
std::pair<int, int>
innerCoordChunktoAbsolute(const std::pair<int, int>& coord,
                     const std::pair<int, int>& selectedCoord)
{
      std::pair<int, int> Abs;
      Abs.first = coord.first*(Chunk::SIZE-1) + selectedCoord.first + (2*(coord.first < 0)-1)*(Chunk::SIZE-1)/2;
      Abs.second = coord.second*(Chunk::SIZE-1) + selectedCoord.first + (2*(coord.second < 0)-1)*(Chunk::SIZE-1)/2;
      return Abs;
}

}





FreeFlyCamera::FreeFlyCamera()
{
  _position = Vector3D(0,0,0);
  _phi = 0;
  _theta = 0;
  VectorsFromAngles();

  _speed = 0.01;
  _sensivity = 0.02;
  _verticalMotionActive = false;
  _keyconf["forward"] = SDLK_UP;
  _keyconf["backward"] = SDLK_DOWN;
  _keyconf["strafe_left"] = SDLK_LEFT;
  _keyconf["strafe_right"] = SDLK_RIGHT;
  _keyconf["boost"] = SDLK_RSHIFT;
  _keystates[_keyconf["forward"]] = false;
  _keystates[_keyconf["backward"]] = false;
  _keystates[_keyconf["strafe_left"]] = false;
  _keystates[_keyconf["strafe_right"]] = false;
  _keystates[_keyconf["boost"]] = false;

  // SDL_WM_GrabInput(SDL_GRAB_ON);
  // SDL_ShowCursor(SDL_DISABLE);
}

FreeFlyCamera::~FreeFlyCamera()
{
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
}

void
FreeFlyCamera::OnMouseMotion(const SDL_MouseMotionEvent& event)
{
  _theta -= event.xrel; //* _sensivity;
  _phi -= event.yrel; //* _sensivity;
  VectorsFromAngles();
}

void
FreeFlyCamera::OnMouseButton(const SDL_MouseButtonEvent& event)
{
  //coup de molette vers le haut
  if (event.button == SDL_BUTTON_WHEELUP && event.type == SDL_MOUSEBUTTONDOWN)
  {
    _verticalMotionActive = true;
    _timeBeforeStoppingVerticalMotion = 250;
    _verticalMotionDirection = 1;

  }
  //coup de molette vers le bas
  else if (event.button == SDL_BUTTON_WHEELDOWN && event.type == SDL_MOUSEBUTTONDOWN)
  {
    _verticalMotionActive = true;
    _timeBeforeStoppingVerticalMotion = 250;
    _verticalMotionDirection = -1;
  }
}

void
FreeFlyCamera::OnKeyboard(const SDL_KeyboardEvent& event)
{
  for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end(); ++it)
  {
    if (event.keysym.sym == it->first)
    {
      it->second = (event.type == SDL_KEYDOWN);
      break;
    }
  }
}

void
FreeFlyCamera::animate(Uint32 timestep)
{
  double realspeed = _keystates[_keyconf["boost"]] ? 10 * _speed : _speed;
  if (_keystates[_keyconf["forward"]])
    _position += _forward * (realspeed * timestep);
  if (_keystates[_keyconf["backward"]])
    _position -= _forward * (realspeed * timestep);
  if (_keystates[_keyconf["strafe_left"]])
    _position += _left * (realspeed * timestep);
  if (_keystates[_keyconf["strafe_right"]])
    _position -= _left * (realspeed * timestep);
  if (_verticalMotionActive)
  {
    if (timestep > _timeBeforeStoppingVerticalMotion)
      _verticalMotionActive = false;
    else
      _timeBeforeStoppingVerticalMotion -= timestep;
    _position += Vector3D(0, 0, _verticalMotionDirection * realspeed * timestep);
  }
  _target = _position + _forward;

}

void
FreeFlyCamera::setSpeed(double speed)
{
  _speed = speed;
}

void
FreeFlyCamera::setSensivity(double sensivity)
{
  _sensivity = sensivity;
}

void
FreeFlyCamera::setPosition(const Vector3D & position)
{
  _position = position;
  _target = _position + _forward;
}

void
FreeFlyCamera::VectorsFromAngles()
{
  static const Vector3D up(0, 0, 1);
  if (_phi > 89)
    _phi = 89;
  else if (_phi < -89)
    _phi = -89;

  double r_temp = cos(_phi * M_PI / 180);

  _forward._z = sin(_phi * M_PI / 180);
  _forward._x = r_temp * cos(_theta * M_PI / 180);
  _forward._y = r_temp * sin(_theta * M_PI / 180);

  _left = up.crossProduct(_forward);
  _left.normalize();

  _target = _position + _forward;
}

void
FreeFlyCamera::look()
{
  gluLookAt(_position._x, _position._y, _position._z,
            _target._x, _target._y, _target._z,
            0, 0, 1);
}

Vector3D
FreeFlyCamera::getCurrentPosition() const
{
  return _position;
}

Vector3D
FreeFlyCamera::getCurrentLook() const
{
  return _target;
}




Chunk::Coord*
FreeFlyCamera::picking(const Map::chunks_type& chunks) const
{

  auto chunk = chunks.find(std::make_pair(Chunk::absoluteToChunkCoord(_position._x),Chunk::absoluteToChunkCoord(_position._y)));
  /*assert(chunk != chunks.cend() && "Can't found corresponding chunk!");*/

  int MaxPick = 20;

  int newX =-1;
  int newY =-1;


  int x0 = static_cast<int>(_position._x)%(Chunk::SIZE-1);
  int y0 = static_cast<int>(_position._y)%(Chunk::SIZE-1);




  if ( x0 >0)
  {
  if( x0 < (Chunk::SIZE-1)/2)
  {x0 = x0 + (Chunk::SIZE-1)/2;}
  else
  {x0 = x0 - (Chunk::SIZE-1)/2;}
  }
  else
  {
  if( x0 > -(Chunk::SIZE-1)/2)
  {
  x0 = x0 + (Chunk::SIZE-1)/2;
  }
  else
  {
  x0 = x0 + (Chunk::SIZE-1) +(Chunk::SIZE-1)/2;
  }
  }

  if ( y0 >0)
  {
  if( y0 < (Chunk::SIZE-1)/2)
  {y0 = y0 + (Chunk::SIZE-1)/2;}
  else
  {y0 = y0 - (Chunk::SIZE-1)/2;}
  }
  else
  {
  if( y0 > -(Chunk::SIZE-1)/2)
  {
  y0 = y0 + (Chunk::SIZE-1)/2;
  }
  else
  {
  y0 = y0 + (Chunk::SIZE-1) +(Chunk::SIZE-1)/2;
  }
  }

  int Nbx = fabs(MaxPick*_forward._x)+1;
  int Nby = fabs(MaxPick*_forward._y)+1;

  int signeX = (_forward._x > 0) - (_forward._x < 0);
  int signeY = (_forward._y > 0) - (_forward._y < 0);

  double LocalZ;
  double Distance;
  double LastBest = 2000;//sqrt(_forward._x*MaxPick*_forward._x*MaxPick+_forward._y*MaxPick*_forward._y*MaxPick);

 std::cout << "Les bornes sont" << std::endl;
 std::cout << Nbx*signeX << " " <<  Nby*signeY << std::endl;

 std::cout << "Point de départ" << std::endl;
 std::cout <<x0 << " " << y0 << std::endl;

  for (int x = 0;x < Nbx;++x)
  for (int y = 0;y < Nby;++y)
  {

    Distance = sqrt((_position._x  + x*signeX)*(_position._x  + x*signeX) +
                    (_position._y  + y*signeY)*(_position._y  + y*signeY));


   LocalZ = Distance/sqrt((_position._x  + Nbx*signeX)*(_position._x + Nbx*signeX) + (_position._y + Nby*signeY)*(_position._y + Nby*signeY))*(_forward._z*MaxPick) + _position._z;

   if( (LocalZ < (*chunk->second)(x0 + x*signeX, y0 + y*signeY)) || (LocalZ < (*chunk->second)(x0 + (x+1)*signeX, y0 + y*signeY)) ||  (LocalZ < (*chunk->second)(x0 + x*signeX, y0 + (y+1)*signeY)) || (LocalZ < (*chunk->second)(x0 + (x+1)*signeX, y0 + (y+1)*signeY)))

    {
    if (Distance < LastBest)
    {
     LastBest = Distance;
     newX = x0 + x*signeX;
     newY = y0 + y*signeY;
     }
     }
}


  if(newX == -1 && newY == -1)
  {return 0;}

    return((*chunk->second).getCoord(newX,newY));
    /*
   SelectedCoord  = std::make_pair(newX,newY);

return(innerCoordChunktoAbsolute(std::make_pair(Chunk::absoluteToChunkCoord(_position._x),Chunk::absoluteToChunkCoord(_position._y),
     selectedCoord));*/



  /*auto chunk = chunks.find(std::make_pair(x, y));
  assert(chunk != chunks.cend() && "Can't found corresponding chunk!");
  return chunk->second->getCoord(x, y, _target._z);

*/

}
