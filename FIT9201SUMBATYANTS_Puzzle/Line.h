#pragma once
#include "Point.h"

class Line
{
public:
    Line();
    Line(const Point& x, const Point& y);
    Point next();

private:
    Point x, y;
    int deltaX, deltaY;
    int signX, signY;
    int error;
};
