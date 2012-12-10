#include "Map.hh"
#include "Drawer.hh"
#include "Block/Basic.hh"
#include "TextureManager.hh"
#include "ShadersManager.hh"
#include "Opengl.hh"
#include "Architecte.hh"
#include "iostream"
#include <vector>
#include <sstream>
#include <cmath>

#include "Model/StaticCubeModel.hh"

namespace
{
void drawChunk(const std::pair<int, int>& coord, const Chunk& chunk,
               const Chunk::Coord* selectedCoord)
{
    TextureManager& textures = TextureManager::getInstance();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["veg1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures["wood1"]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable("terrain");

    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex0"), 0);
    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex1"), 1);
    glUniform1i(glGetUniformLocation(shaders.get("terrain"), "tex2"), 2);
    GLuint attrib = glGetAttribLocation(shaders.get("terrain"), "selected");

    /*if (selectedCoord)
      glUniform3f(glGetUniformLocation(shaders.get("terrain"), "selectedCoord"),
                  selectedCoord->getX(), selectedCoord->getY(), selectedCoord->getZ());
*/
    int selectX = 0;
    int selectY = 0;

    if (selectedCoord)
    {
        selectX = selectedCoord->getX();
        selectY = selectedCoord->getY();
    }

    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
    auto end = chunk.cend();
    for (auto it = chunk.cbegin(); it != end; ++it)
    {
        const double xTex = ((*it)->getY() / Chunk::SIZE) * 15;
        const double yTex =  (1.0 - (*it)->getX() / Chunk::SIZE) * 15;
        glMultiTexCoord2fARB(GL_TEXTURE0, xTex, yTex);
        glMultiTexCoord2fARB(GL_TEXTURE1, xTex, yTex);
        glMultiTexCoord2fARB(GL_TEXTURE2, xTex, yTex);

        const double realX = coord.first*(Chunk::SIZE-1) + (*it)->getX() -Chunk::SIZE/2;
        const double realY = coord.second*(Chunk::SIZE-1) + (*it)->getY()-Chunk::SIZE/2;
        const double realZ = (*it)->getZ();


        glVertexAttrib1f(attrib, /*selectedCoord &&*/
                         realX - 4 < selectX - Chunk::SIZE/2  && selectX - Chunk::SIZE/2 < realX + 4 &&
                         realY - 4 < selectY - Chunk::SIZE/2 && selectY - Chunk::SIZE/2  < realY + 4);
        glVertex3f(realX, realY, realZ);
    }
    glEnd();
    glPopMatrix();

    shaders.disable();
}

} // namespace

void
Drawer::drawChunks(const Map::chunks_type& chunks, const Chunk::Coord* selectedCoord) const
{
    auto end = chunks.cend();
    for (auto it = chunks.cbegin(); it != end; ++it)
        drawChunk(it->first, *it->second, selectedCoord);
}

void
Drawer::drawPickingBox(const Map& map) const
{
    const Map::blocks_type& blocks = map.getBlocks();
    auto end = blocks.end();
    for (auto block = blocks.begin(); block != end; ++block)
        block->second->drawPickingBox();
}

void
Drawer::drawBlocks(const Map& map) const
{
    const Map::blocks_type& blocks = map.getBlocks();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);



    ShadersManager& shaders = ShadersManager::getInstance();
    //glUniform1f(glGetUniformLocation(shaders.get("cube"), "cube_color"), isHighlight() ? 0.2 : 0.0);
    glUniform1f(glGetUniformLocation(shaders.get("cube"), "cube_color"), 0.0);
    GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
    glVertexAttrib1f(attrib, 0.0);

