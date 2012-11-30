#ifndef BLOCK_NEIGHBORMATRIX_HH_
# define BLOCK_NEIGHBORMATRIX_HH_

# include "../Core/Array3D.hh"

namespace Block
{
  class NeighbourMatrix : public Core::Array3D<int, 3>
  {
  private:
    typedef Core::Array3D<int, 3> super;

  public:
    NeighbourMatrix()
      : super()
    {
    }

//    int operator()(int x, int y, int z) const
//    {
//      return super(x, y, z);
//    }

//    int& operator()(int x, int y, int z)
//    {
//      return super(x, y, z);
//    }
  };
} // Block

#endif /* !BLOCK_NEIGHBORMATRIX_HH_ */
