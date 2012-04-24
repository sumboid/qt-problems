#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <vector>
#include <QImage>

#include "View.h"
#include "Point.h"
#include "Filter.h"


class Triangle
{
public:
    Triangle(View *, const QImage&);

    void setImageCoordinates(const Point*);
    void setScale(const double&);
    void draw(const Point x, const double angle);
private:
    std::vector<Point> getLine(const Point& x, const Point& y) const;
    unsigned int getColor(const Point& x) const;

    Point imagePoints[3]; /* [c], [a], [b] */
    Point points[3]; /* [c], [a], [b] */
    double scale;
    Filter filter;


    View* view;
    const QImage& image;
};

#endif // TRIANGLE_H
