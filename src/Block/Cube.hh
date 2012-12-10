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
    virtual void specificInit();
    virtual void specificDraw(const NeighbourMatrix& neighbors) const;
    virtual Core::Vector3D specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const;
  };
} // Block

#endif /* !BLOCK_CUBE_HH_ */
