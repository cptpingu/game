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
#include "Core/Random.hh"

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





std::vector<Core::Vector3D> Drawer::collisionlist(const  Core::Vector3D &from,const Core::Vector3D &to)
{

    //S'utilise d'a partir d'un block
    std::vector<Core::Vector3D> List;
    Core::Vector3D v;
    float alphax = (to - from).length();
    float alphay = (to - from).length();
    float alphaz = (to - from).length();
    int dx = 0;
    int dy = 0;
    int dz = 0;

    v = (to - from);
    v.normalize();

    float alpha =0;


    while (alpha <  (to - from).length()-1  )
    {

    if (v._x != 0)
    alphax =  ((v._x > 0) - (v._x < 0))*(dx*Block::SIZE + Block::HALF_SIZE)/v._x;

    if (v._y != 0)
    alphay = ( (v._y > 0) - (v._y < 0))*(dy*Block::SIZE+ Block::HALF_SIZE)/v._y;

    if (v._z != 0)
    alphaz = ((v._z > 0) - (v._z < 0))*(dz*Block::SIZE+ Block::HALF_SIZE)/v._z;

    //if(v._x == 0 && v._y == 0 && v._z == 0 )
    //std::cout<< alphax << "_" << alphaz <<  "_" << alphaz << "_"<< (to - from).length()<< std::endl;
    alpha = std::min(alphaz,std::min(alphax,alphay));

    if (alphax==alpha && alphax < (to - from).length())
        dx++;
    if (alphay==alpha && alphay < (to - from).length())
        dy++;
    if (alphaz==alpha && alphaz < (to - from).length())
        dz++;
    //std::cout<< dx*((v._x > 0) - (v._x < 0)) << "_" << dy*((v._y > 0) - (v._y < 0)) << "_" << dz*((v._z > 0) - (v._z < 0)) << "_" << alpha <<std::endl;
    List.push_back(Core::Vector3D (from._x + dx*((v._x > 0) - (v._x < 0)),from._y + dy*((v._y > 0) - (v._y < 0)),from._z +dz*((v._z > 0) - (v._z < 0))));

    }
    return List;

}



