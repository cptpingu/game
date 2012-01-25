#include "Block.hh"
#include "TextureManager.hh"
#include <GL/gl.h>
#include <GL/glu.h>

Block::Block()
    :_x(0), _y(0), _z(0), _size(1)
{
}

Block::Block(int x, int y, int z, int size)
    :_x(x), _y(y), _z(z), _size(size)
{
}




