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
    virtual bool specificIsNullIndex(int index) const;
    virtual void specificInit();
    virtual void specificDraw() const;
    virtual Core::Vector3D specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const;
  };
} // Block

#endif /* !BLOCK_TRIANGLE_HH_ */
