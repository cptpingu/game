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

   SDL_WM_GrabInput(SDL_GRAB_ON);
   SDL_ShowCursor(SDL_DISABLE);
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



  int MaxPick = 50;
  int Nbx = fabs(MaxPick*_forward._x)+1;
  int Nby = fabs(MaxPick*_forward._y)+1;

  int newX = 0;
  int newY = 0;



  int x0 = static_cast<int>(_position._x)%(Chunk::SIZE-1);
  int y0 = static_cast<int>(_position._y)%(Chunk::SIZE-1);

  x0 = (Chunk::SIZE-1)/2*(x0 <0) + x0 + ((Chunk::SIZE-1)/2)*(1-((x0 / (Chunk::SIZE-1)/2)) )*(x0>=0) + ((Chunk::SIZE-1)/2)*(-(x0 / (Chunk::SIZE-1)/2) )*(x0<0);

  y0 = (Chunk::SIZE-1)/2*(y0 <0) + y0   + ((Chunk::SIZE-1)/2)*(1-((y0 / (Chunk::SIZE-1)/2)) )*(y0>=0) + ((Chunk::SIZE-1)/2)*(-(y0 / (Chunk::SIZE-1)/2) )*(y0<0);

   /*std::cout << _position._x << std::endl;
   std::cout << _position._y << std::endl;
   std::cout << _position._z << std::endl;*/


  int signeX = (_forward._x > 0) - (_forward._x < 0);
  int signeY = (_forward._y > 0) - (_forward._y < 0);

 int Vx = 0;
 int Vy = 0;
 double Vz = 0;


 std::cout << _forward._y << std::endl;
 std::cout << _forward._x << std::endl;

 if (fabs(_forward._x) >fabs(_forward._y))
 //if (Nbx>Nby)
 {
   for (int x = 0;x < Nbx;++x)
    {

       Vy = static_cast<int>(signeX*x*(_forward._y/ _forward._x));
       Vz = _forward._z * sqrt( x*x + (Vy*_forward._y/_forward._x)*(Vy*_forward._y/_forward._x));



       if((x0 + x*signeX) > Chunk::SIZE-1 || (x*signeX + x0) < 0 || (y0 + Vy) < 0 || (y0 + Vy) > Chunk::SIZE-1)
       {
       std::cout << "out" << std::endl;
       chunk = chunks.find(std::make_pair(Chunk::absoluteToChunkCoord(_position._x + x*signeX),Chunk::absoluteToChunkCoord(_position._y + Vy)));

       int x0 = static_cast<int>(_position._x + x*signeX)%(Chunk::SIZE-1);
       int y0 = static_cast<int>(_position._y + Vy)%(Chunk::SIZE-1);

       x0 = (Chunk::SIZE-1)/2*(x0 <0) + x0 + ((Chunk::SIZE-1)/2)*(1-((x0 / (Chunk::SIZE-1)/2)) )*(x0>=0) + ((Chunk::SIZE-1)/2)*(-(x0 / (Chunk::SIZE-1)/2) )*(x0<0);

       y0 = (Chunk::SIZE-1)/2*(y0 <0) + y0   + ((Chunk::SIZE-1)/2)*(1-((y0 / (Chunk::SIZE-1)/2)) )*(y0>=0) + ((Chunk::SIZE-1)/2)*(-(y0 / (Chunk::SIZE-1)/2) )*(y0<0);


       Vy = 0;
       Nbx = Nbx - x;
       x = 0;
       }

       if( _position._z + Vz <(*chunk->second)(x0 + x*signeX, y0 + Vy))
       {
       newX = x0 + x*signeX;
       newY = y0 + Vy;

       break;
       }
       else
       {
       newX = x0;
       newY = y0;
       }
    }
 }
 else
 {
     for (int y = 0;y < Nby;++y)
     {
        Vx = static_cast<int>(signeY*y*(_forward._x/ _forward._y));
        Vz = _forward._z * sqrt( (Vx*_forward._x / _forward._y)*(Vx*_forward._x / _forward._y) + y*y);


        if((x0 + Vx) > Chunk::SIZE-1 || (Vx + x0) < 0 || (y0 + y*signeY) < 0 || (y0 + y*signeY) > Chunk::SIZE-1)
        {
        std::cout << "out" << std::endl;
        chunk = chunks.find(std::make_pair(Chunk::absoluteToChunkCoord(_position._x + Vx),Chunk::absoluteToChunkCoord(_position._y + y*signeY)));

        int x0 = static_cast<int>(_position._x + Vx)%(Chunk::SIZE-1);
        int y0 = static_cast<int>(_position._y + y*signeY)%(Chunk::SIZE-1);

        x0 = (Chunk::SIZE-1)/2*(x0 <0) + x0 + ((Chunk::SIZE-1)/2)*(1-((x0 / (Chunk::SIZE-1)/2)) )*(x0>=0) + ((Chunk::SIZE-1)/2)*(-(x0 / (Chunk::SIZE-1)/2) )*(x0<0);

        y0 = (Chunk::SIZE-1)/2*(y0 <0) + y0   + ((Chunk::SIZE-1)/2)*(1-((y0 / (Chunk::SIZE-1)/2)) )*(y0>=0) + ((Chunk::SIZE-1)/2)*(-(y0 / (Chunk::SIZE-1)/2) )*(y0<0);

        Vx = 0;

        Nby = Nby - y;
        y = 0;
        }



      if( _position._z + Vz <(*chunk->second)(x0 + Vx, y0 + y*signeY))
      {
       newX = x0 + Vx;
       newY = y0 + y*signeY;

       break;
      }
      else
      {
       newX = x0;
       newY = y0;
      }

     }
}
/* std::cout << "Coord" << std::endl;
 std::cout <<newX << " " << newY << std::endl;*/
return((*chunk->second).getCoord(newX,newY));


}
