#include "Line.h"
#include <cstdlib>

#include <iostream>

Line::Line()
{
}
Line::Line(const Point& x, const Point& y): x(x), y(y)
{
    deltaX = abs(x.first - y.first);
    deltaY = abs(y.second - x.second);
    signX = x.first < y.first ? 1 : -1;
    signY = x.second < y.second ? 1 : -1;

    error = deltaX - deltaY;
}

Point Line::next()
{
    int error2 = error * 2;
    if(x.first == y.first && x.second == y.second)
    {
        return y;
    }

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

    return x;
}
