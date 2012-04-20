#include "Mapper.h"

Mapper::Mapper(const Point* _realPoints,
               const QImage& _image):
image(_image)
{
    for(int i = 0; i < 3; i++)
    {
        realPoints[i].first = _realPoints[i].first;
        realPoints[i].second = _realPoints[i].second;
    }
}

void Mapper::setPoints(const Point* _points)
{
    for(int i = 0; i < 3; i++)
    {
        points[i].first = _points[i].first;
        points[i].second = _points[i].second;
    }

    //Move triangle to (0, 0)

    for(int i = 0; i < 3; i++)
    {
        points[i].first -= points[0].first;
        points[i].second -= points[0].second;
    }
}

void Mapper::setScale(const double _scale)
{
    scale = _scale;
}

void Mapper::setFilter(const Filter type)
{
    filter = type;
}

unsigned int getColor(const Point& point)
{
    
    return 0;
}
