#ifndef BLOCK_BASIC_HH_
# define BLOCK_BASIC_HH_

# include "../Core/Container3D.hh"
# include "../Block/NeighbourMatrix.hh"
# include "../Core/Vector3D.hh"
# include "../Opengl.hh"
# include "../Model/MemoryPiece.hh"

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

    bool isNullIndex(int index) const;
    void highlight(FaceType face, bool highlight);
    bool isHighlighted(FaceType face) const;
    bool isHighlight() const;
    void resetHighlight();
    void draw(const Model::MemoryPiece& mem) const;
    void changeState(const NeighbourMatrix& neighbours);
    void selectionDraw() const;
    unsigned int getState() const;

  public:
    virtual std::string getShaderName() const;
    virtual void drawPickingBox(const Model::MemoryPiece& mem) const;
    virtual Core::Vector3D collision(const Core::Vector3D& current, const Core::Vector3D& next) const;

  private:
    void initPickingBox();
    virtual bool specificIsNullIndex(int index) const = 0;
    virtual void specificInit() = 0;
    virtual void specificDraw(const Model::MemoryPiece& mem) const = 0;
    virtual void specificChangeState(const NeighbourMatrix& neighbours) = 0;
    virtual Core::Vector3D specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const = 0;

  protected:
    id_type _id;
    std::array<bool, FaceType::back + 1> _highlights;
    bool _isHighlighted;
    GLuint  _pickingVBOId;
    GLuint  _vboId;
    unsigned int _pickingModelState;
    unsigned int _modelState;
    GLfloat _pickingColors[72];
  };
} // Block

#endif /* !BLOCK_BASIC_HH_ */
