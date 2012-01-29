#ifndef BLOCK_HH_
# define BLOCK_HH_

# include "Core/Container3D.hh"

class Block : public Core::Container3D<int>
{
  typedef Core::Container3D<int> super;
public:
    static const int SIZE = 2;
public:
  Block(int x, int y, int z)
    : super(x, y, z),
      _up(0), _down(0),
      _left(0), _right(0),
      _front(0), _back(0)
  {
  }

public:
  Block* _up;
  Block* _down;
  Block* _left;
  Block* _right;
  Block* _front;
  Block* _back;
};

#endif /* !BLOCK_HH_ */
