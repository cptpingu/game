#ifndef ARRAY2D_HH_
# define ARRAY2D_HH_

# include "NonCopyable.hh"
# include <vector>

namespace Core
{
  template <typename T, int LENGTH, int CAPACITY = LENGTH * LENGTH>
  struct Array2D : private Core::NonCopyable<std::vector<T> >,
                   public std::vector<T>
  {
  public:
    Array2D()
    {
      std::vector<T>::reserve(CAPACITY);
      std::vector<T>::resize(CAPACITY);
    }

    T operator()(int x, int y) const
    {
      return std::vector<T>::operator[](x + y * LENGTH);
    }

    T& operator()(int x, int y)
    {
      return std::vector<T>::operator[](x + y * LENGTH);
    }

    T operator[](int) const = delete;
    T& operator[](int) = delete;
  };
} // Core

#endif /* !ARRAY2D_HH_ */
