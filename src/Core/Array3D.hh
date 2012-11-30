#ifndef CORE_ARRAY3D_HH_
# define CORE_ARRAY3D_HH_

# include "NonCopyable.hh"

# include <vector>
# include <cassert>

namespace Core
{
  /*!
  ** @struct Array3D
  **
  ** This class is used to emulate a fixed 3D array.
  */
  template <typename T, unsigned int LENGTH, unsigned int CAPACITY = LENGTH * LENGTH * LENGTH>
  struct Array3D : private Core::NonCopyable<std::vector<T> >,
                   public std::vector<T>
  {
  public:
    Array3D()
    {
      std::vector<T>::reserve(CAPACITY);
      std::vector<T>::resize(CAPACITY);
    }

    T operator()(int x, int y, int z) const
    {
      assert(x >= 0 && "Invalid range");
      assert(y >= 0 && "Invalid range");
      assert(z >= 0 && "Invalid range");
      assert(x + y * LENGTH + z * LENGTH * LENGTH < std::vector<T>::size() && "Index out of bound");
      return std::vector<T>::operator[](x + y * LENGTH + z * LENGTH * LENGTH);
    }

    T& operator()(int x, int y, int z)
    {
      assert(x >= 0 && "Invalid range");
      assert(y >= 0 && "Invalid range");
      assert(z >= 0 && "Invalid range");
      assert(x + y * LENGTH + z * LENGTH * LENGTH < std::vector<T>::size() && "Index out of bound");
      return std::vector<T>::operator[](x + y * LENGTH + z * LENGTH * LENGTH);
    }

    T operator[](int) const = delete;
    T& operator[](int) = delete;
  };
} // Core

#endif /* !CORE_ARRAY3D_HH_ */
