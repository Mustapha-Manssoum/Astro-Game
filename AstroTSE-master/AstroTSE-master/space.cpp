#include "space.h"

Space::Space()
{
spaceSpeed =0.;
}
void Space::LoadTexture(){

    glGenTextures(2, textureID);

    QImage imgSpace = QImage(":/space2.jpg");
    QImage space = imgSpace.convertToFormat(QImage::Format_RGBA8888);

    /* Space texture */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, space.width(), space.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, space.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Space::Display(uint64_t m_TimeElapsed){

    /* Define speeds */
    spaceSpeed = (m_TimeElapsed % 5) / 5.;




    glPushMatrix();
    /* Load all textures. */
    LoadTexture();
    GLUquadric* quadrique = gluNewQuadric();
    gluQuadricDrawStyle(quadrique, GLU_FILL);
    gluQuadricTexture(quadrique,GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    /* Bind space texture to array */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    //gluQuadricOrientation(quadrique,GLU_INSIDE);
    gluSphere(quadrique,350,20.,20.);
    gluDeleteQuadric(quadrique);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

