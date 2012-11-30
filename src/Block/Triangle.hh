#ifndef BLOCK_TRIANGLE_HH_
# define BLOCK_TRIANGLE_HH_

# include "Basic.hh"

namespace Block
{
  class Triangle : public Basic
  {
  private:
    typedef Basic super;

  public:
    Triangle(int x, int y, int z);
    virtual ~Triangle();

  public:
    virtual std::string getShaderName() const;

  private:
    virtual void specificDraw(const NeighbourMatrix& neighbours) const;
  };
} // Block

#endif /* !BLOCK_TRIANGLE_HH_ */
