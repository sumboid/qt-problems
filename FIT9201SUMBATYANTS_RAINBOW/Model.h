#pragma once
#include <QRgb>
#include "View.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void setSpeed(const int speed);
    void drawPixels() const;

    void setWidth(const int) const;
    void setHeight(const int) const;
    void clear() const;
    void resize();
    void setPhase(const int);
    void invertButton(bool);
private:
    View* view;
    int speed;
    int phase;

    float random() const;
    QRgb HSVtoRGB(const float&, const float&, const float&) const;
};
