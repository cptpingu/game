#ifndef BLOCK_H
#define BLOCK_H

class block
{
public:

    void Draw(block b)const;
    block(int x,int y,int z,int taille);
    block();
public:


    int _x;
    int _y;
    int _z;
    int taille;

};

#endif // BLOCK_H
