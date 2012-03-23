#include "ControllerSin.h"
#include "ModelSin.h"

ControllerSin::~ControllerSin()
{
    delete model;
}
ControllerSin::ControllerSin(View* view)
{
    model = new ModelSin(view);
}

void ControllerSin::update()
{
    model->update();
}

void ControllerSin::drawFunction()
{
    model->setFunction();
}

void ControllerSin::drawAxis()
{
    model->setAxis();
}

void ControllerSin::clear()
{
    model->clear();
}
