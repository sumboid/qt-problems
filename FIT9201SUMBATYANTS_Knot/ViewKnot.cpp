#include <QSize>
#include "ViewKnot.h"
#include "Controller.h"

ViewKnot::ViewKnot()
{
    controller = new Controller(this);
    painterWidget = new PainterWidget(controller);
    mainWindow.setMinimumSize(500, 400);
    ui.setupUi(&mainWindow);
    ui.verticalLayout->insertWidget(0, painterWidget, 1);
    connect(ui.boundButton, SIGNAL(stateChanged(int)), controller, SLOT(setBounds(int)));


    mainWindow.show();
    controller->update();
}
ViewKnot::~ViewKnot()
{
    delete painterWidget;
    delete controller;
}

int ViewKnot::getWidth()
{
    return painterWidget->getHeight();
}

int ViewKnot::getHeight()
{
    return painterWidget->getWidth();
}

void ViewKnot::setPixel(int x, int y, unsigned int color)
{
    painterWidget->setPixel(x, y, color);
}

void ViewKnot::clear()
{
    painterWidget->clear();
}

void ViewKnot::paint()
{
    painterWidget->paint();
}

unsigned int ViewKnot::getColor(int x, int y)
{
    return painterWidget->getColor(x, y);
}
