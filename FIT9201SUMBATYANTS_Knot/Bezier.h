#pragma once
#include "Drawable.h"

class Bezier : public Drawable {
public:
    Bezier (const Vector*);
    Vector shift(double*);
    Vector point(double);
    Vector gradient(double);

    virtual void draw(View* view, const Camera* camera, unsigned int color);

private:
    Vector points[4];
};
