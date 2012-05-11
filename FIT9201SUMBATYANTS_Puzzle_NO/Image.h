#pragma once
#include <QImage>
#include "Filter.h"
class Image {
public:
    Image (const char* image);
    ~Image ();
    void setScale(const double hscale, const double vscale);
    void setFilter(const Filter& filter);
    void getPixel(const double u, const double v, const Point& c, const Point& a, const Point& b);
private:
    QImage original;
    Qimage bilinear;
    QImage nearest;

    Filter filter;
};
