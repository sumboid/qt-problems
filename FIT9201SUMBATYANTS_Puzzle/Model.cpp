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
        //triangles[i] = Triangle(view, image);
    }
}

Model::~Model()
{}

void Model::draw()
{
    Triangle t(view, &image);
    setTrianglePoints(t, 0);
    t.setScale(getScale());
    t.draw(Point(view->getWidth()/2, view->getHeight()/2), 0);
}

double Model::getScale() const
{
    double widthScale = view->getWidth() * 16. / 81 / image.width();
    double heightScale = view->getHeight() * 16. / 81 / image.height();
    return widthScale > heightScale ? heightScale : widthScale;
}

void Model::setTrianglePoints(Triangle& triangle, const int number)
{
    Point a, b, c;
    a.first = 0;
    a.second = 0;
    c.first = 0;
    c.second = image.height() - 1;
    b.first = image.width() - 1;
    b.second = image.height() - 1;

    Point points[3] = {c, a, b};
    triangle.setImageCoordinates(points);
}

void Model::setAngle(const double _angle)
{
    angle = _angle;
}

void Model::invertButton(bool state)
{
    view->invertButton(state);
}
