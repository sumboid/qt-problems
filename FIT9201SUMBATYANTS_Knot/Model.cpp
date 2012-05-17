#include "Model.h"
#include "Line.h"
#include "Vector.h"
#include "Camera.h"
#include "Bezier.h"
#include "Knot.h"
#include "CustomSpline.h"
#include <iostream>

Model::Model(View* _view, Camera* _camera):
view(_view), camera(_camera)
{
    double ps[6][3] =
            { {70, 0, 90}
            , {100, 100, 0}
            , {0, 100, 100}
            , {90, 0, 0}
            , {90, 90, 100}
            , {0, 100, 0}};
    knot = new Knot(ps, 6);
    bounds = knot->getBounds();
    Vector min(bounds[0], bounds[1], bounds[2]);
    Vector max(bounds[3], bounds[4], bounds[5]);
    Vector id(max);
    id.subtract(min);
    id.multiply(1. / 2.);
    id.subtract(min);
    camera->setCenter(id);
}

Model::~Model()
{
    delete knot;
}


void Model::draw()
{
    view->clear();
    knot->draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[2], bounds[3], bounds[1], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[2], bounds[0], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[2], bounds[0], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[5], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[5], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[1], bounds[2], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[1], bounds[2], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[4], bounds[2], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[4], bounds[2], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    view->paint();
}

void Model::resize()
{
}
