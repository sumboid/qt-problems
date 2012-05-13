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
    double angle = 3.1415 / 180;
    double matrix[4][3] = {{0, angle, 0},
                          {0, -angle, 0},
                          {-angle, 0, 0},
                          {angle, 0, 0}};
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
            camera->translate(1);
            break;
        case DOWN:
            camera->translate(-1);
            break;
        default:
            return;
    }
}

void Controller::scale(bool b)
{
    double more[3] = {1, 1, 1};
    double less[3] = {-1, -1, -1};
    b ? camera->scale(more) : camera->scale(less);
}           

void Controller::reset()
{
    camera->reset();
}
