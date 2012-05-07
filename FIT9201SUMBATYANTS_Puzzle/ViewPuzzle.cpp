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

void ViewPuzzle::invertButton(bool state)
{
    ui.startButton->setDisabled(!state);
    ui.stopButton->setDisabled(state);
}

unsigned int ViewPuzzle::getColor(int x, int y)
{
    return painterWidget->getColor(x, y);
}

void ViewPuzzle::setDial(const int step)
{
    ui.dial->setValue(step);
}

void ViewPuzzle::setBar(const char* message)
{
    ui.statusBar->showMessage(message);
}
