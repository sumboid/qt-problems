#include "Controller.h"
#include "Model.h"

namespace
{
    const int MSEC_INTERVAL = 50;
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
    model->drawPixels();
}

void Controller::start()
{
    timer.start();
}

void Controller::stop()
{
    timer.stop();
}

void Controller::clear()
{
    timer.stop();
    model->clear();
}

void Controller::setWidth(const int width)
{
    model->setWidth(width);
}

void Controller::setHeight(const int height)
{
    model->setHeight(height);
}

void Controller::setSpeed(const int speed)
{
    model->setSpeed(speed);
}
