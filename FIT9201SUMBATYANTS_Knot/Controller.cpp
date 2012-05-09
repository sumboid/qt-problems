#include "Controller.h"
#include "Model.h"

Controller::~Controller()
{
    delete model;
}
Controller::Controller(View* view): model(new Model(view))
{
}

void Controller::update()
{
    model->draw();
}

void Controller::resize()
{
    model->resize();
}
