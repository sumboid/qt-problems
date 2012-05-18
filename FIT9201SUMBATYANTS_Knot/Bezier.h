#pragma once
#include "Drawable.h"
#include "Curve.h"

class Bezier : public Drawable, public Curve
{
public:
    Bezier (const Vector*);
    double* getBounds() const;
    virtual Vector point(double) const;
    virtual void draw(View* view, const Camera* camera, unsigned int color);

private:
    void checkBounds();
    Vector shift(double*) const;

    Vector points[4];
    double bounds[6];
};
