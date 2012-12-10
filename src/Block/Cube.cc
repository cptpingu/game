#include "Cube.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include "../Model/StaticCubeModel.hh"

namespace Block
{
  Cube::Cube(int x, int y, int z)
    : super(x, y, z)
  {
  }

  Cube::~Cube()
  {
  }

  void
  Cube::specificInit()
  {
    _vboId = Model::CubeModel::getInstance().getVboId();
    ASSERT_MSG(_vboId, "Vertex buffer initialisation failed!");
  }

  std::string
  Cube::getShaderName() const
  {
    return "cube";
  }

  void
  Cube::specificDraw() const
  {
//    ShadersManager& shaders = ShadersManager::getInstance();
//    glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), isHighlight() ? 0.2 : 0.0);
//    GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
//    glVertexAttrib1f(attrib, 0.0);

//    TextureManager& textures = TextureManager::getInstance();
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

//    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
//    glBindBuffer(GL_ARRAY_BUFFER, _vboId);

//    glVertexPointer(3, GL_FLOAT, 0, 0);
//    glNormalPointer(GL_FLOAT, 0, (void*)sizeof(Model::Cube::vertices));
//    glTexCoordPointer(3, GL_FLOAT, 0, (void*)(sizeof(Model::Cube::vertices) + sizeof(Model::Cube::normals)));

    glPushMatrix();
    glTranslatef(_x * Block::SIZE + Block::SIZE / 2,
                 _y * Block::SIZE + Block::SIZE / 2,
                 _z * Block::SIZE + Block::SIZE / 2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glPopMatrix();
  }

  Core::Vector3D
  Cube::specificCollision(const Core::Vector3D& current, const Core::Vector3D& next) const
  {
    return current;
  }
} // Block
