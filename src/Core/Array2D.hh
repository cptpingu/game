#ifndef ARRAY2D_HH_
# define ARRAY2D_HH_

# include "NonCopyable.hh"
# include "Assert.hh"
# include <vector>


namespace Core
{
  /*!
  ** @struct Array2D
  **
  ** This class is used to emulate a fixed 2D array.
  */
  template <typename T, unsigned int LENGTH, unsigned int CAPACITY = LENGTH * LENGTH>
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
      ASSERT_MSG(x >= 0, "Invalid range x = " << x);
      ASSERT_MSG(y >= 0, "Invalid range y = " << y);
      ASSERT_MSG(x + y * LENGTH < std::vector<T>::size(),
                 "Index out of bound, index is "
                 << x + y * LENGTH
                 << " but max size is " << std::vector<T>::size());
      return std::vector<T>::operator[](x + y * LENGTH);
    }

    T& operator()(int x, int y)
    {
      ASSERT_MSG(x >= 0, "Invalid range x = " << x);
      ASSERT_MSG(y >= 0, "Invalid range y = " << y);
      ASSERT_MSG(x + y * LENGTH < std::vector<T>::size(),
                 "Index out of bound, index is "
                 << x + y * LENGTH
                 << " but max size is " << std::vector<T>::size());
      return std::vector<T>::operator[](x + y * LENGTH);
    }

    T operator[](int) const = delete;
    T& operator[](int) = delete;
  };
} // Core

#endif /* !ARRAY2D_HH_ */
