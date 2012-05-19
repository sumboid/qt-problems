#include <QSize>
#include "ViewPlotter.h"
#include "Controller.h"

namespace
{
    const int START_SPEED = 5000;
}

ViewPlotter::ViewPlotter()
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
ViewPlotter::~ViewPlotter()
{
    delete painterWidget;
    delete controller;
}

int ViewPlotter::getWidth()
{
    return painterWidget->getHeight();
}

int ViewPlotter::getHeight()
{
    return painterWidget->getWidth();
}

int ViewPlotter::getWindowHeight()
{
    return mainWindow.height();
}

int ViewPlotter::getWindowWidth()
{
    return mainWindow.width();
}

void ViewPlotter::setWindowWidth(const int width)
{
    mainWindow.resize(width, mainWindow.height());
}

void ViewPlotter::setWindowHeight(const int height)
{
    mainWindow.resize(mainWindow.width(), height);
}

void ViewPlotter::setPixel(int x, int y, unsigned int color)
{
    painterWidget->setPixel(x, y, color);
}

void ViewPlotter::clear()
{
    painterWidget->clear();
}

void ViewPlotter::paint()
{
    painterWidget->paint();
}

void ViewPlotter::setWidthSpin(const int x)
{
    ui.widthSpin->setValue(x);
}

void ViewPlotter::setHeightSpin(const int x)
{
    ui.heightSpin->setValue(x);
}

void ViewPlotter::invertButton(bool state)
{
    ui.startButton->setDisabled(!state);
    ui.stopButton->setDisabled(state);
}

int ViewPlotter::getSpeed()
{
    return START_SPEED;
}
