#ifndef SPACE_H
#define SPACE_H

#include <qopengl.h>
#include <GL/glu.h>
//#include <QGLWidget>
#include <QImage>

class Space
{
public:
    Space();
    void Display(uint64_t);

private:
    GLuint* textureID = new GLuint[2];
    double spaceSpeed;
    /* Methods */
    void LoadTexture();

    /* Getters */
    float GetSpaceWidth() const { return 50.; }
    float GetSpaceHeight() const {return 200.; }
    float GetSpaceSpeed() const { return spaceSpeed; }

    /* Destructor */
    ~Space();
};

#endif // SPACE_H
