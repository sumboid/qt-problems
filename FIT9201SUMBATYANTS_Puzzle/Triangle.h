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
    Triangle(View *, const QImage *);

    void setImageCoordinates(const Point*);
    void setScale(const double&, const double&);
    void draw(const Point& x, const double angle);
    void setFilter(const Filter& filter);
    void setBlend(const bool);
private:
    unsigned int getColor(const Point& x) const;

    Point imagePoints[3]; /* [c], [a], [b] */
    Point points[3]; /* [c], [a], [b] */
    double vScale;
    double hScale;
    Filter filter;
    bool blend;


    View* view;
    const QImage* image;
};

#endif // TRIANGLE_H
