#include "Vector3D.hh"
#include <cmath>

Vector3D::Vector3D()
  : _x(0), _y(0), _z(0)
{
}

Vector3D::Vector3D(double x, double y, double z)
  : _x(x), _y(y), _z(z)
{
}

Vector3D::Vector3D(const Vector3D& v)
  : _x(v._x), _y(v._y), _z(v._z)
{
}

Vector3D::Vector3D(const Vector3D& from,const Vector3D& to)
  : _x(to._x - from._x), _y(to._y - from._y), _z(to._z - from._z)
{
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
    _x = v._x;
    _y = v._y;
    _z = v._z;
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
    _x += v._x;
    _y += v._y;
    _z += v._z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D & v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D & Vector3D::operator-=(const Vector3D & v)
{
    _x -= v._x;
    _y -= v._y;
    _z -= v._z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D& Vector3D::operator*=(const double a)
{
    _x *= a;
    _y *= a;
    _z *= a;
    return *this;
}

Vector3D Vector3D::operator*(const double a) const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator*(const double a,const Vector3D& v)
{
    return Vector3D(v._x * a, v._y * a, v._z * a);
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

double Vector3D::length() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3D& Vector3D::normalize()
{
    (*this) /= length();
    return (*this);
}
Vector3D Vector3D::mStar(const Vector3D& v) const
{
    Vector3D t;
    t._x = _x * v._x;
    t._y = _y * v._y;
    t._z = _z * v._z;
    return t;
}


