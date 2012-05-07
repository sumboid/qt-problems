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
private:
    unsigned int getColor(const Point& x);

    Point imagePoints[3]; /* [c], [a], [b] */
    Point points[3]; /* [c], [a], [b] */
    bool blend;
    int allPixels;
    int opacityPixels;


    View* view;
    const Image* image;
};

#endif // TRIANGLE_H
