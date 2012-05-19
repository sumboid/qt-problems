#include "Model.h"
#include "Line.h"
#include "Vector.h"
#include "Camera.h"
#include "Bezier.h"
#include "Knot.h"
#include "CustomSpline.h"
#include <iostream>

Model::Model(View* _view, Camera* _camera):
view(_view), camera(_camera), boundBox(false)
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
    delete bounds;
}


void Model::draw()
{
    view->clear();
    knot->draw(view, camera, 0x0);
    if(boundBox)
    {
        drawBounds();
    }
    drawAxis();
    view->paint();
}

void Model::drawBounds()
{
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
}

void Model::drawAxis()
{
    Line(0, 0, 0, 100, 0, 0).draw(view, camera, 0xff0000);
    Line(0, 0, 0, 0, 100, 0).draw(view, camera, 0x00ff00);
    Line(0, 0, 0, 0, 0, 100).draw(view, camera, 0x0000ff);
}

void Model::setBoundBox(bool flag)
{
    boundBox = flag;
}

void Model::resize()
{
}
