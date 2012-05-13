#pragma once
#include "Drawable.h"
#include "Vector.h"

class Line : public Drawable
{
public:
    Line (const Vector& v1, const Vector& v2);
    Line (int, int, int, int, int, int);
    virtual ~Line ();

    virtual void draw(View* view, const Camera* camera, unsigned int color);
private:
    void drawLine(View* view, int x0, int y0, int x1, int y1, unsigned int color);
    Vector v[2];
    double alpha;
    double length;
};
