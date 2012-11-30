#ifndef BLOCK_BASIC_HH_
# define BLOCK_BASIC_HH_

# include "../Core/Container3D.hh"
# include "../Block/NeighborMatrix.hh"

# include <array>
# include <string>

/*!
** @class Basic
**
** Class used to put block model into the game.
*/
namespace Block
{
  static const int SIZE = 2;

  enum FaceType
  {
    none = 0,
    up,
    down,
    left,
    right,
    front,
    back
  };

  class Basic : public Core::Container3D<int>
  {
    typedef Core::Container3D<int> super;

  public:
    Basic(int x, int y, int z);
    virtual ~Basic();

  public:
    void highlight(FaceType face, bool highlight);
    bool isHighlighted(FaceType face) const;
    void resetHighlight();

    void draw(const NeighborMatrix& neighbors) const;

    virtual std::string getShaderName() const;

  private:
    virtual void specificDraw(const NeighborMatrix& neighbors) const = 0;

  private:
    std::array<bool, FaceType::back + 1> _highlights;
  };
} // Block

#endif /* !BLOCK_BASIC_HH_ */
