#include "Vector3D.hh"
#include <cmath>
#include <stdlib.h>

namespace Core
{
  Vector3D::Vector3D()
    : super(0, 0, 0)
  {
  }

  Vector3D::Vector3D(double x, double y, double z)
    : super(x, y, z)
  {
  }

  Vector3D::Vector3D(const Vector3D& v)
    : super(v._x, v._y, v._z)
  {
  }

  Vector3D::Vector3D(const Vector3D& from,const Vector3D& to)
    : super(to._x - from._x, to._y - from._y, to._z - from._z)
  {
  }

  Vector3D&
  Vector3D::operator=(const Vector3D& v)
  {
    _x = v._x;
    _y = v._y;
    _z = v._z;
    return *this;
  }

  Vector3D&
  Vector3D::operator+=(const Vector3D& v)
  {
    _x += v._x;
    _y += v._y;
    _z += v._z;
    return *this;
  }

  Vector3D
  Vector3D::operator+(const Vector3D & v) const
  {
    Vector3D t = *this;
    t += v;
    return t;
  }

  Vector3D&
  Vector3D::operator-=(const Vector3D & v)
  {
    _x -= v._x;
    _y -= v._y;
    _z -= v._z;
    return *this;
  }

  Vector3D
  Vector3D::operator-(const Vector3D& v) const
  {
    Vector3D t = *this;
    t -= v;
    return t;
  }

  Vector3D&
  Vector3D::operator*=(const double a)
  {
    _x *= a;
    _y *= a;
    _z *= a;
    return *this;
  }

  Vector3D
  Vector3D::operator*(const double a) const
  {
    Vector3D t = *this;
    t *= a;
    return t;
  }

  Vector3D& Vector3D::operator/=(const double a)
  {
    _x /= a;
    _y /= a;
    _z /= a;
    return *this;
  }

  Vector3D Vector3D::operator/(const double a) const
  {
    Vector3D t = *this;
    t /= a;
    return t;
  }

  Vector3D Vector3D::crossProduct(const Vector3D& v) const
  {
    Vector3D t;
    t._x = _y * v._z - _z * v._y;
    t._y = _z * v._x - _x * v._z;
    t._z = _x * v._y - _y * v._x;
    return t;
  }

  double
  Vector3D::length() const
  {
    return sqrt(_x * _x + _y * _y + _z * _z);
  }

  Vector3D&
  Vector3D::normalize()
  {
    (*this) /= length();
    return (*this);
  }

  Vector3D
  Vector3D::mStar(const Vector3D& v) const
  {
    Vector3D t;
    t._x = _x * v._x;
    t._y = _y * v._y;
    t._z = _z * v._z;
    return t;
  }

  double
  Vector3D::distance(const Vector3D& v) const
  {
    return distance(v._x, v._y, v._z);
  }

  double
  Vector3D::distance(double x, double y, double z) const
  {
    return sqrt((_x - x) * (_x - x) +
                (_y - y) * (_y - y) +
                (_z * z) * (_z * z));
  }

  Vector3D operator*(const double a,const Vector3D& v)
  {
    return Vector3D(v._x * a, v._y * a, v._z * a);
  }

  double
  Vector3D::Norm(const Vector3D& v,int type)
  {
    double norm = -1;
    if(type == 1)
      norm = fabs(v._x)+fabs(v._x) + fabs(v._y);
    if(type == 2)
      norm = v._x*v._x+v._y*v._y+v._z*v._z;
    if (type == 0)
    {
      if(fabs(v._x)>fabs(v._y))
        norm = fabs(v._x);
      else
        norm = fabs(v._y);
      if(fabs(v._z) >norm)
        norm = fabs(v._z);

    }

    return(norm);
  }
} // Core
