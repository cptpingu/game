#ifndef BLOCK_CUBE_HH_
# define BLOCK_CUBE_HH_

# include "Basic.hh"

namespace Block
{
  class Cube : public Basic
  {
  private:
    typedef Basic super;

  public:
    Cube(int x, int y, int z);
    virtual ~Cube();

  public:
    virtual std::string getShaderName() const;

  private:
    virtual void specificDraw(const NeighbourMatrix& neighbors) const;
  };
} // Block

#endif /* !BLOCK_CUBE_HH_ */
