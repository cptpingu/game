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
    Block::NeighbourMatrix neighbours;

    ShadersManager& shaders = ShadersManager::getInstance();
    GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
    glVertexAttrib1f(attrib, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    auto end = blocks.end();
    for (auto block = blocks.begin(); block != end; ++block)
    {
        block->second->draw(neighbours);
        block->second->resetHighlight();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    shaders.disable();
}


void Drawer::light(unsigned int timestep)
{








    glPushMatrix();
    glTranslated(0,0,30);
    glRotated(45,1,0,0);

    GLfloat ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat cyan[] = {0.f, .0f, 1.0f, 1.f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT,ambient);
    GLfloat shininess[] = {40};
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

        ShadersManager& shaders = ShadersManager::getInstance();
        shaders.enable("tex_lightning");

        //float  id = glGetUniformLocation(prog, "var");
        //float distance = 5;

        for (int i = 1;i<10;++i)
        {
        glPushMatrix();
        glTranslated(2*i,0,30);
        glRotated(45,1,0,0);

        //glVertexAttrib1f(,distance*i);
/*
        glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient);

        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
        }*/
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
}
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
        glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,.1f);

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


  // cube ///////////////////////////////////////////////////////////////////////
  //    v6----- v5
  //   /|      /|
  //  v1------v0|
  //  | |     | |
  //  | v7----|-v4
  //  |/      |/
  //  v2------v3

  // vertex coords array for glDrawArrays() =====================================
  // A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
  // of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
  // vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
  // array is 108 floats (36 * 3 = 108).
  GLfloat vertices[]  = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                          -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                          1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                          1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                          1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                          -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                          -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                          -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                          -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                          1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                          1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                          -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

  // normal array
  GLfloat normals[]   = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                          0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                          1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                          1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                          0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                          0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                          -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                          -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                          0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                          0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                          0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                          0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

  // color array
  GLfloat colors[]    = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                          1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                          1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                          0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                          1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                          0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                          1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                          0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                          0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                          1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                          0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                          0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4


  GLuint vboId = 0;

  void
  Drawer::initVBO(const Map& map)
  {
  // create vertex buffer objects, you need to delete them when program exits
  // Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
  // glBufferDataARB with NULL pointer reserves only memory space.
  // Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
  // target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals)+sizeof(colors), 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals), sizeof(colors), colors);  // copy colours after normals
}

void
internalDraw()
{
  // bind VBOs with IDs and set the buffer offsets of the bound VBOs
  // When buffer object is bound with its ID, all pointers in gl*Pointer()
  // are treated as offset instead of real pointer.
  glBindBuffer(GL_ARRAY_BUFFER, vboId);

  // enable vertex arrays
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  // before draw, specify vertex and index arrays with their offsets
  glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
  glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices)+sizeof(normals)));
  glVertexPointer(3, GL_FLOAT, 0, 0);

  for (int x = 0; x < 100; ++x)
  {
    for (int y = 0; y < 100; ++y)
    {
      glPushMatrix();
      glTranslatef(x, y, 20);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glPopMatrix();
    }
  }

  //glDrawArrays(GL_TRIANGLES, 0, 36);

  glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  // it is good idea to release VBOs with ID 0 after use.
  // Once bound with 0, all pointers in gl*Pointer() behave as real
  // pointer, so, normal vertex array operations are re-activated
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
Drawer::drawVBO()
{
//  for (int x = 0; x < 1000; ++x)
//  {
//    for (int y = 0; y < 100; ++y)
//    {
//      glPushMatrix();
//      glTranslatef(x, y, 20);
      //internalDraw();
//      glPopMatrix();
//    }
//  }
}
