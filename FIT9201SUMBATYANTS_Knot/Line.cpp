#include "Line.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Line::Line(const Vector& v1, const Vector& v2)
{
    v[0] = v1;
    v[1] = v2;
}

Line::Line(int x1, int x2, int x3, int x4, int x5, int x6):
alpha(0), length(0)
{
    v[0] = Vector(x1, x2, x3);
    v[1] = Vector(x4, x5, x6);
}

Line::~Line()
{
}

void Line::draw(View* view, const Camera* camera, unsigned int color)
{
    Vector2D first = camera->project(v[0]);
    Vector2D second = camera->project(v[1]);
    
    if(first.z < 0 && second.z < 0)
    {
        return;
    }

    int width = view->getWidth() / 2;
    int height = view->getHeight() / 2;

    if(second.z < 0)
    {
        if(second.z < -0.1)
        {
            alpha = fabs(first.z) / fabs(second.z);
            length = sqrt((first.x[0] - second.x[0]) * (first.x[0] - second.x[0]) + 
                          (first.x[1] - second.x[1]) * (first.x[1] - second.x[1]));
        }
        drawLine(view,
                 first.x[0] + width,
                 first.x[1] + height,
                 second.x[0] + width,
                 second.x[1] + height,
                 color);
    }
    else if(first.z < 0)
    {
        if(first.z < -0.1)
        {
            alpha = fabs(second.z) / fabs(first.z);
            length = sqrt((first.x[0] - second.x[0]) * (first.x[0] - second.x[0]) + 
                          (first.x[1] - second.x[1]) * (first.x[1] - second.x[1]));
        }
        drawLine(view,
                 second.x[0] + width,
                 second.x[1] + height,
                 first.x[0] + width,
                 first.x[1] + height,
                 color);
    }
    else
    {
        drawLine(view,
                 first.x[0] + width,
                 first.x[1] + height,
                 second.x[0] + width,
                 second.x[1] + height,
                 color);
    }
}

void Line::drawLine(View* view, int x0, int y0, int x1, int y1, unsigned int color)
{
    int start[2] = {x0, y0};
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int signX = x0 < x1 ? 1 : -1;
    int signY = y0 < y1 ? 1 : -1;
    int error = dx - dy;

    while(!(x0 == x1 && y0 == y1))
    {
        view->setPixel(x0, y0, color);
        if(fabs(alpha) > 1e-3)
        {
            if(alpha * length / (alpha + 1) < sqrt((start[0] - x0) * (start[0] - x0) + 
                                          (start[1] - y0) * (start[1] - y0)))
            {
                return;
            }
        }
        int error2 = error*2;
        if(error2 > -dy)
        {
            error -= dy;
            x0 += signX;
        }
        if(error2 < dx)
        {
            error += dx;
            y0 += signY;
        }
    }
    view->setPixel(x1, y1, color);
}
