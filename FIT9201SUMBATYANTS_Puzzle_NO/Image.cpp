#include "Image.h"

Image::Image(const char* image): original(QImage(image)), filter(NEAREST)
{}

Image::~Image() {};

void setScale(const double hscale, const double vscale)
{
    bilinear = QImage(original.width() * hscale + 0.5,
                      original.height() * vscale + 0.5,
                      QImage::Format_RGB888);
    nearest = QImage(original.width() * hscale + 0.5,
                      original.height() * vscale + 0.5,
                      QImage::Format_RGB888);

    for(int x = 0; x < nearest.width(); ++x)
    {
        for(int y = 0; y < nearest.height(); ++y)
        {
            unsigned color = original.pixel(x / nearest.width() * original.width() + 0.5,
                                            y / nearest.height() * original.height() + 0.5);
            nearest.setPixel(x, y, color);
        }
    }

    for(int x = 0; x < nearest.width(); ++x)
    {
        for(int y = 0; y < nearest.height(); ++y)
        {

    
}
