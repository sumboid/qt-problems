#include <QSize>
#include "ViewRainbow.h"
#include "Controller.h"

namespace
{
    const int START_SPEED = 5000;
}

ViewRainbow::ViewRainbow()
{
    controller = new Controller(this);
    painterWidget = new PainterWidget(controller);
    mainWindow.setMinimumSize(500, 400);
    ui.setupUi(&mainWindow);
    ui.verticalLayout_2->insertWidget(0, painterWidget, 1);
    ui.stopButton->setDisabled(true);
    ui.speedSlider->setValue(START_SPEED);

    connect(ui.colorSlider, SIGNAL(valueChanged(int)), controller, SLOT(setPhase(int)));
    connect(ui.clearButton, SIGNAL(clicked()), controller, SLOT(clear(void)));
    connect(ui.startButton, SIGNAL(clicked()), controller, SLOT(start(void)));
    connect(ui.stopButton, SIGNAL(clicked()), controller, SLOT(stop(void)));
    connect(ui.speedSlider, SIGNAL(valueChanged(int)), controller, SLOT(setSpeed(int)));
    connect(ui.widthSpin, SIGNAL(valueChanged(int)), controller, SLOT(setWidth(int)));
    connect(ui.heightSpin, SIGNAL(valueChanged(int)), controller, SLOT(setHeight(int)));

    mainWindow.show();
}
ViewRainbow::~ViewRainbow()
{
    delete painterWidget;
    delete controller;
}

int ViewRainbow::getWidth()
{
    return painterWidget->getHeight();
}

int ViewRainbow::getHeight()
{
    return painterWidget->getWidth();
}

int ViewRainbow::getWindowHeight()
{
    return mainWindow.height();
}

int ViewRainbow::getWindowWidth()
{
    return mainWindow.width();
}

void ViewRainbow::setWindowWidth(const int width)
{
    mainWindow.resize(width, mainWindow.height());
}

void ViewRainbow::setWindowHeight(const int height)
{
    mainWindow.resize(mainWindow.width(), height);
}

void ViewRainbow::setPixel(int x, int y, unsigned int color)
{
    painterWidget->setPixel(x, y, color);
}

void ViewRainbow::clear()
{
    painterWidget->clear();
}

void ViewRainbow::paint()
{
    painterWidget->paint();
}

void ViewRainbow::setWidthSpin(const int x)
{
    ui.widthSpin->setValue(x);
}

void ViewRainbow::setHeightSpin(const int x)
{
    ui.heightSpin->setValue(x);
}

void ViewRainbow::invertButton(bool state)
{
    ui.startButton->setDisabled(!state);
    ui.stopButton->setDisabled(state);
}

int ViewRainbow::getSpeed()
{
    return START_SPEED;
}
