#ifndef CORE_CONTAINER3D_HH_
# define CORE_CONTAINER3D_HH_

namespace Core
{
  /*!
  ** @class Container3D
  **
  ** Generic way to store 3D values.
  */
  template <typename T>
  class Container3D
  {
  public:
    typedef T type;

  public:
    Container3D()
      : _x(), _y(), _z()
    {
    }

    Container3D(T x, T y, T z)
      : _x(x), _y(y), _z(z)
    {
    }

  public:
    T _x;
    T _y;
    T _z;
  };
} // Core

#endif /* CORE_CONTAINER3D_HH_ */
