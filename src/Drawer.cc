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

void
Drawer::drawPickingBox(const Map& map) const
{
    const Map::groups_type& groups = map.getGroups();
    auto end = groups.cend();
    for (auto it = groups.cbegin(); it != end; ++it)
      it->second->drawPicking();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    ShadersManager::getInstance().disable();
}

void
Drawer::drawBlocks(const Map& map) const
{
  const Map::groups_type& groups = map.getGroups();
  auto end = groups.cend();
  for (auto it = groups.cbegin(); it != end; ++it)
    it->second->draw();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  ShadersManager::getInstance().disable();
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
        float distance = 0.1;
       GLuint dist = glGetAttribLocation(shaders.get("tex_lightning"), "Temps");
        for (int i = 1;i<10;++i)
        {
        glPushMatrix();
        glTranslated(3*i+1,0,30);
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
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,1);

            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0, 1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,1);


            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,-1);

            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,-1);

            glNormal3d(1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,1);



            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,-1,1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,-1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,1);


            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,-1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,-1,1);


            glNormal3d(1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(0,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,-1);

            glNormal3d(1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,-1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,-1,-1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),-1/sqrt(3));
            glTexCoord2d(0,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,-1);



            glNormal3d(1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,-1,1);

            glNormal3d(1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(1,0);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(1,1,1);

            glNormal3d(-1/sqrt(3),1/sqrt(3),1/sqrt(3));
            glTexCoord2d(1,1);
            glVertexAttrib1f(dist,distance*i);
            glVertex3d(-1,1,1);

            glNormal3d(-1/sqrt(3),-1/sqrt(3),1/sqrt(3));
            glTexCoord2d(0,1);
            glVertexAttrib1f(dist,distance*i);
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


        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.5f);
        glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,1.0f);
        glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,2.0f);

        glEnable(GL_LIGHT1);
        glLightf(GL_LIGHT1,GL_AMBIENT,1.0f);



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

  // 400 * 100 => 45 fps
  int z = 20;
  for (int x = 0; x < 400; ++x)
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

  static const int nb = 40;
  for (int i = 0; i < nb; ++i)
  {
    for (int j = 0; j < nb; ++j)
    {
      for (int k = 0; k < nb; ++k)
      {
        where._x = i + 1;
        where._y = j + 1;
        where._z = k + 1;
        map.createBlock(where);
      }
    }
  }

//  for (int i = 0; i < 64; ++i)
//  {
//    where._x = 2 * i;
//    where._y = -1;
//    where._z = -1;
//    map.createBlock(where, i);
//  }

//  400 * 100 => 40fps
//   for (int i = 0; i < 400; ++i)
//   {
//     for (int j = 0; j < 100; ++j)
//     {
//       where._x = i + 1;
//       where._y = j + 1;
//       where._z = 20;
//       map.createBlock(where);
//     }
//   }
}
