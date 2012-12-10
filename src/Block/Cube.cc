#include "Cube.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"

namespace Block
{
  Cube::Cube(int x, int y, int z)
    : super(x, y, z)
  {
  }

  Cube::~Cube()
  {
  }

  std::string
  Cube::getShaderName() const
  {
    return "cube";
  }

  void
  Cube::specificDraw(const NeighbourMatrix& neighbours) const
  {
#define DRAW_FACE(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X4, Y4, Z4, N_X, N_Y, N_Z, HIGHLIGHT) \
    if (!neighbours(N_X, N_Y, N_Z))                                     \
    {                                                                   \
      glTexCoord2d(0, 0);                                               \
      glVertexAttrib1f(attrib, isHighlighted(HIGHLIGHT) ? 0.3 : 0.0);   \
      glVertex3d(X1 * Block::SIZE, Y1 * Block::SIZE, Z1 * Block::SIZE); \
      glTexCoord2d(1, 0);                                               \
      glVertexAttrib1f(attrib, isHighlighted(HIGHLIGHT) ? 0.3 : 0.0);   \
      glVertex3d(X2 * Block::SIZE, Y2 * Block::SIZE, Z2 * Block::SIZE); \
      glTexCoord2d(1, 1);                                               \
      glVertexAttrib1f(attrib, isHighlighted(HIGHLIGHT) ? 0.3 : 0.0);   \
      glVertex3d(X3 * Block::SIZE, Y3 * Block::SIZE, Z3 * Block::SIZE); \
      glTexCoord2d(0, 1);                                               \
      glVertexAttrib1f(attrib, isHighlighted(HIGHLIGHT) ? 0.3 : 0.0);   \
      glVertex3d(X4 * Block::SIZE, Y4 * Block::SIZE, Z4 * Block::SIZE); \
    }

    TextureManager& textures = TextureManager::getInstance();
    ShadersManager& shaders = ShadersManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);
    GLuint attrib = glGetAttribLocation(shaders.get(getShaderName()), "face_color");

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);
    glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), isHighlight() ? 0.2 : 0.0);
    glBegin(GL_QUADS);

    //par terre
    DRAW_FACE(0, 0, 0,
              1, 0, 0,
              1, 1, 0,
              0, 1, 0,
              0, 0, -1,
              Block::down);

    //face droite
    DRAW_FACE(0, 0, 1,
              0, 1, 1,
              0, 1, 0,
              0, 0, 0,
              -1, 0, 0,
              Block::right);

    //face gauche
    DRAW_FACE(1, 0, 1,
              1, 1, 1,
              1, 1, 0,
              1, 0, 0,
              1, 0, 0,
              Block::left);

    //face face
    DRAW_FACE(0, 1, 1,
              1, 1, 1,
              1, 1, 0,
              0, 1, 0,
              0, 1, 0,
              Block::front);

    //face derriere
    DRAW_FACE(0, 0, 1,
              1, 0, 1,
              1, 0, 0,
              0, 0, 0,
              0, -1, 0,
              Block::back);

    //face au ciel
    DRAW_FACE(0, 0, 1,
              1, 0, 1,
              1, 1, 1,
              0, 1, 1,
              0, 0, 1,
              Block::up);
#undef DRAW_FACE

    glEnd();

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
