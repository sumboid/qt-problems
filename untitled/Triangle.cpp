#include <cmath>
#include "Triangle.h"

Triangle::Triangle(View* _view, const QImage& _image):
    scale(0), view(_view), image(_image)
{
    for(int i = 0; i < 3; ++i)
    {
        imageCoordinates.x[i] = Point(0, 0);
    }
}

void Triangle::setImageCoordinates(const Point* coordinates)
{
    for(int i = 0; i < 3; ++i)
    {
        imageCoordinates.x[i].first = coordinates[i].first;
        imageCoordinates.x[i].second = coordinates[i].second;
    }
}

void Triangle::setScale(const double& _scale)
{
    scale = _scale;
}

std::vector<Point> Triangle::drawLine(const Point _x, const Point _y)
{
    Point x = _x;
    Point y = _y;
    std::vector<Point> line;
    const int deltaX = abs(x.first - y.first);
    const int deltaY = abs(y.second - x.second);
    const int signX = x.first < y.first ? 1 : -1;
    const int signY = x.second < y.second ? 1 : -1;

    int error = deltaX - deltaY;
    setPixel(y.first, y.second);
    while(x.first != y.first || x.second != y.second)
    {
        line.insert(Point(x.first, x.second));
        const int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x.first += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            x.second += signY;
        }
    }

    return line;
}


void Triangle::draw(const Point x, const double angle)
{
    /* Hurdcoar
     *
     *  [a]
     *   |\
     *   | \
     *   |  \
     *   |   \
     *  [c]--[b]
     *
     */

    Point a, b, c = x;

    return;
}
