#ifndef CORE_VECTOR3D_HH_
# define CORE_VECTOR3D_HH_

# include "Container3D.hh"


namespace Core
{
  class Vector3D : public Container3D<double>
  {
    typedef Container3D<double> super;

  public:
    Vector3D();
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& v);
    Vector3D(const Vector3D& from, const Vector3D& to);
    Vector3D& operator=(const Vector3D& v);
    Vector3D& operator+=(const Vector3D& v);
    Vector3D operator+(const Vector3D& v) const;
    Vector3D& operator-=(const Vector3D& v);
    Vector3D operator-(const Vector3D& v) const;
    Vector3D& operator*=(const double a);
    Vector3D operator*(const double a) const;
    Vector3D& operator/=(const double a);
    Vector3D operator/(const double a) const;


    Vector3D crossProduct(const Vector3D& v) const;
    double length() const;
    Vector3D& normalize();


    double Norm(const Vector3D& v,int type);
    double distance(double x, double y, double z) const;
    double distance(const Vector3D& v) const;
    Vector3D mStar(const Vector3D& v) const;

    friend Vector3D operator*(const double a, const Vector3D& v);
  };
} // Core

#endif /* !CORE_VECTOR3D_HH_ */
