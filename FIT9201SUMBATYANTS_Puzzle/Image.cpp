#include "Image.h"
#include <QRgb>
#include <iostream>

Image::Image(const char* image): original(QImage(image)), filter(NEAREST)
{
    setScale(1, 1);
}


Image::~Image() {};

void Image::setScale(const double hscale, const double vscale)
{
    bilinear = QImage(original.width() * hscale + 0.5,
                      original.height() * vscale + 0.5,
                      original.format());
    nearest = QImage(original.width() * hscale + 0.5,
                     original.height() * vscale + 0.5,
                     original.format());

    for(int x = 0; x < nearest.width(); ++x)
    {
        for(int y = 0; y < nearest.height(); ++y)
        {
            unsigned color = original.pixel((double)x / nearest.width() * original.width(),
                                            (double)y / nearest.height() * original.height());
            nearest.setPixel(x, y, color);
        }
    }

    for(int x = 0; x < bilinear.width(); ++x)
    {
        for(int y = 0; y < bilinear.height(); ++y)
        {
            double rx = (double)x / (bilinear.width() - 1) * (original.width() - 1);
            double ry = (double)y / (bilinear.height() - 1) * (original.height() - 1);
            int ix = rx;
            int iy = ry;
            if (ix > original.width() - 2)
            {
                ix = original.width() - 2;
            }
            if (iy > original.height() - 2)
            {
                iy = original.height() - 2;
            }

            double dx = rx - ix;
            double dy = ry - iy;

            double d[] = { (1 - dy) * (1 - dx), dy * (1 - dx), dy * dx, (1 - dy) * dx };
            int p[] = { original.pixel(ix, iy),
                        original.pixel(ix, iy + 1),
                        original.pixel(ix + 1, iy + 1),
                        original.pixel(ix + 1, iy)};

            double rgba[] = {0, 0, 0, 0};
            for (int j = 0; j < 4; j++) 
            {
                rgba[0] += qRed(p[j]) * d[j];
                rgba[1] += qGreen(p[j]) * d[j];
                rgba[2] += qBlue(p[j]) * d[j];
                rgba[3] += qAlpha(p[j]) * d[j];
            }
            unsigned int color = qRgba(rgba[0], rgba[1], rgba[2], rgba[3]);

            bilinear.setPixel(x, y, color);
        }
    }
}

void Image::setFilter(const Filter& _filter)
{
    filter = _filter;
}

unsigned int Image::pixel(const int x, const int y) const
{
    if(filter == BILINEAR)
    {
        return bilinear.pixel(x, y);
    }
    else if(filter == NEAREST)
    {
        return nearest.pixel(x, y);
    }
    else
    {
        return 0x0;
    }
}

unsigned int Image::width() const
{
    return nearest.width();
}

unsigned int Image::height() const
{
    return nearest.height();
}
unsigned int Image::rwidth() const
{
    return original.width();
}

unsigned int Image::rheight() const
{
    return original.height();
}
