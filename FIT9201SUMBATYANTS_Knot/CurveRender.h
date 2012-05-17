#pragma once
#include "Drawable.h"
#include "Curve.h"

class CurveRender
{
public:
    CurveRender(const Curve* curve, double);
    void draw(View*, const Camera*, unsigned int color);
private:
    const Curve* curve;
    double bound;
};
