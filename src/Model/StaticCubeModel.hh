#ifndef MODEL_STATICCUBEMODEL_HH_
# define MODEL_STATICCUBEMODEL_HH_

# include "../Opengl.hh"
# include "../Core/Singleton.hh"
# include "../Core/Assert.hh"
# include "MemoryPiece.hh"

namespace Model
{
  /*!
  ** CUBE
  **
  **    v1------v0
  **   /|      /|
  **  v2------v3|
  **  | |     | |
  **  | v6----|-v5
  **  |/      |/
  **  v7------v4
  **
  ** A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
  ** of 36 vertices (6 sides * 2 triangles * 3 vertices = 36 vertices). And, each
  ** vertex is 3 components (x, y, z) of floats, therefore, the size of vertex
  ** array is 108 floats (36 * 3 = 108). 72 points in compact mode.
  */
  namespace Cube
  {
    static const GLfloat vertices[] =
    {
      +1, +1, +1,  -1, +1, +1,  -1, -1, +1,  +1, -1, +1, // v0-v1-v2-v3 (up)
      +1, +1, +1,  +1, -1, +1,  +1, -1, -1,  +1, +1, -1, // v0-v3-v4-v5 (right)
      +1, +1, +1,  +1, +1, -1,  -1, +1, -1,  -1, +1, +1, // v0-v5-v6-v1 (back)
      -1, +1, +1,  -1, +1, -1,  -1, -1, -1,  -1, -1, +1, // v1-v6-v7-v2 (left)
      -1, -1, -1,  +1, -1, -1,  +1, -1, +1,  -1, -1, +1, // v7-v4-v3-v2 (front)
      +1, -1, -1,  -1, -1, -1,  -1, +1, -1,  +1, +1, -1  // v4-v7-v6-v5 (down)
    };

    static const GLfloat normals[] =
    {
      +0, +0, +1,   +0, +0, +1,   +0, +0, +1,  +0, +0, +1, // v0-v1-v2-v3 (up)
      +1, +0, +0,   +1, +0, +0,   +1, +0, +0,  +1, +0, +0, // v0-v3-v4-v5 (right)
      +0, +1, +0,   +0, +1, +0,   +0, +1, +0,  +0, +1, +0, // v0-v5-v6-v1 (back)
      -1, +0, +0,   -1, +0, +0,   -1, +0, +0,  -1, +0, +0, // v1-v6-v7-v2 (left)
      +0, -1, +0,   +0, -1, +0,   +0, -1, +0,  +0, -1, +0, // v7-v4-v3-v2 (front)
      +0, +0, -1,   +0, +0, -1,   +0, +0, -1,  +0, +0, -1  // v4-v7-v6-v5 (down)
    };

    static const GLfloat textures[] =
    {
      1, 1, 0,  0, 1, 0,  0, 0, 0,  1, 0, 0, // v0-v1-v2-v3 (up)
      1, 1, 0,  0, 1, 0,  0, 0, 0,  1, 0, 0, // v0-v3-v4-v5 (right)
      0, 1, 0,  0, 0, 0,  1, 0, 0,  1, 1, 0, // v0-v5-v6-v1 (back)
      0, 1, 0,  0, 0, 0,  1, 0, 0,  1, 1, 0, // v1-v6-v7-v2 (left)
      0, 0, 0,  1, 0, 0,  1, 1, 0,  0, 1, 0, // v7-v4-v3-v2 (front)
      1, 1, 0,  0, 1, 0,  0, 0, 0,  1, 0, 0  // v4-v7-v6-v5 (down)
    };

    static const GLubyte indices[] =
    {
      0, 1, 2,    2, 3, 0,  // up
      4, 5, 6,    6, 7, 4,  // right
      8, 9,10,   10,11, 8,  // back
      12,13,14,  14,15,12,  // left
      16,17,18,  18,19,16,  // front
      20,21,22,  22,23,20   // down
    };

    static const unsigned int emptyIndex = 63;
  } // Cube

  class CubeModel : public Core::Singleton<CubeModel>
  {
  public:
    CubeModel();
    ~CubeModel();

    void init();
    GLuint getVboId() const;
    void release();
    const MemoryPiece& bindVBO(int index) const;

  private:
    GLuint           _vboId;
    GLuint           _iboId;
    MemoryPieces<64> _computedIndices;
  };
} // Model

#endif /* !MODEL_STATICCUBEMODEL_HH_ */
