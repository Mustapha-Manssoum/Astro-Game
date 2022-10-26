#include "spaceship.h"

SpaceShip::SpaceShip()
{
}
void SpaceShip::Display(int posx, int posy, int posz,int teta,int phi){

    glPushMatrix();
    // Translation of the spaceship
    glTranslatef(posx, posy, posz);
    //Rotaton of the spaceship
    glRotatef(teta, 1, 0, 0);
    glRotatef(phi, 0, 1, 0);
    DrawShip();
    glPopMatrix();

}
void SpaceShip::DrawShip(){
    /* Rotate spaceship */
    glRotatef(180, 1, 0, 0);


    GLUquadric* head = gluNewQuadric();
    gluQuadricDrawStyle(head, GLU_FILL);
    gluCylinder(head, 2., 0., 10., 20, 20);
    gluDeleteQuadric(head);
    /*Drawing the core of the spaceship*/
    glTranslatef(0, 0, -6);
    //glRotatef(180, 0, 1, 1);
    GLUquadric* core = gluNewQuadric();
    gluQuadricDrawStyle(core,GLU_FILL);
    gluCylinder(head, 1., 2., 6., 20, 20);
    gluDeleteQuadric(core);

    /*Drawing the tale of the spaceship*/
    GLUquadric* tale = gluNewQuadric();
    gluQuadricDrawStyle(tale,GLU_FILL);
    gluDisk(tale, 1., 2., 30, 2);
    gluDeleteQuadric(tale);


}
void SpaceShip::DrawWings(GLUquadric* quadrique){

    gluQuadricDrawStyle(quadrique, GLU_FILL);
    gluPartialDisk(quadrique,0.5,2.,15,2,0.,120.);
    gluDeleteQuadric(quadrique);
}

