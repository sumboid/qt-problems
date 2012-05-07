#include "Controller.h"
#include "Model.h"

#include <iostream>

namespace
{
    const int MSEC_INTERVAL = 10;
}

Controller::~Controller()
{
    delete model;
}
Controller::Controller(View* view): step(0)
{
    model = new Model(view);
    connect(&timer, SIGNAL(timeout()), this, SLOT(nextStep()));
    timer.setInterval(MSEC_INTERVAL);
}

void Controller::update()
{
    model->draw();
}

void Controller::resize()
{
    model->resize();
}

void Controller::start()
{
    model->invertButton(false);
    timer.start();
}

void Controller::stop()
{
    model->invertButton(true);
    timer.stop();
}

void Controller::init()
{
    model->invertButton(true);
    timer.stop();
    model->init();
    step = 0;
    setStep(0);
    update();
}

void Controller::setBlend(const int blend)
{
    model->setBlend(blend);
    update();
}

void Controller::setFilter(const int filter)
{
    model->setFilter(filter);
    update();
}

void Controller::setStep(const int _step)
{
    step = _step;
    model->setStep(_step);
    model->draw();
}

void Controller::nextStep()
{
    step == 360 ? step = 1 : step++;
    setStep(step);
}
