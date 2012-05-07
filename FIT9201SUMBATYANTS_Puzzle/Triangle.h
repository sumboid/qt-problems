#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <vector>


#include "Image.h"
#include "View.h"
#include "Point.h"

class Triangle
{
public:
    Triangle(View *, const Image *);

    void setImageCoordinates(const Point*);
    void draw(const Point& x, const double angle);
    void setBlend(const bool);
    bool checkPoint(const Point& point) const;
    const char* getInfo() const;
private:
    unsigned int getColor(const Point& x);
    void setPoints(const Point& x, const double _angle);

    Point imagePoints[3]; /* [c], [a], [b] */
    Point points[3]; /* [c], [a], [b] */
    bool blend;
    int allPixels;
    int transparentPixels;
    int borderPixels;


    View* view;
    const Image* image;
};

#endif // TRIANGLE_H
