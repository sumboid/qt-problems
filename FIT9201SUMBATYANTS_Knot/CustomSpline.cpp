#include "CustomSpline.h"
#include "CurveRender.h"

CustomSpline::CustomSpline(double* start, double* end)
{
    shift = Vector(start[0], start[1], start[2]);
    for(int i = 0; i < 3; i++)
    {
        scale[i] = end[i] / (100 - start[i]);
    }
}

Vector CustomSpline::point(double t) const
{
    Vector rv;
    if(t - 1 < 0.00001)
    {
        rv = P1::point(t);
    }
    else
    {
        rv = P2::point(t);
    }

    rv.add(shift);
    return rv;
}

void CustomSpline::draw(View* view, const Camera* camera, unsigned int color)
{
    CurveRender(this, 1).draw(view, camera, color);
}
