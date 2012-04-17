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

void Triangle::drawLine(const Point x, const Point y)
{
}

void Triangle::draw(const Point x, const double angle)
{

    return;
}
