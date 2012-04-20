#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <vector>
#include <QImage>

#include "View.h"
#include "Point.h"


class Triangle
{
public:
    Triangle(View *, const QImage&);

    void setImageCoordinates(const Point*);
    void setScale(const double&);
    void draw(const Point x, const double angle);
private:
    a.first = scale * (imagePoints[1].first - imagePoints[0].first) + c.first;
    a.second = scale * (imagePoints[1].second - imagePoints[0].second) + c.second;
    std::vector<Point> getLine(const Point x, const Point y);

    Point imagePoints[3]; /* [c], [a], [b] */
    double scale;

    View* view;
    const QImage& image;
};

#endif // TRIANGLE_H
