#ifndef ASTEROID_H
#define ASTEROID_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QImage>

class Asteroid
{
private:
    int X = 0;
    int Y = 0;
    int Z = 0;
    int radius = 0;
    GLuint* textureID = new GLuint[1];
public:
    Asteroid();
    /* Methods */

    //void Display(int radius);//, unsigned int i);
    void Display(int radius, int X,int Y, int Z);

    void LoadTexture();

    //void DrawAsteroid(int radius);//, unsigned int i);
    void DrawAsteroid(int radius, int X,int Y, int Z);

    /* Getters*/
    int  GetX() { return X; }
    int  GetY() { return Y; }
    int  GetZ() { return Z; }
    int  GetRadius() { return radius; }


     /*Setters*/
    void SetX(int pos) { X = pos; }
    void SetY(int pos) { Y = pos; }
    void SetZ(int pos) { Z = pos; }
    void SetRadius(int pos) { radius = pos; }
};

#endif // ASTEROID_H
