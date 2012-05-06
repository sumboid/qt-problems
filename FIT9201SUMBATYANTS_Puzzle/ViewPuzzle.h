#pragma once
#include <QObject>
#include <QtGui/QApplication>
#include <QMainWindow>

#include "View.h"
#include <Controller.h>
#include "PainterWidget.h"
#include "ui_MainWindow.h"

namespace Ui
{
    class MainWindow;
}

class ViewPuzzle: public View, public QObject
{
public:
    ViewPuzzle();
    virtual ~ViewPuzzle();

    virtual int getWidth();
    virtual int getHeight();
    virtual void paint();
    virtual void clear();
    virtual void setPixel(int x, int y, unsigned int color);
    virtual void invertButton(bool state);
    virtual unsigned int getColor(int x, int y);
    virtual void setDial(const int);

private:
    Ui::MainWindow ui;
    QMainWindow mainWindow;
    PainterWidget* painterWidget;
    Controller* controller;
};
