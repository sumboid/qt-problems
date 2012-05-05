#include <QPixmap>
#include <QResource>
#include <math.h>
#include <stdlib.h>
#include "Model.h"

#include <iostream>

namespace
{
    const int NUMBER_OF_TRIANGLES = 32;
}

Model::Model(View* _view):
view(_view), angle(0), image(QImage(":/puzzle.png"))
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles.push_back(new Triangle(view, &image));
    }
}

Model::~Model()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        delete triangles[i];
    }
}


void Model::draw()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        setTrianglePoints(*triangles[i], i);
        triangles[i]->setScale(getVScale(), getHScale());
    }
    view->clear();
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i]->draw(getTrianglePosition(*triangles[i], i), angle);
    }
    view->paint();
}

double Model::getHScale() const
{
    return view->getWidth() * 16. / 81 / image.width();
}
double Model::getVScale() const
{
    return view->getHeight() * 16. / 81 / image.height();
}

#define max(x, y) (x > y ? x : y)

void Model::setTrianglePoints(Triangle& triangle, const int number)
{
    Point a, b, c;
    int line = number >> 3;
    int position = number % 8;
    bool even = position & 1;

    int qw = image.width() / 4;
    int qh = image.height() / 4;
    a.first = max(0, position / 2 * qw - 1);
    a.second = max(0, line * qh - 1);
    b.first = a.first + qw;
    b.second = a.second + qh;
    c.first = even ? b.first : a.first;
    c.second = even ? a.second : b.second;

    Point pointsOdd[3] = {c, a, b};
    Point pointsEven[3] = {c, b, a};
    triangle.setImageCoordinates(even ? pointsEven : pointsOdd);
}

Point Model::getTrianglePosition(Triangle& triangle, const int number)
{
    Point a, b, c;
    int line = number >> 3;
    int position = number % 8;
    bool even = position & 1;

    int qw = image.width() / 4;
    int qh = image.height() / 4;
    a.first = max(0, view->getWidth() / 2 + (position / 2 * qw - 1 - 2*qw) * getHScale() + 0.5);
    a.second = max(0, view->getHeight() / 2 + (line * qh - 1 - 2*qh) * getVScale() + 0.5);
    b.first = a.first + qw * getHScale() + 0.5;
    b.second = a.second + qh * getVScale() + 0.5;
    c.first = even ? b.first : a.first;
    c.second = even ? a.second : b.second;

    return c;
}

void Model::setAngle(const double _angle)
{
    angle = _angle;
}

void Model::init()
{
}

void Model::setFilter(const int _filter)
{
    Filter filter = (_filter != 0 ? BILINEAR : NEAREST);
    for(int i = 0; i < 32; i++)
    {
        triangles[i]->setFilter(filter);
    }
}

void Model::setBlend(const int blend)
{
    for(int i = 0; i < 32; i++)
    {
        triangles[i]->setBlend(blend != 0);
    }
}

void Model::invertButton(bool state)
{
    view->invertButton(state);
}
