#include "Triangle.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include <typeinfo>
#include <iostream>

namespace Block
{
  Triangle::Triangle(int x, int y, int z)
    : super(x, y, z)
  {
  }

  Triangle::~Triangle()
  {
  }

  bool
  Triangle::specificIsNullIndex(int) const
  {
    return false;
  }

  void
  Triangle::specificInit()
  {
  }

  std::string
  Triangle::getShaderName() const
  {
    return "cube"; // FIXME créer un shader pour les triangles
  }

  void
  Triangle::specificDraw() const
  {
    const NeighbourMatrix neighbours;
      /*if(isHighlight())
      {
      std::cout << (typeid(*this)==typeid(*neighbours(0,0,0))) << std::endl;
      std::cout << typeid(*this).name() << "_" << typeid(*neighbours(0,0,0)).name() << std::endl;
      }*/

    TextureManager& textures = TextureManager::getInstance();
    ShadersManager& shaders = ShadersManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["metal"]);

    glPushMatrix();
    glTranslatef(_x * Block::SIZE, _y * Block::SIZE, _z * Block::SIZE);
    glUniform1f(glGetUniformLocation(shaders.get(getShaderName()), "cube_color"), isHighlight() ? 0.2 : 0.0);

    //Median plan Begin

   if( (
        neighbours.same(1,0,0) ||
        neighbours.same(-1,0,0) ||
        neighbours.same(0,1,0) ||
        neighbours.same(0,-1,0)
        )
        &&
        (
        !(neighbours.same(-1,-1,1) ||
        neighbours.same(-1,0,1)    ||
        neighbours.same(-1,1,1)    ||
        neighbours.same(0,-1,1)    ||
        neighbours.same(0,1,1)     ||
        neighbours.same(1,-1,1)    ||
        neighbours.same(1,0,1)     ||
        neighbours.same(1,1,1))
        )
        )

{
    if (!(neighbours.same(0,-1,0))&&
        !(neighbours.same(0,1,0) )&&
        !(neighbours.same(-1,0,0))&&
         neighbours.same(1,0,0) )
    {
    glBegin(GL_TRIANGLE_STRIP);
//1
    glTexCoord2d(0, 0);
    glVertex3d(0, Block::SIZE,0);
//2
    glTexCoord2d(0, 1);
    glVertex3d(Block::SIZE,0,0);
//3
    glTexCoord2d(1,1);
    glVertex3d(Block::SIZE, Block::SIZE,0);
//4
    glTexCoord2d(1, 1);
    glVertex3d(Block::SIZE, 0,Block::SIZE);
//5
    glTexCoord2d(1, 0);
    glVertex3d(0, Block::SIZE,0);
//6
    glTexCoord2d(0,0);
    glVertex3d(0,0,0);
//7
    glTexCoord2d(0,1);
    glVertex3d(Block::SIZE ,0,0);
//8
    glTexCoord2d(1,1);
    glVertex3d(Block::SIZE / 2, 0,Block::SIZE);
    //glTexCoord2d(Block::SIZE, Block::SIZE);
    //glVertex3d(Block::SIZE/2, 0,Block::SIZE);
    }

    else if (!(neighbours.same(1,0,0)  )&&
         !(neighbours.same(0,1,0)  )&&
         !(neighbours.same(0,-1,0) )&&
         neighbours.same(-1,0,0)
             )
    {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
    //1
        glVertex3d(0, Block::SIZE ,0);
    //
        glTexCoord2d(0, 1);
    //2
        glVertex3d(Block::SIZE , 0,0);
    //
        glTexCoord2d(1, 1);
    //3
        glVertex3d(Block::SIZE , Block::SIZE,0);
    //
        glTexCoord2d(1, 0);
    //4
        glVertex3d(0, Block::HALF_SIZE ,Block::SIZE);
    //
        glTexCoord2d(0, 0);
    //5
        glVertex3d(0, Block::SIZE,0);
    //
        glTexCoord2d(0, 1);
    //6
        glVertex3d(0,0,0);
    //
        glTexCoord2d(1,1);
    //7
        glVertex3d(Block::SIZE,0,0);

        glTexCoord2d(1, 0);
    //8
        glVertex3d(0, Block::HALF_SIZE ,Block::SIZE);
        //glTexCoord2d(Block::SIZE, Block::SIZE);
        //glVertex3d(Block::SIZE/2, 0,Block::SIZE);
    }

    else if(!(neighbours.same(0,-1,0))&&
       !(neighbours.same(1,0,0))&&
       !(neighbours.same(-1,0,0))&&
       neighbours.same(0,1,0)
            )
    {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
    //1
        glVertex3d(0, Block::SIZE,0);
    //
        glTexCoord2d(0, 1);
    //2
        glVertex3d(Block::SIZE, 0,0);
    //
        glTexCoord2d(1,1);
    //3
        glVertex3d(Block::SIZE , Block::SIZE,0);
    //
        glTexCoord2d(1, 0);
    //4
        glVertex3d(0,Block::SIZE,Block::SIZE);
    //
        glTexCoord2d(0, 0);
    //5
        glVertex3d(0, Block::SIZE,0);
    //
        glTexCoord2d(0, 1);
    //6
        glVertex3d(0,0,0);
    //
        glTexCoord2d(1,1);
    //7
        glVertex3d(Block::SIZE ,0,0);

        glTexCoord2d(1, 0);
    //8
        glVertex3d(0, Block::SIZE,Block::SIZE);
        //glTexCoord2d(Block::SIZE, Block::SIZE);
        //glVertex3d(Block::SIZE/2, 0,Block::SIZE);

    }

    else if(!(neighbours.same(0,1,0))&&
       !(neighbours.same(1,0,0))&&
       !(neighbours.same(-1,0,0))&&
       neighbours.same(0,-1,0)
            )
    {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
    //1
        glVertex3d(0, Block::SIZE,0);
    //
        glTexCoord2d(0, 1);
    //2
        glVertex3d(Block::SIZE,0,0);
    //
        glTexCoord2d(1,1);
    //3
        glVertex3d(Block::SIZE, Block::SIZE,0);
    //
        glTexCoord2d(1, 0);
    //4
        glVertex3d(0,0,Block::SIZE);
    //
        glTexCoord2d(0, 0);
    //5
        glVertex3d(0, Block::SIZE,0);
    //
        glTexCoord2d(0, 1);
    //6
        glVertex3d(0,0,0);
    //
        glTexCoord2d(0,0);
    //7
        glVertex3d(Block::SIZE, 0,0);

        glTexCoord2d(1,1);
    //8
        glVertex3d(Block::HALF_SIZE,0,Block::SIZE);
        //glTexCoord2d(Block::SIZE, Block::SIZE);
        //glVertex3d(Block::SIZE/2, 0,Block::SIZE);

    }

    else if(!(neighbours.same(1,0,0))&&
       !(neighbours.same(-1,0,0))&&
       neighbours.same(0,1,0) &&
       neighbours.same(0,-1,0)
       )
    {

        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(0,0,0);
       //
           glTexCoord2d(0,1);
       //2
           glVertex3d(Block::SIZE, Block::SIZE,0);
       //
           glTexCoord2d(1,1);
       //3
           glVertex3d(0,Block::SIZE,0);
       //
           glTexCoord2d(1, 0);
       //4
           glVertex3d(Block::HALF_SIZE,Block::SIZE,Block::SIZE);
       //
           glTexCoord2d(0, 0);
       //5
           glVertex3d(0,0,0);
       //
           glTexCoord2d(0,1);
       //6
           glVertex3d(Block::HALF_SIZE,0,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE,0,0);

           glTexCoord2d(0,1);
       //8
           glVertex3d(Block::SIZE , Block::SIZE , 0);

           glTexCoord2d(1, 1);
        //9
           glVertex3d( Block::HALF_SIZE,0, Block::SIZE);

            glTexCoord2d(1,0);
         //10
            glVertex3d  (Block::HALF_SIZE,Block::SIZE , Block::SIZE);
    }

    else if(!(neighbours.same(0,1,0))&&
       !(neighbours.same(0,-1,0))&&
       neighbours.same(1,0,0) &&
       neighbours.same(-1,0,0)
              )

    {
        glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(0,0,0);
       //
           glTexCoord2d(0,1);
       //2
           glVertex3d(Block::SIZE, Block::SIZE,0);
       //
           glTexCoord2d(1,1);
       //3
           glVertex3d(0, Block::SIZE,0);
       //
           glTexCoord2d(1, 0);
       //4
           glVertex3d(Block::HALF_SIZE, Block::SIZE,Block::SIZE);
       //
           glTexCoord2d(0, 0);
       //5
           glVertex3d(0,0,0);
       //
           glTexCoord2d(0, 1);
       //6
           glVertex3d(Block::HALF_SIZE, 0,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE,0,0);

           glTexCoord2d(0, 1);
       //8
           glVertex3d(Block::SIZE , Block::SIZE , 0);

           glTexCoord2d(1,1);
        //9
           glVertex3d( Block::HALF_SIZE,0, Block::SIZE);

            glTexCoord2d(1,0);
         //10
            glVertex3d  (Block::HALF_SIZE,Block::SIZE, Block::SIZE);
    }


    else if(!(neighbours.same(1,0,0))&&
       !(neighbours.same(0,-1,0) )&&
       neighbours.same(0,1,0) &&
       neighbours.same(-1,0,0)
            )

    {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(0,Block::SIZE,0);
            //
                glTexCoord2d(0,1);
            //2
                glVertex3d(Block::SIZE,0,0);
            //
                glTexCoord2d(1,1);
            //3
                glVertex3d(Block::SIZE,Block::SIZE,0);
            //
                glTexCoord2d(1, 0);
            //4
                glVertex3d(Block::HALF_SIZE ,Block::SIZE,Block::SIZE);
            //
                glTexCoord2d(0, 0);
            //5
                glVertex3d(0,Block::SIZE,0);
            //
                glTexCoord2d(0,1);
            //6
                glVertex3d(Block::SIZE,0,0);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(0,Block::HALF_SIZE,Block::SIZE);

                glTexCoord2d(0,1);
            //8
                glVertex3d(0,0,0);

                glTexCoord2d(1,1);
             //9
                glVertex3d(0,Block::SIZE,0);

                 glTexCoord2d(1,0);
              //10
                 glVertex3d(Block::SIZE,0,0);
                 glTexCoord2d(0,0);
                 //11
                glVertex3d(0,Block::HALF_SIZE,Block::SIZE);}

    else if(!(neighbours.same(-1,0,0) )&&
       !(neighbours.same(0,-1,0))&&
       neighbours.same(0,1,0) &&
       neighbours.same(1,0,0)
            )
    {

        glRotatef(-90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(0,Block::SIZE,0);
            //
                glTexCoord2d(0,1);
            //2
                glVertex3d(Block::SIZE,0,0);
            //
                glTexCoord2d(1,1);
            //3
                glVertex3d(Block::SIZE, Block::SIZE,0);
            //
                glTexCoord2d(1, 0);
            //4
                glVertex3d(Block::HALF_SIZE ,Block::SIZE,Block::SIZE);
            //
                glTexCoord2d(0,0);
            //5
                glVertex3d(0,Block::SIZE,0);
            //
                glTexCoord2d(0,1);
            //6
                glVertex3d(Block::SIZE,0,0);
            //
                glTexCoord2d(1,1);
            //7
                glVertex3d(0, Block::HALF_SIZE,Block::SIZE);

                glTexCoord2d(1,0);
            //8
                glVertex3d(0,0,0);

                glTexCoord2d(0,0);
             //9
                glVertex3d(0,Block::SIZE,0);

                 glTexCoord2d(0,1);
              //10
                 glVertex3d(Block::SIZE ,0, 0);
                 glTexCoord2d(1,1);
                 //11
                glVertex3d(0 ,Block::HALF_SIZE ,Block::SIZE);
    }

    else if(!(neighbours.same(1,0,0))&&
       !(neighbours.same(0,1,0))&&
       neighbours.same(0,-1,0) &&
       neighbours.same(-1,0,0)
            )

    {

        glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(-Block::SIZE / 2 , Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,0 ,Block::SIZE);
    }

    else if(!(neighbours.same(-1,0,0))&&
       !(neighbours.same(0,1,0) )&&
       neighbours.same(0,-1,0) &&
       neighbours.same(1,0,0)
            )
    {

        glRotatef(-180,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(-Block::SIZE / 2 , Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,0 ,Block::SIZE);
    }

    else if(!(neighbours.same(-1,0,0))&&
       neighbours.same(0,1,0) &&
       neighbours.same(0,-1,0) &&
       neighbours.same(1,0,0)
            )
    {

        glRotatef(-180,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(0 , -Block::SIZE/2 , Block::SIZE);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(Block::SIZE / 2 , -Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,Block::SIZE / 2 ,0);
                glTexCoord2d(Block::SIZE,0);

                //12
                glTexCoord2d(Block::SIZE,Block::SIZE);
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                //13
                glTexCoord2d(0,0);
                glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
                //14
                glTexCoord2d(Block::SIZE,0);
                glVertex3d(0, -Block::SIZE/2,Block::SIZE);

    }

    else if(!(neighbours.same(1,0,0))&&
       neighbours.same(0,1,0) &&
       neighbours.same(0,-1,0) &&
       neighbours.same(-1,0,0)
            )

    {

        glRotatef(0,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(0 , -Block::SIZE/2 , Block::SIZE);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(Block::SIZE / 2 , -Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,Block::SIZE / 2 ,0);
                glTexCoord2d(Block::SIZE,0);

                //12
                glTexCoord2d(Block::SIZE,Block::SIZE);
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                //13
                glTexCoord2d(0,0);
                glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
                //14
                glTexCoord2d(Block::SIZE,0);
                glVertex3d(0, -Block::SIZE/2,Block::SIZE);

    }

    else if(!(neighbours.same(0,1,0))&&
       neighbours.same(1,0,0) &&
       neighbours.same(0,-1,0) &&
       neighbours.same(-1,0,0)
            )
    {

        glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(0 , -Block::SIZE/2 , Block::SIZE);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(Block::SIZE / 2 , -Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,Block::SIZE / 2 ,0);
                glTexCoord2d(Block::SIZE,0);

                //12
                glTexCoord2d(Block::SIZE,Block::SIZE);
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                //13
                glTexCoord2d(0,0);
                glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
                //14
                glTexCoord2d(Block::SIZE,0);
                glVertex3d(0, -Block::SIZE/2,Block::SIZE);

    }

    else if(!(neighbours.same(0,-1,0))&&
       neighbours.same(1,0,0) &&
       neighbours.same(0,1,0) &&
       neighbours.same(-1,0,0)
            )
    {

        glRotatef(270,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
            //1
                glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, 0);
            //2
                glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //3
                glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            //
                glTexCoord2d(0, 0);
            //4
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);
            //
                glTexCoord2d(Block::SIZE, 0);
            //5
                glVertex3d(-Block::SIZE / 2, Block::SIZE/2,0);
            //
                glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
            //
                glTexCoord2d(0,0);
            //7
                glVertex3d(0 ,Block::SIZE/2,Block::SIZE);

                glTexCoord2d(Block::SIZE, 0);
            //8
                glVertex3d(0 , -Block::SIZE/2 , Block::SIZE);

                glTexCoord2d(Block::SIZE, Block::SIZE);
             //9
                glVertex3d(Block::SIZE / 2 , -Block::SIZE / 2 , 0);

                 glTexCoord2d(0,0);
              //10
                 glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);
                 glTexCoord2d(Block::SIZE,0);
                 //11
                glVertex3d(-Block::SIZE/2 ,Block::SIZE / 2 ,0);
                glTexCoord2d(Block::SIZE,0);

                //12
                glTexCoord2d(Block::SIZE,Block::SIZE);
                glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                //13
                glTexCoord2d(0,0);
                glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
                //14
                glTexCoord2d(Block::SIZE,0);
                glVertex3d(0, -Block::SIZE/2,Block::SIZE);

    }

    else if(neighbours.same(0,-1,0) &&
       neighbours.same(1,0,0) &&
       neighbours.same(0,1,0) &&
       neighbours.same(-1,0,0))
         {

             glRotatef(270,0,0,1);
             glBegin(GL_TRIANGLE_STRIP);
             glTexCoord2d(0, 0);
                 //1
                     glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
                 //
                     glTexCoord2d(Block::SIZE, 0);
                 //2
                     glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
                 //
                     glTexCoord2d(Block::SIZE, Block::SIZE);
                 //3
                     glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
                 //
                     glTexCoord2d(0, 0);
                 //4
                     glVertex3d(Block::SIZE/2 ,0,Block::SIZE);
                 //
                     glTexCoord2d(Block::SIZE, 0);
                 //5
                     glVertex3d(0, Block::SIZE/2,Block::SIZE);
                 //
                     glTexCoord2d(Block::SIZE, Block::SIZE);
                 //6
                     glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                 //
                     glTexCoord2d(0,0);
                 //7
                     glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);

                     glTexCoord2d(Block::SIZE, 0);
                 //8
                     glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);

                     glTexCoord2d(Block::SIZE, Block::SIZE);
                  //9
                     glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);

                      glTexCoord2d(0,0);
                   //10
                      glVertex3d(0 , -Block::SIZE/2 ,Block::SIZE);
                      glTexCoord2d(Block::SIZE,0);
                      //11
                     glVertex3d(Block::SIZE/2 ,0,Block::SIZE);
                     glTexCoord2d(Block::SIZE,0);

                     //12
                     glTexCoord2d(Block::SIZE,Block::SIZE);
                     glVertex3d(-Block::SIZE / 2, 0,Block::SIZE);
                     //13
                     glTexCoord2d(0,0);
                     glVertex3d(0 , -Block::SIZE/2 ,Block::SIZE);
                     //14
                     glTexCoord2d(Block::SIZE,0);
                     glVertex3d(-Block::SIZE/2 , -Block::SIZE/2 , 0);

         }

