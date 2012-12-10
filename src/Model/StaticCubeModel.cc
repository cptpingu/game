#include "StaticCubeModel.hh"
#include "../Core/Assert.hh"

namespace Model
{
  CubeModel::CubeModel()
  {
  }

  CubeModel::~CubeModel()
  {
    release();
  }

  void
  CubeModel::init()
  {
    glGenBuffers(1, &_vboId);
    ASSERT_MSG(_vboId, "Vertex buffer initialisation failed!");
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Cube::vertices) +
                 sizeof(Cube::normals) +
                 sizeof(Cube::textures), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    sizeof(Cube::vertices),
                    Cube::vertices);
    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(Cube::vertices),
                    sizeof(Cube::normals),
                    Cube::normals);
    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(Cube::textures) + sizeof(Cube::normals),
                    sizeof(Cube::textures),
                    Cube::textures);
  }

  GLuint
  CubeModel::getVboId() const
  {
    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    return _vboId;
  }

  void
  CubeModel::release()
  {
    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    glDeleteBuffers(1, &_vboId);
  }
} // Model
