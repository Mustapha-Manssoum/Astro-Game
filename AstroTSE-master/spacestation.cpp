#include "spacestation.h"

SpaceStation::SpaceStation()
{
}
void SpaceStation::LoadTexture(){

    glGenTextures(2, textureID);

    QImage imgTSE = QImage(":/LogoTSE.jpg");
    QImage logoTse = imgTSE.convertToFormat(QImage::Format_RGBA8888);

    QImage imgSpaceship = QImage(":/spaceship.jpg");
    QImage spaceship = imgSpaceship.convertToFormat(QImage::Format_RGBA8888);

    /* Space texture */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, logoTse.width(), logoTse.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, logoTse.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, spaceship.width(), spaceship.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, spaceship.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

}
void SpaceStation::Display(){

    // The rotation of the spaceship on itself
    // The two cylinders will rotate in opposite directions
    rotationAngle+=1;

    LoadTexture();

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,10,-350);
    glRotatef(rotationAngle,1,0,0);
    GLUquadric* outsideCore = gluNewQuadric();
    gluQuadricDrawStyle(outsideCore, GLU_FILL);
    gluQuadricTexture(outsideCore,GLU_TRUE);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    gluCylinder(outsideCore, 30., 20., 4., 100, 100);
    gluDeleteQuadric(outsideCore);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,-350);
    glRotatef(rotationAngle,0,1,0);
    GLUquadric* insideCore = gluNewQuadric();
    gluQuadricDrawStyle(insideCore, GLU_FILL);
    gluQuadricTexture(insideCore,GLU_TRUE);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    gluCylinder(insideCore, 20., 10., 6., 100, 100);
    gluDeleteQuadric(insideCore);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,-350);
    GLUquadric* tseStation = gluNewQuadric();
    gluQuadricDrawStyle(tseStation, GLU_FILL);
    gluQuadricTexture(tseStation,GLU_TRUE);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    gluSphere(tseStation,5,100.,100.);
    gluDeleteQuadric(tseStation);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