    //End Median influence
}



//Superior plan begin ...
 else if(
         (neighbours.same(-1,-1,1) ||
                 neighbours.same(-1,0,1) ||
                 neighbours.same(-1,1,1) ||
                 neighbours.same(0,-1,1) ||
                 neighbours.same(0,1,1) ||
                 neighbours.same(1,-1,1) ||
                 neighbours.same(1,0,1) ||
                 neighbours.same(1,1,1))

         )

{
        //  0 1 2
        //  0 1 1
        //  0 0 0
    if(
        !(neighbours.same(1,0,1))&&
        !(neighbours.same(0,1,1))&&
       !(neighbours.same(-1,0,1))&&
       !(neighbours.same(0,-1,1) )&&
       !(neighbours.same(-1,1,1) )&&
       !(neighbours.same(-1,-1,1) )&&
       !(neighbours.same(1,-1,1) )&&
        neighbours.same(1,1,1) &&
        ((neighbours.same(1,0,0) )||
        (neighbours.same(0,1,0)))
        )
        {
        glRotatef(-90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
        //1
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        //2
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE,Block::SIZE);
        //3
        glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
        glTexCoord2d(0, 0);
        //4
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(Block::SIZE,0);
        //5
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //6
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(0,0);
        ///7
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        ///8
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, 0);
    }
    //  2 1 0
    //  1 1 0
    //  0 0 0
    else if(
       !neighbours.same(0,1,1) &&
       !neighbours.same(-1,0,1) &&
       !neighbours.same(1,0,1) &&
       !neighbours.same(0,-1,1) &&
       !neighbours.same(1,1,1) &&
       !neighbours.same(-1,-1,1) &&
       !neighbours.same(1,-1,1) &&
        ((neighbours.same(0,1,0) )||
        (neighbours.same(-1,0,0) ))&&
        neighbours.same(-1,1,1)

            )
        {
        //glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
        //1
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        //2
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE,Block::SIZE);
        //3
        glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
        glTexCoord2d(0, 0);
        //4
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(Block::SIZE,0);
        //5
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //6
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(0,0);
        ///7
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        ///8
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, 0);


    }
    //  0 0 0
    //  0 1 1
    //  0 1 2
    else if(
       !neighbours.same(1,0,1) &&
       !neighbours.same(0,-1,1) &&
       !neighbours.same(0,1,1) &&
       !neighbours.same(-1,0,1) &&
       !neighbours.same(1,1,1) &&
       !neighbours.same(-1,-1,1) &&
       !neighbours.same(-1,1,1) &&
        neighbours.same(1,-1,1) &&
        ((neighbours.same(0,-1,0) )||
        (neighbours.same(1,0,0) ))


            )
        {
            glRotatef(-180,0,0,1);
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2d(0, 0);
            //1
            glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, 0);
            //2
            glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE,Block::SIZE);
            //3
            glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            glTexCoord2d(0, 0);
            //4
            glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
            glTexCoord2d(Block::SIZE,0);
            //5
            glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, Block::SIZE);
            //6
            glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
            glTexCoord2d(0,0);
            ///7
            glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, 0);
            ///8
            glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, Block::SIZE);
            //9
            glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            glTexCoord2d(0, 0);

    }
    //  0 0 0
    //  1 1 0
    //  2 1 0
  else if(
       !neighbours.same(-1,0,1) &&
       !neighbours.same(0,-1,1) &&
      !neighbours.same(0,1,1) &&
      !neighbours.same(-1,0,1) &&
       !neighbours.same(1,1,1) &&
       !neighbours.same(-1,1,1) &&
       !neighbours.same(1,-1,1) &&
        neighbours.same(-1,-1,1) &&
        ((neighbours.same(0,-1,0) )||
        (neighbours.same(-1,0,0) ))
          )

        {
        glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0, 0);
        //1
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        //2
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE,Block::SIZE);
        //3
        glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
        glTexCoord2d(0, 0);
        //4
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(Block::SIZE,0);
        //5
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //6
        glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
        glTexCoord2d(0,0);
        ///7
        glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, 0);
        ///8
        glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
        glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
        glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
        glTexCoord2d(0, 0);
    }


