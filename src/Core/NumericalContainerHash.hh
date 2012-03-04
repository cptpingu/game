#ifndef NUMERICALCONTAINERHASH_HH_
# define NUMERICALCONTAINERHASH_HH_

namespace Core
{
  /*!
  ** @class NumericalContainerHash
  **
  ** Hash class for std::unorderd_map used with Container3D.
  */
  template <typename T>
  class NumericalContainerHash : public std::unary_function<Core::Container3D<T>, size_t>
  {
  public:
    size_t operator()(const Core::Container3D<T>& p) const
    {
      size_t m(1000003), x(0x345678), y(hash(p._x));
      x = (x ^ y) * m;
      m += 82524;
      y = hash(p._y);
      x = (x ^ y) * m;
      m += 82522;
      y = hash(p._z);
      x = (x ^ y) * m;
      return x + 97531;
    }

  private:
    size_t hash(T i) const
    {
      static std::hash<size_t> _hash;
      return _hash(i);
    }
  };
} // Core

#endif /* !NUMERICALCONTAINERHASH_HH_ */
