#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <QImage>

#include "View.h"

typedef std::pair<int, int> Point;

class Triangle
{
public:
    Triangle(View *, const QImage&);

    void setImageCoordinates(const Point*);
    void setScale(const double&);
    void draw(const Point x, const double angle);
private:
    void drawLine(const Point x, const Point y);

    struct Coordinates
    {
        Point x[3];
    };

    Coordinates imageCoordinates;
    double scale;

    View* view;
    const QImage& image;
};

#endif // TRIANGLE_H
