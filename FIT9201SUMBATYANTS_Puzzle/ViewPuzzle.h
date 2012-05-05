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
    virtual int getWindowWidth();
    virtual int getWindowHeight();
    virtual void setWindowWidth(const int width);
    virtual void setWindowHeight(const int height);
    virtual void paint();
    virtual void clear();
    virtual void setPixel(int x, int y, unsigned int color);
    virtual void invertButton(bool state);
    virtual unsigned int getColor(int x, int y);

private:
    Ui::MainWindow ui;
    QMainWindow mainWindow;
    PainterWidget* painterWidget;
    Controller* controller;
};
