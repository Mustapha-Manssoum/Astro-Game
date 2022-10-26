#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1400, 800);
    setStyleSheet("background-color:grey");
    page = new QWidget(this);
    page->setGeometry(0,0,this->width(),this->height());

    WelcomePage = new QWidget(page);


    WelcomePage->setGeometry(0,0,this->width(),this->height());
    WelcomePage->setStyleSheet("background-color:green");
    cadreImage = new QLabel(WelcomePage);
    cadreImage->setGeometry(0,0,WelcomePage->width()/3,WelcomePage->height()/3);
    cadreImage->setStyleSheet("background-color:red");
    cadreImage->setPixmap(QPixmap(":/tse.jpg").scaled(cadreImage->size(),Qt::IgnoreAspectRatio));

    titrePage = new QLabel("<h1>ASTRO GAME</h1>",WelcomePage);
    titrePage->setGeometry(WelcomePage->width()/2,0,WelcomePage->width()/3,WelcomePage->height()/5);
    titrePage->setStyleSheet("background-color:transparent;color:black;font-size:30px;");

    champs = new QLineEdit("10",WelcomePage);
    champs->setGeometry(WelcomePage->width()/2,WelcomePage->height()/2,WelcomePage->width()/3,WelcomePage->height()/6);
    champs->setStyleSheet("background-color:red;color:white;border-radius:20%");
    champs->setAlignment(Qt::AlignCenter);
    champs->text().toInt();
    QPushButton *btn = new QPushButton("play",WelcomePage);
    connect(btn,SIGNAL(clicked()),this,SLOT(play()));
    AstroTseWidget.setGeometry(0,0,this->width(),this->height());

}
void MainWindow::play(){
    int d = champs->text().toInt();
    WelcomePage->deleteLater();
    //this->deleteLater();
    AstroTseWidget.show();
}
