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
        triangles.push_back(new Triangle(view, &image));
    }
}

Model::~Model()
{
    for(int i = 0; i < 32; i++)
    {
        delete triangles[i];
    }
}


void Model::draw()
{
    for(int i = 0; i < 32; i++)
    {
        setTrianglePoints(*triangles[i], i);
        triangles[i]->setScale(getScale());
    }
    view->clear();
    for(int i = 0; i < 32; i++)
    {
        triangles[i]->draw(getTrianglePosition(*triangles[i], i), angle);
    }
    view->paint();
}

double Model::getScale() const
{
    double widthScale = view->getWidth() * 16. / 24 / image.width();
    double heightScale = view->getHeight() * 16. / 24 / image.height();
    return widthScale > heightScale ? heightScale : widthScale;
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
#define PRINT(a, x) (std::cout << a << " = (" << x.first << ", " << x.second << ")" << std::endl)

Point Model::getTrianglePosition(Triangle& triangle, const int number)
{
    int line = number / 8;
    int position = number - line * 8 + 1;
    bool even = (position % 2 == 0);

    if (!even)
    {
        position--;
        line++;
    }
    Point x;

    x.first = view->getWidth() / 2 + (float)(position / 2 - 2) * (image.width() * getScale() / 4.);
    x.second = view->getHeight() / 2 + (float)(line - 2) * (image.height() * getScale() / 4.);
    return x;
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
    Filter filter = (_filter == 0 ? BILINEAR : NEAREST);
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