//  0 0 2  0 0 2  0 0 0
//  0 1 2  0 1 2  0 1 2
//  0 0 2  0 0 0  0 0 2
    else if(
       !neighbours.same(-1,-1,1) &&
       !neighbours.same(-1,0,1) &&
       !neighbours.same(-1,1,1) &&
       neighbours.same(1,0,1)
       )

        {
        glRotatef(180,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, 0);
       //2
           glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //3
           glVertex3d(-Block::SIZE /2, Block::SIZE/2,0);
       //
           glTexCoord2d(0, 0);
       //4
           glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
       //
           glTexCoord2d(Block::SIZE, 0);
       //5
           glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //6
           glVertex3d(-Block::SIZE/2, -Block::SIZE / 2,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);

           glTexCoord2d(Block::SIZE, 0);
       //8
           glVertex3d(Block::SIZE/2 , Block::SIZE/2 , 0);

           glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
           glVertex3d( -Block::SIZE/2, -Block::SIZE/2 , Block::SIZE);

            glTexCoord2d(0,0);
         //10
            glVertex3d  (-Block::SIZE/2,Block::SIZE/2 , Block::SIZE);
    }

    //  2 0 0  0 0 0  2 0 0
    //  2 1 0  2 1 0  2 1 0
    //  2 0 0  2 0 0  0 0 0
     else if(
       !neighbours.same(1,0,1) &&
       !neighbours.same(1,1,1) &&
       !neighbours.same(1,-1,1) &&
       neighbours.same(-1,0,1)
            )
        {

        //glRotatef(0,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, 0);
       //2
           glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //3
           glVertex3d(-Block::SIZE /2, Block::SIZE/2,0);
       //
           glTexCoord2d(0, 0);
       //4
           glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
       //
           glTexCoord2d(Block::SIZE, 0);
       //5
           glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //6
           glVertex3d(-Block::SIZE/2, -Block::SIZE / 2,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);

           glTexCoord2d(Block::SIZE, 0);
       //8
           glVertex3d(Block::SIZE/2 , Block::SIZE/2 , 0);

           glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
           glVertex3d( -Block::SIZE/2, -Block::SIZE/2 , Block::SIZE);

            glTexCoord2d(0,0);
         //10
            glVertex3d  (-Block::SIZE/2,Block::SIZE/2 , Block::SIZE);
    }

    //  0 0 0  0 0 0  0 0 0
    //  0 1 0  0 1 0  0 1 0
    //  2 2 2  2 2 0  0 2 2
    else if
       (
       !neighbours.same(-1,1,1) &&
       !neighbours.same(0,1,1) &&
       !neighbours.same(1,1,1) &&
       neighbours.same(0,-1,1)
       )


        {
        glRotatef(90,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, 0);
       //2
           glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //3
           glVertex3d(-Block::SIZE /2, Block::SIZE/2,0);
       //
           glTexCoord2d(0, 0);
       //4
           glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
       //
           glTexCoord2d(Block::SIZE, 0);
       //5
           glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //6
           glVertex3d(-Block::SIZE/2, -Block::SIZE / 2,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);

           glTexCoord2d(Block::SIZE, 0);
       //8
           glVertex3d(Block::SIZE/2 , Block::SIZE/2 , 0);

           glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
           glVertex3d( -Block::SIZE/2, -Block::SIZE/2 , Block::SIZE);

            glTexCoord2d(0,0);
         //10
            glVertex3d  (-Block::SIZE/2,Block::SIZE/2 , Block::SIZE);
    }
    //  2 2 2  0 2 2  2 2 0
    //  0 1 0  0 1 0  0 1 0
    //  0 0 0  0 0 0  0 0 0
    else if(
       !neighbours.same(-1,-1,1) &&
       !neighbours.same(0,-1,1) &&
       !neighbours.same(1,-1,1) &&
       neighbours.same(0,1,1)
            )
        {
        glRotatef(270,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
           glTexCoord2d(0, 0);
       //1
           glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, 0);
       //2
           glVertex3d(Block::SIZE / 2, Block::SIZE / 2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //3
           glVertex3d(-Block::SIZE /2, Block::SIZE/2,0);
       //
           glTexCoord2d(0, 0);
       //4
           glVertex3d(-Block::SIZE/2, Block::SIZE/2,Block::SIZE);
       //
           glTexCoord2d(Block::SIZE, 0);
       //5
           glVertex3d(-Block::SIZE / 2, -Block::SIZE/2,0);
       //
           glTexCoord2d(Block::SIZE, Block::SIZE);
       //6
           glVertex3d(-Block::SIZE/2, -Block::SIZE / 2,Block::SIZE);
       //
           glTexCoord2d(0,0);
       //7
           glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);

           glTexCoord2d(Block::SIZE, 0);
       //8
           glVertex3d(Block::SIZE/2 , Block::SIZE/2 , 0);

           glTexCoord2d(Block::SIZE, Block::SIZE);
        //9
           glVertex3d( -Block::SIZE/2, -Block::SIZE/2 , Block::SIZE);

            glTexCoord2d(0,0);
         //10
            glVertex3d  (-Block::SIZE/2,Block::SIZE/2 , Block::SIZE);
    }

    else

    {
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2d(0, 0);
            //1
            glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, 0);
            //2
            glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            glTexCoord2d(Block::SIZE, 0);
            //3
            glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
            glTexCoord2d(Block::SIZE, Block::SIZE);
            //4
            glVertex3d(0, 0,Block::SIZE);
            glTexCoord2d(0, 0);
            //5
            glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
            //6
            glTexCoord2d(Block::SIZE, 0);
            glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
            //8
            glTexCoord2d(Block::SIZE,Block::SIZE);
            glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
            ///9
            glTexCoord2d(0, 0);


            glVertex3d(0, 0,Block::SIZE);
            glTexCoord2d(Block::SIZE, 0);
            glVertex3d(Block::SIZE/2, Block::SIZE/2,0);
            glTexCoord2d(Block::SIZE, Block::SIZE);
    }
