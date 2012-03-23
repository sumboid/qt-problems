#ifndef VIEWSIN_H
#define VIEWSIN_H

#include <QtGui/QApplication>
#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>

#include "View.h"
#include "PainterWidget.h"
#include "ControllerSin.h"
#include "ui_mainwindow.h"
namespace Ui
{
    class MainWindow;
}

class ViewSin : public View, public QObject
{
public:
    ViewSin();
    virtual ~ViewSin();


    virtual int getWidth();
    virtual int getHeight();
    virtual void paint();

    virtual void setPixel(int x, int y, uint color);
private:
    ControllerSin* controller;
    PainterWidget* painterWidget;
    Ui::MainWindow ui;
    QMainWindow mainWindow;
};

#endif // VIEWSIN_H
