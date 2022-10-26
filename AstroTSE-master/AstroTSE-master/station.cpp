#include "station.h"

Station::Station(int pos)
{
    posz = pos;
}
void Station::Display() const{
    glEnable(GL_TEXTURE_2D);
    QImage Orbite  = QImage(":/tse.jpg");
    QImage textureOrbite = Orbite.convertToFormat(QImage ::Format_RGBA8888);

    QImage telecom  = QImage("../../TD/res/vaisseau.jpg");
    QImage textureTelecom = telecom.convertToFormat(QImage ::Format_RGBA8888);

    GLuint *textures = new GLuint[3];
    glGenTextures(3,textures);
    // on definit la texture courante
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // on definit les caracteristique de la textures courantes
    glTexImage2D(GL_TEXTURE_2D,0,4, textureOrbite.width(),textureOrbite.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,textureOrbite.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    // on definit les caracteristique de la textures courantes
    glTexImage2D(GL_TEXTURE_2D,0,4, textureTelecom.width(),textureTelecom.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,textureTelecom.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    GLUquadric* quadrique2 = gluNewQuadric();
   gluQuadricDrawStyle(quadrique2,GLU_FILL);
   gluQuadricTexture(quadrique2,GLU_TRUE);
   glPushMatrix();


   glTranslated(0,0 ,posz);

   gluCylinder(quadrique2,5,8,1,20,20);
   glNormal3f(0.0,0.0,1.0);
   glPopMatrix();
   glBindTexture(GL_TEXTURE_2D, textures[0]);
   GLUquadric* quadriqueCentral = gluNewQuadric();
   gluQuadricDrawStyle(quadriqueCentral,GLU_FILL);
   gluQuadricTexture(quadriqueCentral,GLU_TRUE);
   glPushMatrix();
   glTranslated(0,0 ,posz);
   glRotated(180,0,0,1);

   gluDisk(quadriqueCentral,0,5,20,1);
   glNormal3f(0.0,0.0,1.0);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
