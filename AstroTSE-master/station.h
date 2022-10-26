#ifndef STATION_H
#define STATION_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include <QImage>

class Station
{
public:
    Station(int pos);
    void setPosz(int pos){ posz = pos;}
    int getPosz(){return posz;}
    // Methode d'affichage
    void Display() const;
private :
    int posz;
};

#endif // STATION_H
