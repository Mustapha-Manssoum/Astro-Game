#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "space.h"
#include "spaceship.h"
#include "spacestation.h"
#include "asteroid.h"
#include "qpainter.h"

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QTimer>
#include <QApplication>
#include <GL/glu.h>
#include <stdlib.h>
#include <windows.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>

#include <cstdio>
#include <iostream>
#include <vector>
#include <QLabel>

/*QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE*/


class MyWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyWidget(QOpenGLWidget * = nullptr);
    ~MyWidget();

public:
    //Ui::Widget *ui;
    const unsigned int W = 1400;
    const unsigned int H = 800;
    const unsigned int NB_ASTEROIDS = 16;

private:
//    remember to change the file path
    cv::String pathToXmlPaml = "C:/Users/DELL PRECISION/Desktop/DEV_multimedia/AstroTSE/AstroTSE-master/palm.xml";
    cv::String pathtoXmlClosedPalm = "C:/Users/DELL PRECISION/Desktop/DEV_multimedia/TEST FOR PROJECT/MoveObjectWin/closed_frontal_palm.xml";
    Space * space;
    SpaceShip * spaceship;
    SpaceStation *stationTSE;

    int posx = 0;
    int posy = -8;
    int posz = 35;

//  Initial position of the spaceship

    float X = 0;
    float Y = 10;
    float Z = 70;
    int phi = 0;
    int teta = 0;

//  Asteroids

    Asteroid ** asteroids;
    int GENERATED_ASTEROIDS =0;



    float m_TimeElapsed { 0.0f };
    QTimer * m_AnimationTimer;
    QElapsedTimer * timer;

    float * CAM_POS = new float[3]{0.,25., 60.};
    float * CAM_TARGET = new float[3]{0.,0., 0.};

    int frameWidth=840;
    int frameHeight=680;
    cv::VideoCapture cap;
    cv::CascadeClassifier palm_cascad;
    cv::CascadeClassifier fist_cascade;
    QLabel * camFrame = nullptr;

private:
//  Herited methods from QOpenGLWidget. Overrided methods
    virtual void initializeGL();
    virtual void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent * event);

    void GenerateAsteroid(unsigned int);
    void DisplayAsteroids();
    void displayCamera();
    void DisplayTimer();
    void GameOver(BOOL WonOrLost);

private slots:
    void Refresh(); //refresh the window

};
#endif // WIDGET_H
