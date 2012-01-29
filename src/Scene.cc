#include "Scene.hh"
#include "FreeFlyCamera.hh"
#include "GLUtils.hh"
#include "TextureManager.hh"
#include "Vector3D.hh"
# include "Opengl.hh"

void chargerTextures()
{

  TextureManager& textures = Singleton<TextureManager>::getInstance();
  //TextureManager& textures = TextureManager::getInstance();

  textures.load("data/images/metal091.jpg", "metal");
  textures.load("data/images/rocket_motor.jpg", "rocketMotor");
  textures.load("data/images/rocket_bottom.jpg", "rocketBottom");
  textures.load("data/images/rocket_middle.jpg", "rocketMiddle");
  textures.load("data/images/rocket_top.jpg", "rocketTop");
  //autre texture
  textures.load("data/images/concrete001.jpg", "concrete");
  textures.load("data/images/neige.jpg", "neige");
  textures.load("data/images/floor032.jpg", "floor1");
  textures.load("data/images/brick009.jpg", "brick1");
  textures.load("data/images/wood002.jpg", "wood1");
  textures.load("data/images/wood006.jpg", "wood2");
  //porte
  textures.load("data/images/door009.jpg", "door");
  //pour les caisse
  textures.load("data/images/crate03.jpg", "crate");
  //toit
  textures.load("data/images/roof05.jpg", "roof");
  //fenetre
  textures.load("data/images/window031_alpha.png", "window");
  //Herbe
  textures.load("data/images/veg008.jpg", "veg1");
  //Eau de la piscine
  textures.load("data/images/eau.jpg", "eau");
  // Dalle de la piscine
  textures.load("data/images/floor006b.jpg", "floor2");
  // Fond du puit
  textures.load("data/images/veg010.jpg", "veg2");
  // puit
  textures.load("data/images/brick077.jpg", "brick2");
   textures.load("data/images/test.jpg", "test");
}

void block(const Vector3D & ou,int taille,char nature )

{
  glPushMatrix();

  glTranslatef(ou._x,ou._y,ou._z);
  TextureManager& textures = Singleton<TextureManager>::getInstance();


  if (nature == 't')
  {glBindTexture(GL_TEXTURE_2D, textures["test"]);}
  else
  {glBindTexture(GL_TEXTURE_2D, textures["eau"]);}

  glBegin(GL_QUADS);
  //par terre
  glTexCoord2d(0,0);
  glVertex3d(-taille/2,-taille/2,0);
  glTexCoord2d(taille,0);
  glVertex3d(taille/2,-taille/2,0);
  glTexCoord2d(taille,taille);
  glVertex3d(taille/2,taille/2,0);
  glTexCoord2d(0,taille);
  glVertex3d(-taille/2,taille/2,0);

  //face droite
  glTexCoord2d(0,0);
  glVertex3d(-taille/2,-taille/2,taille);
  glTexCoord2d(taille,0);
  glVertex3d(-taille/2,taille/2,taille);
  glTexCoord2d(taille,taille);
  glVertex3d(-taille/2,taille/2,0);
  glTexCoord2d(0,taille);
  glVertex3d(-taille/2,-taille/2,0);

  //face gauche
  glTexCoord2d(0,0);
  glVertex3d(taille/2,-taille/2,taille);
  glTexCoord2d(taille,0);
  glVertex3d(taille/2,taille/2,taille);
  glTexCoord2d(taille,taille);
  glVertex3d(taille/2,taille/2,0);
  glTexCoord2d(0,taille);
  glVertex3d(taille/2,-taille/2,0);

  //face face
  glTexCoord2d(0,0);
  glVertex3d(-taille/2,taille/2,taille);
  glTexCoord2d(taille,0);
  glVertex3d(taille/2,taille/2,taille);
  glTexCoord2d(taille,taille);
  glVertex3d(taille/2,taille/2,0);
  glTexCoord2d(0,taille);
  glVertex3d(-taille/2,taille/2,0);

  //face derriere
  glTexCoord2d(0,0);
  glVertex3d(-taille/2,-taille/2,taille);
  glTexCoord2d(taille,0);
  glVertex3d(taille/2,-taille/2,taille);
  glTexCoord2d(taille,taille);
  glVertex3d(taille/2,-taille/2,0);
  glTexCoord2d(0,taille);
  glVertex3d(-taille/2,-taille/2,0);
  //face au ciel
  glTexCoord2d(0,0);
  glVertex3d(-taille/2,-taille/2,taille);
  glTexCoord2d(taille,0);
  glVertex3d(taille/2,-taille/2,taille);
  glTexCoord2d(taille,taille);
  glVertex3d(taille/2,taille/2,taille);
  glTexCoord2d(0,taille);
  glVertex3d(-taille/2,taille/2,taille);

  glEnd();
  glPopMatrix();
}

void go()
{
  //block
  Vector3D la;
  Vector3D b;
  Vector3D c;

  Vector3D e;
  Vector3D f;
  char d;
  d = 'e';
  la = Vector3D(0,0,0);
  b = Vector3D(1,1,2);
  c = Vector3D(10,0,0);
  e= Vector3D(0,10,0);
  f=Vector3D(0,0,10);

  block(la,10,d);//creation d'un block
  //la = la.mStar(b);

  block(la,10,d);
  la = la + c;
  block(la,10,'t');
  la = la + e;
  block(la,10,'t');
  la = la + f;
  block(la,10,'t');
}
