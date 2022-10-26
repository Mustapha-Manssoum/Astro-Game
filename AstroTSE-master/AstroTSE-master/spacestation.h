#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QImage>
class SpaceStation
{
private:
    GLuint* textureID = new GLuint[2];
    float rotationAngle = 0;
public:
    SpaceStation();
    /* Displaying methods */
    void Display();
    void LoadTexture();
};

#endif // SPACESTATION_H
