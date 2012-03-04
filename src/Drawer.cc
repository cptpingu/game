#include "Map.hh"
#include "Drawer.hh"
#include "SolTriangle.hh"
#include "Block.hh"
#include "TextureManager.hh"
#include "ShadersManager.hh"
#include "Opengl.hh"
#include "Architecte.hh"


#include <vector>
#include <sstream>

//Le fonctionnement idéal du drawer => il recoit des listes d'objets typés et dessine les objets OPEN_GL correspondants
//Il n'est pas censé échanger quoi que ce soit avec le reste , c'est le côté open GL du programme.
namespace
{
  void draw(const Map::blocks_type& blocks)
  {


    TextureManager& textures = TextureManager::getInstance();
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    auto end = blocks.end();
    for (auto it = blocks.begin(); it != end; ++it)
    {
      glPushMatrix();
      glTranslatef((*it)->_x * Block::SIZE, (*it)->_y * Block::SIZE, (*it)->_z * Block::SIZE);
      glBegin(GL_QUADS);

      //par terre
      if (!(*it)->_down)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
      }

      //face droite
      if (!(*it)->_right)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2,-Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, 0);
      }

      //face gauche
      if (!(*it)->_left)
      {
        glTexCoord2d(0, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, 0);
      }

      //face face
      if (!(*it)->_front)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
      }

      //face derriere
      if (!(*it)->_back)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, 0);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
      }

      //face au ciel
      if (!(*it)->_up)
      {
        glTexCoord2d(0, 0);
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, 0);
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        glVertex3d(Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
        glTexCoord2d(0, Block::SIZE);
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2, Block::SIZE);
      }

      glEnd();

      glPopMatrix();
    }
  }

  void draw(const std::pair<int, int>& coord, const Chunk& chunk)
  {

//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_NORMALIZE);

//    GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0};
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
//    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
//    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

//    GLfloat spot_direction[] = {1.0, -1.0, -1.0};
//    GLint spot_exponent = 30;
//    GLint spot_cutoff = 180;

//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//    glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
//    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

//    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
//    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
//    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

//    // -------------------------------------------
//    // Lighting parameters:

//    GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
//    GLfloat light_Ka[]  = {1.0f, 1.0f, 1.0f, 1.0f};
//    GLfloat light_Kd[]  = {1.0f, 1.0f, 1.0f, 1.0f};
//    GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

//    // -------------------------------------------
//    // Material parameters:

//    GLfloat material_Ka[] = {0.5f, 0.5f, 0.5f, 1.0f};
//    GLfloat material_Kd[] = {0.5f, 0.5f, 0.5f, 1.0f};
//    GLfloat material_Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};
//    GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
//    GLfloat material_Se = 20.0f;

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

    TextureManager& textures = TextureManager::getInstance();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["veg1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures["wood1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);


    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable("terrain");

    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex0"), 0);
    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex1"), 1);
    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex2"), 2);

    glPushMatrix();

    glBegin(GL_TRIANGLE_STRIP);
    auto end = chunk.cend();
    for (auto it = chunk.cbegin(); it != end; ++it)
    {
      glMultiTexCoord2fARB(GL_TEXTURE0, (((*it)->getY()) / Chunk::SIZE),
                           1.0 - ((*it)->getX()) / Chunk::SIZE);
      glMultiTexCoord2fARB(GL_TEXTURE1, (((*it)->getY()) / Chunk::SIZE),
                           1.0 - ((*it)->getX()) / Chunk::SIZE);
      glVertex3f((*it)->getX() + coord.first * (Chunk::SIZE - 1) - (Chunk::SIZE / 2),
                 (*it)->getY() + coord.second * (Chunk::SIZE - 1) - (Chunk::SIZE / 2),
                 (*it)->getZ());
    }
    glEnd();

    glPopMatrix();

    shaders.disable();

//    glDisable(GL_LIGHTING);
//    glDisable(GL_LIGHT0);
//    glDisable(GL_NORMALIZE);

  }

  void draw(const Map::chunks_type& chunks)
  {
    auto end = chunks.cend();
    for (auto it = chunks.cbegin(); it != end; ++it)
      draw(it->first, *it->second);
  }

  void drawTree(Architecte::Model & Tree)
{
        TextureManager& textures = TextureManager::getInstance();
        glBindTexture(GL_TEXTURE_2D, textures["wood1"]);

        glPushMatrix();
        glBegin(GL_LINE_STRIP);
        auto end = Tree.end();
        for (auto it = Tree.begin(); it != end; ++it)
          {
          {
            glColor3f(1,1,1);
            glVertex3f((*it)._x,
                       (*it)._y,
                       (*it)._z);
          }
         glEnd();
         glPopMatrix();
    }
}


} // namespace

Drawer::Drawer()
{
}

void Drawer::drawMap(const Map& map) const
{
  draw(map.getBlocks());
  //draw(map.getTriangles());
  draw(map.getChunks());

}















