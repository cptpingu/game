#ifndef BLOCK_HH_
# define BLOCK_HH_

# include "Core/Container3D.hh"

# include <array>

/*!
** @class Block
**
** Class used to put block model into the game.
** Blocks are optimized when there are too closed
** (Only draw needed facet).
*/
class Block : public Core::Container3D<int>
{
  typedef Core::Container3D<int> super;
public:
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

public:
  Block(int x, int y, int z)
    : super(x, y, z),
      _up(0), _down(0),
      _left(0), _right(0),
      _front(0), _back(0),
      _highlights()
  {
  }

  void highlight(FaceType face, bool highlight) { assert(face >= none && face <= back && "Index out of bound!"); _highlights[face] = highlight; }
  bool isHighlighted(FaceType face) const { assert(face >= none && face <= back && "Index out of bound!"); return _highlights[face]; }
  /*!
  ** Each neighbour block is "pointed"
  */
public:
  Block* _up;
  Block* _down;
  Block* _left;
  Block* _right;
  Block* _front;
  Block* _back;
  std::array<bool, FaceType::back + 1> _highlights;
};






/*!
** Given x,y,z coords, get the block pointer.
**
** @param x X coord.
** @param y Y coord.
** @param z Z coord.
** @return A pointer on coord, or 0 if not found.
*/






#endif /* !BLOCK_HH_ */
