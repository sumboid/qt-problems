#include "Controller.h"
#include "Model.h"


Controller::~Controller()
{
    delete model;
}

Controller::Controller(View* view)
{
    camera = new Camera();
    model = new Model(view, camera);
}

void Controller::update()
{
    model->draw();
}

void Controller::resize()
{
    model->resize();
}

void Controller::rotate(Direction direction)
{
    double angle = 3.1415 / 60;
    double matrix[4][3] = {{0, -angle, 0},
                          {0, angle, 0},
                          {angle, 0, 0},
                          {-angle, 0, 0}};
    switch(direction)
    {
        case LEFT:
            camera->rotate(matrix[0]);
            break;
        case RIGHT:
            camera->rotate(matrix[1]);
            break;
        case UP:
            camera->rotate(matrix[2]);
            break;
        case DOWN:
            camera->rotate(matrix[3]);
            break;
        default:
            return;
    }
}

void Controller::translate(Direction direction)
{
    switch(direction)
    {
        case UP:
            camera->translate(5);
            break;
        case DOWN:
            camera->translate(-5);
            break;
        default:
            return;
    }
}

void Controller::reset()
{
    camera->reset();
}
