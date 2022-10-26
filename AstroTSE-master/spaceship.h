#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QImage>


class SpaceShip
{
private:
    float * position;
public:
    SpaceShip();

    /* Displaying methods */
    void Display(int posx, int posy,int posz,int teta,int phi);
    void DrawShip();
    void DrawWings(GLUquadric*);
    void DrawLights(GLUquadric*);


    /* Getters */
    float * GetPosition() { return position; }

    /* Setters */
    void SetPosition(float * pos) { position = pos; }

};

#endif // SPACESHIP_H
