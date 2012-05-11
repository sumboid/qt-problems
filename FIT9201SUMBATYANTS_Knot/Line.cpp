#include "Line.h"
#include <cstdlib>

Line::Line(const Vector& v1, const Vector& v2)
{
    v[1] = new Vector(v1);
    v[2] = new Vector(v2);
}

Line::~Line()
{
    delete v[1];
    delete v[0];
}

void Line::draw(View* view, const Camera* camera, unsigned int color)
{
    Vector2D first = camera->project(*v[1]);
    Vector2D second = camera->project(*v[2]);

    int width = view->getWidth() / 2;
    int height = view->getHeight() / 2;

    drawLine(view, first.x[0] + width, first.x[1] + height, second.x[0] + width, second.x[1] + height, color);
}

void Line::drawLine(View* view, int x0, int y0, int x1, int y1, unsigned int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int signX = x0 < x1 ? 1 : -1;
    int signY = y0 < y1 ? 1 : -1;
    int error = dx - dy;

    view->setPixel(x1, y1, color);
    while(!(x0 == x1 && y0 == y1))
    {
        view->setPixel(x0, y0, color);
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
}
