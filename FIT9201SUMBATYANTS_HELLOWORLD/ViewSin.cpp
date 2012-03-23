#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSize>
#include <assert.h>
#include "ViewSin.h"
#include "ControllerSin.h"

namespace
{
    static const char TITLE[] = "FIT9201SUMBATYANTS_HELLOWORLD";
}

ViewSin::ViewSin()
{
    controller = new ControllerSin(this);
    painterWidget = new PainterWidget(controller);
    ui.setupUi(&mainWindow);
    ui.verticalLayout_2->insertWidget(0, painterWidget, 1);
    connect(ui.clearButton, SIGNAL(clicked()), controller, SLOT(clear(void)));
    connect(ui.sinButton, SIGNAL(clicked()), controller, SLOT(drawFunction(void)));
    connect(ui.axisButton, SIGNAL(clicked()), controller, SLOT(drawAxis(void)));
    mainWindow.setWindowTitle(TITLE);

    mainWindow.show();
}
ViewSin::~ViewSin()
{
    delete controller;
    delete painterWidget;
}

int ViewSin::getWidth()
{
    return painterWidget->getHeight();
}

int ViewSin::getHeight()
{
    return painterWidget->getWidth();
}

void ViewSin::setPixel(int x, int y, uint color)
{
    painterWidget->setPixel(x, y, color);
}

void ViewSin::paint()
{
    painterWidget->paint();
}
