#ifndef BLOCK_BASIC_HH_
# define BLOCK_BASIC_HH_

# include "../Core/Container3D.hh"
# include "../Block/NeighbourMatrix.hh"
# include "../Core/Vector3D.hh"
# include "../Opengl.hh"

# include <array>
# include <string>

/*!
** @class Basic
**
** Class used to put block model into the game.
*/
namespace Block
{
  typedef Core::Container3D<GLuint> id_type;
  static const int SIZE = 2;
  static const double HALF_SIZE = SIZE / 2;

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

  /*!
  ** @class Basic
  **
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
  class Basic : public Core::Container3D<int>
  {
    typedef Core::Container3D<int> super;

  public:
    Basic(int x, int y, int z);
    virtual ~Basic();

  public:
    void registerBlock();
    void unregisterBlock();
    void init();

    void highlight(FaceType face, bool highlight);
    bool isHighlighted(FaceType face) const;
    bool isHighlight() const;
    void resetHighlight();
    void draw(const NeighbourMatrix& neighbours) const;
    void selectionDraw() const;

  public:
    virtual std::string getShaderName() const;
    virtual void drawPickingBox() const;
    virtual Core::Vector3D collision(const Core::Vector3D& current, const Core::Vector3D& next) const;

  private:
    void initPickingBox();
    virtual void specificInit() = 0;
    virtual void specificDraw(const NeighbourMatrix& neighbours) const = 0;
    virtual Core::Vector3D specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const = 0;

  protected:
    id_type _id;
    std::array<bool, FaceType::back + 1> _highlights;
    GLuint  _pickingVBOId;
    GLfloat _pickingColors[108];
    GLuint  _vboId;

  protected:
    static const GLfloat _vertices[108];
    static const GLfloat _normals[108];
    static const GLfloat _textures[108];
  };
} // Block

#endif /* !BLOCK_BASIC_HH_ */
