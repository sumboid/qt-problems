#include <QSize>
#include "ViewPuzzle.h"
#include "Controller.h"

#include <iostream>
namespace
{
    const int START_SPEED = 5000;
}

ViewPuzzle::ViewPuzzle()
{
    controller = new Controller(this);
    painterWidget = new PainterWidget(controller);
    mainWindow.setMinimumSize(500, 400);
    ui.setupUi(&mainWindow);
    ui.horizontalLayout_2->insertWidget(0, painterWidget, 1);
    ui.stopButton->setDisabled(true);

    connect(ui.blendCheckBox, SIGNAL(stateChanged(int)), controller, SLOT(setBlend(int)));
    connect(ui.filterCheckBox, SIGNAL(stateChanged(int)), controller, SLOT(setFilter(int)));
    connect(ui.dial, SIGNAL(valueChanged(int)), controller, SLOT(setStep(int)));
    connect(ui.initButton, SIGNAL(clicked()), controller, SLOT(init(void)));
    connect(ui.startButton, SIGNAL(clicked()), controller, SLOT(start(void)));
    connect(ui.stopButton, SIGNAL(clicked()), controller, SLOT(stop(void)));

    mainWindow.show();
    controller->update();
}
ViewPuzzle::~ViewPuzzle()
{
    delete painterWidget;
    delete controller;
}

int ViewPuzzle::getWidth()
{
    return painterWidget->getHeight();
}

int ViewPuzzle::getHeight()
{
    return painterWidget->getWidth();
}

int ViewPuzzle::getWindowHeight()
{
    return mainWindow.height();
}

int ViewPuzzle::getWindowWidth()
{
    return mainWindow.width();
}

void ViewPuzzle::setWindowWidth(const int width)
{
    mainWindow.resize(width, mainWindow.height());
}

void ViewPuzzle::setWindowHeight(const int height)
{
    mainWindow.resize(mainWindow.width(), height);
}

void ViewPuzzle::setPixel(int x, int y, unsigned int color)
{
    painterWidget->setPixel(x, y, color);
}

void ViewPuzzle::clear()
{
    painterWidget->clear();
}

void ViewPuzzle::paint()
{
    painterWidget->paint();
}

void ViewPuzzle::setWidthSpin(const int x)
{
  //  ui.widthSpin->setValue(x);
}

void ViewPuzzle::setHeightSpin(const int x)
{
  //  ui.heightSpin->setValue(x);
}

void ViewPuzzle::invertButton(bool state)
{
  //  ui.startButton->setDisabled(!state);
  //  ui.stopButton->setDisabled(state);
}

int ViewPuzzle::getSpeed()
{
    return START_SPEED;
}
