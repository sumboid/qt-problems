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

void Controller::start()
{
    model->invertButton(false);
    timer.start();
    lastTime.start();
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

void Controller::setBlend(int blend)
{
    model->setBlend(blend);
    update();
}

void Controller::setFilter(int filter)
{
    model->setFilter(filter);
    update();
}

void Controller::setStep(int _step)
{
    step = _step;
    model->setStep(_step);
    model->draw();
}

void Controller::nextStep()
{
    int delta = lastTime.elapsed();
    int steps = delta / MSEC_INTERVAL;
    step = (step + steps) % 360;
    //step == 360 ? step = 1 : step++;
    lastTime.restart();
    setStep(step);
}

void Controller::getInfo(int x, int y)
{
    model->getInfo(x, y);
}

void Controller::resize(int flag)
{
    model->resize(flag);
    model->draw();
}
