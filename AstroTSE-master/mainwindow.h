#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "astroGame.h"
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *WelcomePage;
    QLabel* cadreImage;
    QLabel* titrePage;
    QLineEdit* champs;
    QWidget* page ;
    MyWidget AstroTseWidget;

public:
    explicit MainWindow(QWidget *parent = nullptr);
public slots:
    void play();
signals:

};

#endif // MAINWINDOW_H
