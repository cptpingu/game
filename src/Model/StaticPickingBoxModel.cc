#include "StaticPickingBoxModel.hh"
#include "../Core/Assert.hh"

namespace Model
{
  PickingBoxModel::PickingBoxModel()
  {
  }

  PickingBoxModel::~PickingBoxModel()
  {
    release();
  }

  void
  PickingBoxModel::init()
  {
    glGenBuffers(1, &_vboId);
    ASSERT_MSG(_vboId, "Vertex buffer initialisation failed!");
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(PickingBox::vertices), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    sizeof(PickingBox::vertices),
                    PickingBox::vertices);
  }

  GLuint
  PickingBoxModel::getVboId() const
  {
    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    return _vboId;
  }

  void
  PickingBoxModel::release()
  {
    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    glDeleteBuffers(1, &_vboId);
  }
} // Model
