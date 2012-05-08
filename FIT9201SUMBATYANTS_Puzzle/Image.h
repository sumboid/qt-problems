#pragma once
#include <QImage>
#include "Filter.h"
class Image {
public:
    Image (const char* image);
    ~Image ();
    void setScale(const double hscale, const double vscale);
    void setFilter(const Filter& filter);
    unsigned int pixel(const int x, const int y) const;
    unsigned int width() const;
    unsigned int height() const;
    unsigned int rwidth() const;
    unsigned int rheight() const;
private:
    QImage original;
    QImage bilinear;
    QImage nearest;

    Filter filter;
};