//End Superior plan...

}
 else

 {
         glBegin(GL_TRIANGLE_STRIP);
         glTexCoord2d(0, 0);
         //1
         glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
         glTexCoord2d(Block::SIZE, 0);
         //2
         glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
         glTexCoord2d(Block::SIZE, 0);
         //3
         glVertex3d(Block::SIZE /2, Block::SIZE/2,0);
         glTexCoord2d(Block::SIZE, Block::SIZE);
         //4
         glVertex3d(0, 0,Block::SIZE);
         glTexCoord2d(0, 0);
         //5
         glVertex3d(-Block::SIZE / 2, Block::SIZE / 2,0);
         //6
         glTexCoord2d(Block::SIZE, 0);
         glVertex3d(-Block::SIZE / 2, -Block::SIZE / 2,0);
         //8
         glTexCoord2d(Block::SIZE,Block::SIZE);
         glVertex3d(Block::SIZE / 2, -Block::SIZE / 2,0);
         ///9
         glTexCoord2d(0, 0);


         glVertex3d(0, 0,Block::SIZE);
         glTexCoord2d(Block::SIZE, 0);
         glVertex3d(Block::SIZE/2, Block::SIZE/2,0);
         glTexCoord2d(Block::SIZE, Block::SIZE);
 }

    glEnd();

    glPopMatrix();
}

  Core::Vector3D
  Triangle::specificCollision(const Core::Vector3D&, const Core::Vector3D& next) const
  {
    return next;
  }
} // Block
