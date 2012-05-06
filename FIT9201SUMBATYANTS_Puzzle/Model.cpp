#include <QPixmap>
#include <QResource>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Model.h"

#include <iostream>

Model::Model(View* _view):
view(_view), step(0), image(QImage(":/puzzle.png"))
{
    init();
    srand(time(0));
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i] = new Triangle(view, &image);
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
        triangles[i]->draw(getTrianglePosition(i), getTriangleAngle(i));
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

Point Model::getTrianglePosition(const int number)
{
    Point a, b, c;
    int line = number >> 3;
    int position = number % 8;
    bool even = position & 1;
    double hscale = getHScale();
    double vscale = getVScale();

    int qw = image.width() / 4;
    int qh = image.height() / 4;
    a.first = view->getWidth() / 2 + (position / 2 * qw - 2 * qw) * hscale + 0.5;
    a.second = view->getHeight() / 2 + (line * qh - 2 * qh) * vscale + 0.5;
    b.first = a.first + qw * hscale + 0.5;
    b.second = a.second + qh * vscale + 0.5;
    c.first = even ? b.first : a.first;
    c.second = even ? a.second : b.second;

    double hstep = lastPoints[number].first / 180.;
    double vstep = lastPoints[number].second / 180.;
    int hshift = (step > 180 ? hstep * (360 - step) : hstep * step) + 5*sin(step / 180 * 3.1415);
    int vshift = (step > 180 ? vstep * (360 - step) : vstep * step) + 5*sin(step / 180 * 3.1415);

    if (hscale <= 1.)
        hshift *= hscale;
    if (vscale <= 1.)
        vshift *= vscale;

    c.first += hshift;
    c.second += vshift;
    return c;
}

double Model::getTriangleAngle(const int number)
{
    double part = angles[number] / 180;
    return part * (step > 180 ? 360 - step : step);
}

void Model::setStep(const int _step)
{
    view->setDial(_step);
    step = _step;
}


void Model::init()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        angles[i] = (double)(rand() % 180) / 180 * 3.1415;
        lastPoints[i].first = (rand() % 360 - 180);
        lastPoints[i].second = (rand() % 360 - 180);
    }
}

void Model::setFilter(const int _filter)
{
    Filter filter = (_filter != 0 ? BILINEAR : NEAREST);
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i]->setFilter(filter);
    }
}

void Model::setBlend(const int blend)
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i]->setBlend(blend != 0);
    }
}

void Model::invertButton(bool state)
{
    view->invertButton(state);
}
