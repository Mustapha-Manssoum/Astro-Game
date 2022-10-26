#include "asteroid.h"

Asteroid::Asteroid()
{

}
void Asteroid::LoadTexture(){

    glGenTextures(2, textureID);

    QImage imgAsteroid = QImage(":/asteroid2.jpg");
    QImage asteroid = imgAsteroid.convertToFormat(QImage::Format_RGBA8888);

    /* Asteroid texture */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, asteroid.width(), asteroid.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, asteroid.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Asteroid::Display(int radius, int X,int Y, int Z){
    DrawAsteroid(radius, X, Y,Z);
}

void Asteroid::DrawAsteroid(int radius, int X,int Y, int Z){
    glPushMatrix();
    LoadTexture();
    glTranslated(X,Y,Z);
    GLUquadric* quadrique = gluNewQuadric();
    gluQuadricDrawStyle(quadrique, GLU_FILL);
    gluQuadricTexture(quadrique,GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    /* Bind space texture to array */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    gluSphere(quadrique,radius,50.,70.);
    gluDeleteQuadric(quadrique);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

