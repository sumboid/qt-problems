#include <stdlib.h>
#include <time.h>
#include <limits>
#include <iostream>
#include <math.h>
#include <QMatrix>
#include <QTime>
#include <QRgb>
#include "Model.h"

#include <iostream>

Model::Model(View* _view):
    view(_view), phase(0)
{
    srand(time(NULL));
    speed = view->getSpeed();
}

Model::~Model()
{}

void Model::drawPixels() const
{
    for(int i = 0; i < speed; i++)
    {
        const float nx = random();
        const float ny = random();
        const float blend = nx;

        const float scale[2] = {2.0f, 0.6f};
        QPointF pt((2.0f * nx - 1.0f) * scale[0],
                   (2.0f * ny - 1.0f) * scale[1]); // [-scale, scale]

        const float angle = 25.0f;

        QMatrix mLeft(QMatrix().rotate(-angle));
        QMatrix mRight(QMatrix().rotate(angle));

        pt = (1.0f - blend) * pt * mLeft + blend * pt * mRight;

        const int width = view->getWidth();
        const int height = view->getHeight();

        int px = static_cast<int>(0.5f * (pt.x() + 1.0f) * width + 0.5f);
        int py = static_cast<int>(0.5f * (pt.y() + 1.0f) * height + 0.5f);

        if(0 <= px && px < width && 0 <= py && py < height)
        {
            view->setPixel(px, py, HSVtoRGB(ny * 360 + phase, 1.f, 1.f));
        }
    }
    view->paint();
}

QRgb Model::HSVtoRGB(const float& h, const float& s, const float& v) const
{
    int magic = static_cast<int>(h / 60) % 6;
    float f = h / 60 - static_cast<int>(h / 60);
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch(magic)
    {
        default:
        case 0: return qRgb(static_cast<quint8>(v * 255),
                            static_cast<quint8>(t * 255),
                            static_cast<quint8>(p * 255));

        case 1: return qRgb(static_cast<quint8>(q * 255),
                            static_cast<quint8>(v * 255),
                            static_cast<quint8>(p * 255));

        case 2: return qRgb(static_cast<quint8>(p * 255),
                            static_cast<quint8>(v * 255),
                            static_cast<quint8>(t * 255));

        case 3: return qRgb(static_cast<quint8>(p * 255),
                            static_cast<quint8>(q * 255),
                            static_cast<quint8>(v * 255));

        case 4: return qRgb(static_cast<quint8>(t * 255),
                            static_cast<quint8>(p * 255),
                            static_cast<quint8>(v * 255));

        case 5: return qRgb(static_cast<quint8>(v * 255),
                            static_cast<quint8>(p * 255),
                            static_cast<quint8>(q * 255));
    }
}

void Model::clear() const
{
    view->clear();
}

void Model::setWidth(const int _width) const
{
    view->setWindowWidth(_width);
}

void Model::setHeight(const int _height) const
{
    view->setWindowHeight(_height);
}

void Model::setSpeed(const int _speed)
{
    speed = _speed;
}

float Model::random() const
{
    return (rand() % RAND_MAX) / static_cast<float>(RAND_MAX - 1);
}

void Model::resize()
{
    view->setWidthSpin(view->getWindowWidth());
    view->setHeightSpin(view->getWindowHeight());
}

void Model::setPhase(const int _phase)
{
    phase = _phase;
}

void Model::invertButton(bool state)
{
   view->invertButton(state);
}
