#include "Controller.h"
#include "Model.h"

#include <iostream>

namespace
{
    const int MSEC_INTERVAL = 100;
}

Controller::~Controller()
{
    delete model;
}
Controller::Controller(View* view)
{
    model = new Model(view);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.setInterval(MSEC_INTERVAL);
}

void Controller::update()
{
    model->draw();
}

void Controller::start()
{
    //model->invertButton(false);
    timer.start();
}

void Controller::stop()
{
    //model->invertButton(true);
    timer.stop();
}

void Controller::clear()
{
    model->invertButton(true);
    timer.stop();
    //model->clear();
}

void Controller::setWidth(const int width)
{
    //model->setWidth(width);
}

void Controller::setHeight(const int height)
{
    //model->setHeight(height);
}

void Controller::setSpeed(const int speed)
{
    //model->setSpeed(speed);
}

void Controller::resize()
{
    //model->resize();
}

void Controller::setAngle(const int angle)
{
    model->setAngle(static_cast<double>(angle) / 180 * 3.14159265);
    model->draw();
}
