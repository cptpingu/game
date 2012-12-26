#ifndef BLOCK_CUBE_HH_
# define BLOCK_CUBE_HH_

# include "Basic.hh"
# include "../Model/MemoryPiece.hh"

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
    virtual bool specificIsNullIndex(int index) const;
    virtual void specificInit();
    virtual void specificDraw(const Model::MemoryPiece& mem) const;
    virtual void specificChangeState(const NeighbourMatrix& neighbours);
    virtual Core::Vector3D specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const;
  };
} // Block

#endif /* !BLOCK_CUBE_HH_ */
