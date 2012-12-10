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
    _vboId = Model::Cube::init();
    ASSERT_MSG(_vboId, "Vertex buffer initialisation failed!");
  }

  std::string
  Cube::getShaderName() const
  {
    return "cube";
  }

  void
  Cube::specificDraw(const NeighbourMatrix& neighbours) const
  {
    ShadersManager& shaders = ShadersManager::getInstance();
    glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), isHighlight() ? 0.2 : 0.0);
    GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
    glVertexAttrib1f(attrib, 0.0);

    TextureManager& textures = TextureManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    ASSERT_MSG(_vboId, "Invalid vertex buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glNormalPointer(GL_FLOAT, 0, (void*)sizeof(Model::Cube::vertices));
    glTexCoordPointer(3, GL_FLOAT, 0, (void*)(sizeof(Model::Cube::vertices) + sizeof(Model::Cube::normals)));

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
      Core::Vector3D pos;
      /*Core::Vector3D direction;

      for int i =
      direction = current + (next - current).normalize()*t;

*/
     /* Core::Vector3D cubecenter((_x+1)*Block::SIZE/2.0,(_y+1)*Block::SIZE/2.0,(_z+1)*Block::SIZE/2.0);

      double centerD;
      centerD = (next - cubecenter).length();

      Core::Vector3D Repulse;
      Repulse = next - cubecenter;

      pos =

      */
      pos = next;

 if(current._x > (_x+1)*Block::SIZE && next._x < (_x+1)*Block::SIZE)
      {

          pos._x = (_x+1)*Block::SIZE + 0.005;

      //pos._y = pos._y/100;

      std::cout << "X+1"<<std::endl;
      }


      else if(current._x < _x*Block::SIZE && next._x > _x*Block::SIZE  )
      {
          pos._x = _x*Block::SIZE - 0.005;

      //pos._y = pos._y/100;
      std::cout << "X"<<std::endl;
      }


      else if(current._y > (_y+1)*Block::SIZE && next._y < (_y+1)*Block::SIZE)
      {
      pos._y = (_y+1)*Block::SIZE + 0.005;

      //pos._x = next._x;
      std::cout << "Y+1"<<std::endl;

      }


      else if(current._y < _y*Block::SIZE && next._y > _y*Block::SIZE)
      {
      pos._y = _y*Block::SIZE - 0.005;

      //pos._x = next._x;
      std::cout << "Y"<<std::endl;
      }






/*
      if(current._z > (_z+1)*Block::SIZE && next._z < (_z+1)*Block::SIZE)
       {
       pos._z = (_z+1)*Block::SIZE+ 0.05;

       //pos._y = next._y;

       std::cout << "Z+1"<<std::endl;
       }

       if(current._z < _z*Block::SIZE && next._z > _z*Block::SIZE)
      {
      pos._z = _z*Block::SIZE -0.05;

      //pos._x = next._x;
      std::cout << "Y"<<std::endl;
      }

*/







      return pos;
  }
} // Block
