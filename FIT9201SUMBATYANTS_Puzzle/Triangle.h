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
    bool checkPoint(const Point& point) const;
    const char* getInfo() const;
private:
    unsigned int getColor(const Point& x);

    Point imagePoints[3]; /* [c], [a], [b] */
    Point points[3]; /* [c], [a], [b] */
    double vScale;
    double hScale;
    Filter filter;
    bool blend;
    int allPixels;
    int transparentPixels;
    int borderPixels;


    View* view;
    const QImage* image;
};

#endif // TRIANGLE_H
