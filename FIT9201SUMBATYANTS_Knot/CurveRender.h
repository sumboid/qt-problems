#pragma once
#include "Drawable.h"
#include "Curve.h"

class CurveRender : public Drawable 
{
public:
    CurveRender(const Curve* curve, double);
    virtual void draw(View*, const Camera*, unsigned int color);
private:
    const Curve* curve;
    double bound;
};
