#pragma once
#include <QRgb>
#include "View.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void setSpeed(const int speed);
    void draw() const;
    void setAngle(const double);
    void invertButton(bool);
private:
    View* view;
    double angle;
};
