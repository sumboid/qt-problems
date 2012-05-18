#pragma once

#include "Drawable.h"
#include "Vector.h"
#include "Curve.h"


class CustomSpline : public Drawable, public Curve 
{
public:
    CustomSpline (double* start, double* end);
    virtual Vector point(double t) const;
    virtual void draw(View*, const Camera*, unsigned int color);
private:
    Vector shift;
    double scale[3];

    class P1
    {
    public:
        static Vector point(double t)
        {
            double x =  t * t * t * t * t +
                        2 * t * t * t * t +
                       -3 * t * t * t +
                       -4 * t * t +
                       5 * t;
            double y = -6 * t * t * t * t +
                        5 * t * t * t +
                       -3 * t * t +
                        2 * t;
            double z =  2 * t * t * t +
                       -2 * t * t +
                       -t;

            return Vector(x, y, z);
        }
    };

    class P2
    {
    public:
        static Vector point(double t)
        {
            double x = 9 * t * t * t - 18 * t * t + 9 * t;
            double y = 2 * t * t * t + 7 * t * t - 11 * t;
            double z = 2 * t * t * t - 2 * t * t - t;

            return Vector(x, y, z);
        }
    };
};