    TextureManager& textures = TextureManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    ASSERT_MSG(Model::CubeModel::getInstance().getVboId(), "Invalid vertex buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, Model::CubeModel::getInstance().getVboId());

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glNormalPointer(GL_FLOAT, 0, (void*)sizeof(Model::Cube::vertices));
    glTexCoordPointer(3, GL_FLOAT, 0, (void*)(sizeof(Model::Cube::vertices) + sizeof(Model::Cube::normals)));


    auto end = blocks.end();
    for (auto block = blocks.begin(); block != end; ++block)
    {
      block->second->draw();
      block->second->resetHighlight();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShadersManager::getInstance().disable();
}


void Drawer::light(unsigned int timestep)
{



    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable("tex_lightning");




    glPushMatrix();
    glTranslated(0,0,30);
    glRotated(45,1,0,0);

    GLfloat ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat cyan[] = {0.f, .0f, 1.0f, 1.f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT,ambient);
    GLfloat shininess[] = {50};
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glBegin(GL_QUADS);

        glNormal3d(0,1,0);
        glColor3ub(100,0,0); //face rouge
        glVertex3d(1,1,1);
        glNormal3d(0,1,0);
        glVertex3d(1,1,-1);
        glNormal3d(0,1,0);
        glVertex3d(-1,1,-1);
        glNormal3d(0,1,0);
        glVertex3d(-1,1,1);

        glColor3ub(0,100,0); //face verte
        glNormal3d(1,0,0);
        glVertex3d(1,-1,1);
        glNormal3d(1,0,0);
        glVertex3d(1,-1,-1);
        glNormal3d(1,0,0);
        glVertex3d(1,1,-1);
        glNormal3d(1,0,0);
        glVertex3d(1,1,1);

        glColor3ub(0,0,100); //face bleue
        glNormal3d(0,-1,0);
        glNormal3d(0,-1,0);
        glVertex3d(-1,-1,1);
        glNormal3d(0,-1,0);
        glVertex3d(-1,-1,-1);
        glNormal3d(0,-1,0);
        glVertex3d(1,-1,-1);
        glNormal3d(0,-1,0);
        glVertex3d(1,-1,1);

        glColor3ub(100,100,0); //face jaune
        glNormal3d(-1,0,0);
        glVertex3d(-1,1,1);
        glNormal3d(-1,0,0);
        glVertex3d(-1,1,-1);
        glNormal3d(-1,0,0);
        glVertex3d(-1,-1,-1);
        glNormal3d(-1,0,0);
        glVertex3d(-1,-1,1);

        glColor3ub(0,100,100); //face cyan
        glNormal3d(0,0,-1);
        glVertex3d(1,1,-1);
        glNormal3d(0,0,-1);
        glVertex3d(1,-1,-1);
        glNormal3d(0,0,-1);
        glVertex3d(-1,-1,-1);
        glNormal3d(0,0,-1);
        glVertex3d(-1,1,-1);


        glColor3ub(100,0,100); //face magenta
        glNormal3d(0,0,1);
        glVertex3d(1,-1,1);
        glNormal3d(0,0,1);
        glVertex3d(1,1,1);
        glNormal3d(0,0,1);
        glVertex3d(-1,1,1);
        glNormal3d(0,0,1);
        glVertex3d(-1,-1,1);

        glEnd();


        glPopMatrix();


        glPushMatrix();
        glTranslated(10,0,30);
        glRotated(45,1,0,0);



        glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient);

        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

        glBegin(GL_QUADS);

            glNormal3d(1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(1,1,1);

            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(1,1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(-1,1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0, 1);
            glVertex3d(-1,1,1);


            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(1,-1,1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(1,-1,-1);

            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(1,1,-1);

            glNormal3d(1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertex3d(1,1,1);



            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(-1,-1,1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(-1,-1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(1,-1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertex3d(1,-1,1);


            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(-1,1,1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(-1,1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(-1,-1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertex3d(-1,-1,1);


            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(1,1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(1,-1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(-1,-1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(0,1);
            glVertex3d(-1,1,-1);



            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertex3d(1,-1,1);

            glNormal3d(1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(1,0);
            glVertex3d(1,1,1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(1,1);
            glVertex3d(-1,1,1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertex3d(-1,-1,1);

           glEnd();


            glPopMatrix();

        glPushMatrix();
        glTranslated(0,0,40);
        glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2d(0, 0);
        //1
        glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);

        glTexCoord2d(Block::SIZE, 0);
        //2

        glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
//3
        glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
        glVertex3d(Block::SIZE /2, Block::SIZE/2,0);

        //4
        glNormal3d(0,0,1);

        glVertex3d(0, 0,Block::SIZE);

        //5

        glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);

        //6
        glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);

        //7
        glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        //8
        glNormal3d(0,0,1);
        glVertex3d(0, 0,Block::SIZE);
        //9
        glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
        glVertex3d(Block::SIZE/2, Block::SIZE/2,0);


        glEnd();
        glPopMatrix();






       glPushMatrix();

        static double move = 0;
        move += 1 * timestep;
        glRotatef((move/60), 0, 1, 0);




        glBegin(GL_TRIANGLES);
        glColor3ub(255,0,255);
        glVertex3d(0,0,60);
        glVertex3d(1,0,60);
        glVertex3d(0,1,60);
        glEnd();


        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        int LightPos[4] = {0,0,60,1};
        glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

        glPopMatrix();



    //glTranslatef(move / 1000, 0, 0);


    /*GLfloat specular[] = {0.5f, 0.5f, 0.5f , 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);
    glEnable(GL_COLOR_MATERIAL);
    float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
    float mcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mcolor);*/

    /*glRotated(90,0,1,0);
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    glRotated(-90,0,1,0);*/
    /*GLfloat diffuse[] = { 0.9,0.9,0.9,1.0 };
      GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
      GLfloat shinines[] = { 50.0 };
      GLfloat l_pos[] = { 1.0,1.0,1.0,0.0 };
      glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
      glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
      glMaterialfv(GL_FRONT,GL_SHININESS,shinines);
      glLightfv(GL_LIGHT0,GL_POSITION,l_pos);
      glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);*/




    shaders.disable();
}

void
internalDraw()
{
  ShadersManager& shaders = ShadersManager::getInstance();
  shaders.enable("cube");
  glUniform1f(glGetUniformLocation(shaders.get("cube"), "cube_color"), 0.0);
  GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
  glVertexAttrib1f(attrib, 0.0);

  TextureManager& textures = TextureManager::getInstance();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures["brick1"]);


  glBindBuffer(GL_ARRAY_BUFFER, Model::CubeModel::getInstance().getVboId());

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, 0);
  glNormalPointer(GL_FLOAT, 0, (void*)sizeof(Model::Cube::vertices));
  glTexCoordPointer(3, GL_FLOAT, 0, (void*)(sizeof(Model::Cube::vertices) + sizeof(Model::Cube::normals)));

  int z = 20;
  for (int x = 0; x < 100; ++x)
  {
    for (int y = 0; y < 100; ++y)
    {
      glPushMatrix();
      glTranslatef(x * Block::SIZE + Block::SIZE / 2,
                   y * Block::SIZE + Block::SIZE / 2,
                   z * Block::SIZE + Block::SIZE / 2);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glPopMatrix();
    }
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  ShadersManager::getInstance().disable();
}

void
Drawer::drawVBO()
{
  internalDraw();
}

void
Drawer::drawSomeBlocks(Map& map)
{
  Core::Container3D<int> where;

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      where._x = i + 1;
      where._y = j + 1;
      where._z = 0;
      map.createBlock(where);
    }
  }

  for (int i = 0; i < 40; ++i)
  {
    for (int j = 0; j < 40; ++j)
    {
      where._x = i + 1;
      where._y = j + 1;
      where._z = 20;
      map.createBlock(where);
    }
  }
}