void Drawer::light(unsigned int timestep)
{

    std::vector<Core::Vector3D> list = collisionlist(Core::Vector3D (0,0,0),Core::Vector3D (50,0,50));


    glPushMatrix();
    glTranslated(0,0,30);
    glRotated(45,1,0,0);

    //GLfloat ambient[] = {.5f, .5f, .5f, 1.0f};
    GLfloat ambient[] = {.0f, .0f, .0f, 1.0f};
    GLfloat white[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat cyan[] = {0.5f, .5f, .5f, 1.f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT,ambient);
    GLfloat shininess[] = {60};
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
        //shaders.enable("phong_lightning");
        shaders.enable("tex_lightning");
        //shaders.enable("cubeLight");

        //float  id = glGetUniformLocation(prog, "var");
        //float distance = 0.1;
       //GLuint dist = glGetAttribLocation(shaders.get("tex_lightning"), "Distance");
        //GLuint dist = glGetAttribLocation(shaders.get("cubeLight"), "Distance");

        GLuint dist = glGetAttribLocation(shaders.get("tex_lightning"), "Temps");
         //glVertexAttrib1f(temps,0.5);
        //GLuint Light = glGetAttribLocation(shaders.get("cubeLight"), "LightPosition");


       glPushMatrix();

       static double move = 0;
       //move += 1 * timestep;
       //glRotatef((move/20), 30, 1, 0);

       glBegin(GL_TRIANGLES);
       glColor3ub(0,0,255);
       glVertex3d(0,0,60);
       glVertex3d(1,0,60);
       glVertex3d(0,1,60);
       glEnd();

       int LightPos[4] = {0,0,60,1};
       glLightiv(GL_LIGHT0,GL_POSITION,LightPos);



       glPopMatrix();









#define DRAW(X, Y, Z) \
    glNormal3d(X/sqrt(3),Y/sqrt(3),Z/sqrt(3)); \
    glVertex3d(X,Y,Z);

       for (int x = 0; x < list.size(); ++x)
       {

/*
Core::Vector3D Point;
Point(x-LightPos[1]*1.0,y-LightPos[2]*1.0,z-LightPos[3]*1.0);
double D = Point.length();*/
           float D = 1-(list[x]._z+list[x]._y+list[x]._x)/list.size()*(list[x]._z+list[x]._y+list[x]._x)/list.size();

                   //1/log(sqrt(list[x]._x*list[x]._x + list[x]._y*list[x]._y + list[x]._z*list[x]._z));


       //float D =0.1;
                   glPushMatrix();
                   glTranslated(2*list[x]._x,2*list[x]._y,2*list[x]._z);
                   //glRotated(45,1,0,0);

                   glBegin(GL_QUADS);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                  // glVertexAttrib1f(temps,D);
                   //glVertexAttrib1f(temps,distance*x);
                   //glVertexAttrib3f(dist,distance*i);
                   DRAW(1, 1, 1);


                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   //glVertexAttrib1f(temps,distance*x);
                   DRAW(1, 1, -1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   //glVertexAttrib1f(temps,distance*x);
                   DRAW(-1,1,-1);

                   glTexCoord2d(0, 1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,1,1);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,-1,1);

                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,-1,-1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,1,-1);

                   glTexCoord2d(0,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,1,1);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,1);

                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,-1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,-1,-1);

                   glTexCoord2d(0,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,-1,1);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,1,1);

                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,1,-1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,-1);

                   glTexCoord2d(0,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,1);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,1,-1);

                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,-1,-1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,-1);

                   glTexCoord2d(0,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,1,-1);

                   glTexCoord2d(0,0);
                   glVertexAttrib1f(dist,D);
                  // glVertexAttrib1f(temps,D);
                   DRAW(1,-1,1);

                   glTexCoord2d(1,0);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(1,1,1);

                   glTexCoord2d(1,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,1,1);

                   glTexCoord2d(0,1);
                   glVertexAttrib1f(dist,D);
                   //glVertexAttrib1f(temps,D);
                   DRAW(-1,-1,1);

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
Drawer::drawDebug(Map& map)
{
  //drawALittleMap(map);
  drawSomeBlocks(map);
}

void
Drawer::drawALittleMap(Map& map)
{
  static const int nb = 40;

  Core::Container3D<int> where;
  Core::Array2D<int, nb> tab;

  for (int i = 0; i < nb; ++i)
    for (int j = 0; j < nb; ++j)
      tab(i,j) =  Core::Random::rand() % nb;

  for (int n = 0; n < 3; ++n)
    for (int i = 1; i < nb - 1; ++i)
      for (int j = 1; j < nb - 1; ++j)
        tab(i, j) = (tab(i, j) +
                    tab(i + 1, j) +
                    tab(i, j + 1) +
                    tab(i + 1, j + 1) +
                    tab(i - 1, j) +
                    tab(i - 1, j + 1) +
                    tab(i, j - 1) +
                    tab(i + 1, j - 1) +
                    tab(i - 1, j - 1)) / 9;

  for (int i = 0; i < nb - 1; ++i)
  {
    for (int j = 0; j < nb - 1; ++j)
    {
      for (int k = 0; k < nb; ++k)
      {

        where._x = i + 1;
        where._y = j + 1;
        where._z = k * (k < tab(i + 1, j + 1));
        map.createBlock(where);
      }
    }
  }
}

void
Drawer::drawSomeBlocks(Map& map)
{
  static const int nb = 10;

  Core::Container3D<int> where;

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

  for (int i = 0; i < 64; ++i)
  {
    where._x = 2 * i;
    where._y = -1;
    where._z = -1;
    map.createBlock(where, i);
  }

  //400 * 100 => 40fps
//  for (int i = 0; i < 400; ++i)
//  {
//    for (int j = 0; j < 100; ++j)
//    {
//      where._x = i + 1;
//      where._y = j + 1;
//      where._z = 20;
//      map.createBlock(where);
//    }
//  }
}
