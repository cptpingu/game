#ifndef BLOCK_NEIGHBOURMATRIX_HH_
# define BLOCK_NEIGHBOURMATRIX_HH_

# include "../Core/Array3D.hh"

namespace Block
{
  /*!
  ** Forward declaration for the "Basic" class.
  */
  class Basic;

  /*!
  ** @class NeighbourMatrix
  **
  ** Cube of 3x3x3 with coord from -1 to 1.
  */
  class NeighbourMatrix : public Core::Array3D<Basic*, 3>
  {
  private:
    typedef Core::Array3D<Basic*, 3> super;

  public:
    NeighbourMatrix()
      : super()
    {
    }

    /*!
    ** Transform a [0..2] system to a [-1..1] system.
    **
    ** @param x X coord.
    ** @param y Y coord.
    ** @param z Z coord.
    **
    ** @return Value at (x, y, z)
    */
    Basic* operator()(int x, int y, int z) const
    {
      assert(x >= -1 && "x out of bound");
      assert(x <= 1 && "x out of bound");
      assert(y >= -1 && "y out of bound");
      assert(y <= 1 && "y out of bound");
      assert(z >= -1 && "x out of bound");
      assert(z <= 1 && "x out of bound");
      return super::operator()(x + 1, y + 1, z + 1);
    }

    /*!
    ** Transform a [0..2] sytem to a [-1..1] system.
    **
    ** @param x X coord.
    ** @param y Y coord.
    ** @param z Z coord.
    **
    ** @return Value at (x, y, z)
    */
    Basic*& operator()(int x, int y, int z)
    {
      assert(x >= -1 && "x out of bound");
      assert(x <= 1 && "x out of bound");
      assert(y >= -1 && "y out of bound");
      assert(y <= 1 && "y out of bound");
      assert(z >= -1 && "x out of bound");
      assert(z <= 1 && "x out of bound");
      return super::operator()(x + 1, y + 1, z + 1);
    }

    /*!
    ** Convert a 3x3x3 matrix to an integer mask.
    ** @return A unique value.
    */
    int mask() const
    {
      int res = 0;
      int shift = 0;
      for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
          for (int k = -1; k <= 1; ++k)
            res += (!!operator()(i, j, k) << shift++);
      return res;
    }
  };
} // Block

#endif /* !BLOCK_NEIGHBOURMATRIX_HH_ */
