#include <iostream>
#include <math.h>
#include "ModelSin.h"

namespace
{
    const unsigned int WHITE = 0xffffff;
    const unsigned int GRAY = 0x999999;
}

ModelSin::ModelSin(View* _view): view(_view)
{
    func = false;
    axis = false;
}

ModelSin::~ModelSin()
{}

void ModelSin::drawFunction()
{
    int width = view->getWidth();
    int height = view->getHeight();
    double horisontalShift = width / 2.;
    double dotsPerInterval = height / 3.;
    double verticalShift = height / 2.;

    if(static_cast<int>(1. / dotsPerInterval) >= 0 && height > 2)
    {
        for(int i = 0; i < width; i++)
        {
            view->setPixel(i,
                           static_cast<int>(-sin((i - horisontalShift) / dotsPerInterval) *
                                 dotsPerInterval + verticalShift + 0.5),
                           WHITE);
        }
    }
}

void ModelSin::drawAxis()
{
    int width = view->getWidth();
    int height = view->getHeight();
    int dotsPerInterval = height / 3;

    if(static_cast<int>(1. / dotsPerInterval) >= 0 && height > 2)
    {
        for(int i = 0; i < height; i++)
        {
            if((i - height / 2) % dotsPerInterval == 0)
            {
                for(int k = width/2 - height/100; k != width/2 + height/100; k++)
                {
                    view->setPixel(k, i, GRAY);
                }
            }
            view->setPixel(width/2, i, GRAY);
        }

        for(int i = 0; i < width; i++)
        {
            if((i - width / 2) % dotsPerInterval == 0)
            {
                for(int k = height/2 - height/100; k != height/2 + height/100; k++)
                {
                    view->setPixel(i, k, GRAY);
                }
            }
            view->setPixel(i, height/2, GRAY);
        }
    }
}

void ModelSin::setFunction()
{
    func = true;
}

void ModelSin::setAxis()
{
    axis = true;
}

void ModelSin::clear()
{
    axis = false;
    func = false;
}

void ModelSin::update()
{
    if(axis)
    {
        drawAxis();
    }
    if(func)
    {
        drawFunction();
    }
    view->paint();
}
