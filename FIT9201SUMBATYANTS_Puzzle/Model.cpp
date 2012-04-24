#include <QPixmap>
#include <QResource>
#include <math.h>
#include <stdlib.h>
#include "Model.h"

#include <iostream>

Model::Model(View* _view): 
view(_view), angle(0), image(QPixmap(":/puzzle.png").toImage())
{
    for(int i = 0; i < 32; i++)
    {
        triangles[i] = Triangle(view, image);
    }
}

Model::~Model()
{}

void Model::draw() const
{
    Triangle t(view, image);
    setTrianglePoints(t, 0);
    t.setScale(1);
    t.draw(Point(view.getWidth()/2, view.getHeight()/2), 0);
}

void Model::setTrianglePoints(Trinagle& triangle, const int number)
{
    Point a, b, c;
    a.first = 0;
    a.second = 0;
    c.first = 0;
    c.second = image.height() - 1;
    b.first = image.width() - 1;
    b.second = image.height() - 1;
}

void Model::setAngle(const double _angle)
{
    angle = _angle;
}

void Model::invertButton(bool state)
{
    view->invertButton(state);
}
