#ifndef MODEL_STATICCUBEMODEL_HH_
# define MODEL_STATICCUBEMODEL_HH_

# include "../Opengl.hh"
# include "../Core/Singleton.hh"

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
  ** array is 108 floats (36 * 3 = 108).
  */
  namespace Cube
  {
    static const GLfloat vertices[] =
    {
      +1, +1, +1,  -1, +1, +1,  -1, -1, +1, // v0-v1-v2 (up)
      -1, -1, +1,  +1, -1, +1,  +1, +1, +1, // v2-v3-v0

      +1, +1, +1,  +1, -1, +1,  +1, -1, -1, // v0-v3-v4 (right)
      +1, -1, -1,  +1, +1, -1,  +1, +1, +1, // v4-v5-v0

      +1, +1, +1,  +1, +1, -1,  -1, +1, -1, // v0-v5-v6 (back)
      -1, +1, -1,  -1, +1, +1,  +1, +1, +1, // v6-v1-v0

      -1, +1, +1,  -1, +1, -1,  -1, -1, -1, // v1-v6-v7 (left)
      -1, -1, -1,  -1, -1, +1,  -1, +1, +1, // v7-v2-v1

      -1, -1, -1,  +1, -1, -1,  +1, -1, +1, // v7-v4-v3 (front)
      +1, -1, +1,  -1, -1, +1,  -1, -1, -1, // v3-v2-v7

      +1, -1, -1,  -1, -1, -1,  -1, +1, -1, // v4-v7-v6 (down)
      -1, +1, -1,  +1, +1, -1,  +1, -1, -1  // v6-v5-v4
    };

    static const GLfloat normals[] =
    {
      0, 0, 1,   0, 0, 1,   0, 0, 1,        // v0-v1-v2 (up)
      0, 0, 1,   0, 0, 1,   0, 0, 1,        // v2-v3-v0

      1, 0, 0,   1, 0, 0,   1, 0, 0,        // v0-v3-v4 (right)
      1, 0, 0,   1, 0, 0,   1, 0, 0,        // v4-v5-v0

      0, 1, 0,   0, 1, 0,   0, 1, 0,        // v0-v5-v6 (back)
      0, 1, 0,   0, 1, 0,   0, 1, 0,        // v6-v1-v0

      -1, 0, 0,  -1, 0, 0,  -1, 0, 0,       // v1-v6-v7 (left)
      -1, 0, 0,  -1, 0, 0,  -1, 0, 0,       // v7-v2-v1

      0,-1, 0,   0,-1, 0,   0,-1, 0,        // v7-v4-v3 (front)
      0,-1, 0,   0,-1, 0,   0,-1, 0,        // v3-v2-v7

      0, 0,-1,   0, 0,-1,   0, 0,-1,        // v4-v7-v6 (down)
      0, 0,-1,   0, 0,-1,   0, 0,-1         // v6-v5-v4
    };

    static const GLfloat textures[] =
    {
      1, 1, 0,  0, 1, 0,  0, 0, 0,          // v0-v1-v2 (up)
      0, 0, 0,  1, 0, 0,  1, 1, 0,          // v2-v3-v0

      1, 1, 0,  0, 1, 0,  0, 0, 0,          // v0-v3-v4 (right)
      0, 0, 0,  1, 0, 0,  1, 1, 0,          // v4-v5-v0

      0, 1, 0,  0, 0, 0,  1, 0, 0,          // v0-v5-v6 (back)
      1, 0, 0,  1, 1, 0,  0, 1, 0,          // v6-v1-v0

      0, 1, 0,  0, 0, 0,  1, 0, 0,          // v1-v6-v7 (left)
      1, 0, 0,  1, 1, 0,  0, 1, 0,          // v7-v2-v1

      0, 0, 0,  1, 0, 0,  1, 1, 0,          // v7-v4-v3 (front)
      1, 1, 0,  0, 1, 0,  0, 0, 0,          // v3-v2-v7

      1, 1, 0,  0, 1, 0,  0, 0, 0,          // v4-v7-v6 (down)
      0, 0, 0,  1, 0, 0,  1, 1, 0           // v6-v5-v4
    };
  } // Cube

  class CubeModel : public Core::Singleton<CubeModel>
  {
  public:
    CubeModel();
    ~CubeModel();

    void init();
    GLuint getVboId() const;
    void release();
    void bindVBO(int index) const;

  private:
    GLuint _vboId;
  };
} // Model

#endif /* !MODEL_STATICCUBEMODEL_HH_ */
