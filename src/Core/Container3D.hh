#ifndef CORE_CONTAINER3D_HH_
# define CORE_CONTAINER3D_HH_

# include "Traits.hh"
# include <cassert>

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
      assert(!isPointer<T>::value); // FIXME
    }

    Container3D(T x, T y, T z)
      : _x(x), _y(y), _z(z)
    {
    }

    bool operator==(const Container3D<T>& container) const
    {
      return _x == container._x && _y == container._y && _z == container._z;
    }

    bool operator!=(const Container3D<T>& container) const
    {
      return !operator==(container);
    }

  public:
    T _x;
    T _y;
    T _z;
  };
} // Core

#endif /* CORE_CONTAINER3D_HH_ */
