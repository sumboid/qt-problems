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
    view->clear();
    t.draw(Point(view->getWidth()/2, view->getHeight()/2), angle);
    view->paint();
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
    int line = number / 8;
    int position = number - line * 8;
    bool odd = (position % 2 == 1);

    if(!odd)
    {
        a.first = position * ((image.width() - 1) / 4);
        a.second = line * ((image.height() - 1) / 4);
        b.first = (position + 1) * ((image.width() - 1) / 4);
        b.second = (line + 1) * ((image.height() - 1) / 4);
        c.first = a.first;
        c.second = b.second; 
    }
    else
    {
        a.first = (position + 1) * ((image.width() - 1) / 4);
        a.second = (line + 1) * ((image.height() - 1) / 4);
        b.first = position * ((image.width() - 1) / 4);
        b.second = line * ((image.width() - 1) / 4);
        c.first = b.first;
        c.second = a.second;
    }

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
