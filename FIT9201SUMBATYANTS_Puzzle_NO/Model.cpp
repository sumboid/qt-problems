#include <QResource>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Model.h"
#include <iostream>

namespace
{
    const int SCALE = 1.;
}


Model::Model(View* _view):
view(_view), image(QImage(":/puzzle.png")), step(0), resized(false)
{
    srand(time(0));
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i] = new Triangle(view, &image);
    }
    init();
}

Model::~Model()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        delete triangles[i];
    }
}

void Model::update()
{
    view->paint();
}

void Model::draw()
{
    calc();
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        triangles[i]->draw(getTrianglePosition(i), getTriangleAngle(i));
    }
}

void Model::calc()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        setTrianglePoints(*triangles[i], i);
        triangles[i]->setScale(getVScale(), getHScale());
    }
}

double Model::getHScale() const
{
    if(resized)
    {
        return (double)view->getWidth() / image.width() * sqrt(16. / 81);
    }
    else
    {
        return SCALE;
    }
}
double Model::getVScale() const
{
    if(resized)
    {
        return (double)view->getHeight() / image.height() * sqrt(16. / 81);
    }
    else
    {
        return SCALE;
    }
}

void Model::resize(int flag)
{
    resized = (flag != 0);
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

    int qw = (image.width() * hscale) / 4. + 0.5;
    int qh = (image.height() * vscale) / 4. + 0.5;
    a.first = view->getWidth() / 2 + (position / 2 * qw - 2 * qw) + 0.5;
    a.second = view->getHeight() / 2 + (line * qh - 2 * qh) + 0.5;
    b.first = a.first + qw + 0.5;
    b.second = a.second + qh + 0.5;
    c.first = even ? b.first : a.first;
    c.second = even ? a.second : b.second;


    int stepHScale = ((view->getWidth() - image.width()) >> 4) % 180;
    int stepVScale = ((view->getHeight() - image.height()) >> 4) % 180;
    double hstep = lastPoints[number].first / 180;
    double vstep = lastPoints[number].second / 180;
    double hshift = (step > 180 ? hstep * (360 - step) : hstep * step);
    double vshift = (step > 180 ? vstep * (360 - step) : vstep * step) + sin(step / 180. * 3.1415);

    c.first += hshift * stepHScale;
    c.second += vshift * stepVScale;
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

#define RANDOM (((rand() % RAND_MAX) / static_cast<double>(RAND_MAX - 1)) * 2 - 1) //[-1 .. 1]

void Model::init()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        angles[i] = (double)(rand() % 720 - 360) / 180 * 3.1415;
        lastPoints[i].first = RANDOM;
        lastPoints[i].second = RANDOM;
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

void Model::getInfo(const int x, const int y)
{
    for(int i = NUMBER_OF_TRIANGLES - 1; i >= 0; --i)
    {
        if(triangles[i]->checkPoint(Point(x, y)))
        {
            view->setBar(triangles[i]->getInfo());
            return;
        }
    }
    view->setBar("");
}
