#include "block.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>
#include "TextureManager.hh"
#include "GLUtils.hh"
#include "FreeFlyCamera.hh"
#include "Scene.hh"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

block::block()
    :_x(0), _y(0), _z(0), taille(10)
{}

block::block(int x,int y,int z,int taille)
    :_x(x), _y(y), _z(z), taille(taille)
{}


block::block(Draw(block b))
   {
            glPushMatrix();

            glTranslatef(b._x*b.taille,b._y*b.taille,b._z*b.taille);
            TextureManager& textures = Singleton<TextureManager>::getInstance();

            glBindTexture(GL_TEXTURE_2D, textures["test"]);


            glBegin(GL_QUADS);
            //par terre
            glTexCoord2d(0,0);
            glVertex3d(-b.taille/2,-b.taille/2,0);
            glTexCoord2d(b.taille,0);
            glVertex3d(b.taille/2,-b.taille/2,0);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(b.taille/2,b.taille/2,0);
            glTexCoord2d(0,b.taille);
            glVertex3d(-b.taille/2,b.taille/2,0);

            //face droite
            glTexCoord2d(0,0);
            glVertex3d(-b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,0);
            glVertex3d(-b.taille/2,b.taille/2,b.taille);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(-b.taille/2,b.taille/2,0);
            glTexCoord2d(0,b.taille);
            glVertex3d(-b.taille/2,-b.taille/2,0);

            //face gauche
            glTexCoord2d(0,0);
            glVertex3d(b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,0);
            glVertex3d(b.taille/2,b.taille/2,b.taille);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(b.taille/2,b.taille/2,0);
            glTexCoord2d(0,b.taille);
            glVertex3d(b.taille/2,-b.taille/2,0);

            //face face
            glTexCoord2d(0,0);
            glVertex3d(-b.taille/2,b.taille/2,b.taille);
            glTexCoord2d(b.taille,0);
            glVertex3d(b.taille/2,b.taille/2,b.taille);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(b.taille/2,b.taille/2,0);
            glTexCoord2d(0,b.taille);
            glVertex3d(-b.taille/2,b.taille/2,0);

            //face derriere
            glTexCoord2d(0,0);
            glVertex3d(-b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,0);
            glVertex3d(b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(b.taille/2,-b.taille/2,0);
            glTexCoord2d(0,b.taille);
            glVertex3d(-b.taille/2,-b.taille/2,0);
            //face au ciel
            glTexCoord2d(0,0);
            glVertex3d(-b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,0);
            glVertex3d(b.taille/2,-b.taille/2,b.taille);
            glTexCoord2d(b.taille,b.taille);
            glVertex3d(b.taille/2,b.taille/2,b.taille);
            glTexCoord2d(0,b.taille);
            glVertex3d(-b.taille/2,b.taille/2,b.taille);

            glEnd();
            glPopMatrix();
          }




