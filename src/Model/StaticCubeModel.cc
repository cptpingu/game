#include "StaticCubeModel.hh"
#include "../Core/Assert.hh"
#include <algorithm>
#include <cstring>

namespace Model
{
  namespace
  {
    int copyIndices(GLubyte* indices, int offset, bool tab[6])
    {
      int nb = 0;
      for (int i = 0; i < 6; ++i)
      {
        if (tab[i])
        {
	  std::memcpy(indices + offset, Model::Cube::indices + (i * 6), 6);
          indices += 6;
          nb += 6;
        }
      }
      return nb;
    }

    int initAllIndices(GLubyte* indices, int offset, unsigned char nb_zero,
                       MemoryPieces<64>& computedIndices)
    {
      ASSERT_MSG(nb_zero <= 6, "nb_zero: " << nb_zero);
      bool tab[6] = {true, true, true, true, true, true};
      for (int i = 0; i < nb_zero; ++i)
        tab[i] = false;

      int nb = 0;
      do
      {
        computedIndices.last().from = offset + nb;
        computedIndices.last().size = copyIndices(indices + nb, offset, tab);
        nb += computedIndices.last().size;
        computedIndices.next();
      }
      while (std::next_permutation(tab, tab + 6));

      return nb;
    }

    void initAllIndices2(GLubyte* indices, MemoryPieces<64>& computedIndices)
    {
      int nb = 0;
      for (int i = 0; i <= 6; ++i)
        nb += initAllIndices(indices, nb, i, computedIndices);
    }
  } // namespace

  CubeModel::CubeModel()
    : _vboId(0),
      _iboId(0)
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

    GLubyte* indices = new GLubyte[1152];
    initAllIndices2(indices, _computedIndices);
    glGenBuffers(1, &_iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1152, indices, GL_STATIC_DRAW);
    delete indices;
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
    ASSERT_MSG(_iboId, "Invalid index buffer!");
    glDeleteBuffers(1, &_vboId);
    glDeleteBuffers(1, &_iboId);
  }

  const MemoryPiece&
  CubeModel::bindVBO(int index) const
  {
    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    ASSERT_MSG(_iboId, "Invalid index buffer!");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
    glIndexPointer(GL_UNSIGNED_BYTE, 0, 0);
    return _computedIndices[index];
  }
} // Model
