#include "Bezier.h"
#include "Line.h"
#include "CurveRender.h"
#include <cstdlib>
#include <iostream>

Bezier::Bezier(const Vector* _points)
{
    for(int i = 0; i < 4; i++)
    {
        points[i] = _points[i];
    }
    checkBounds();
}

Vector Bezier::shift(double* coeff) const
{
    Vector v(0, 0, 0);
    for(int i = 0; i < 4; i++)
    {
        Vector u(points[i]);
        u.multiply(coeff[i]);
        v.translate(u);
    }

    return v;
}

Vector Bezier::point(double t) const
{
    double u = 1 - t;
    double coeff[4] = {u * u * u,
                       u * u * t * 3,
                       u * t * t * 3,
                       t * t * t};
    return shift(coeff);
}

void Bezier::checkBounds()
{
    Vector firstPoint3D = point(0);
    bounds[0] = firstPoint3D.getX();
    bounds[1] = firstPoint3D.getY();
    bounds[2] = firstPoint3D.getZ();
    bounds[3] = firstPoint3D.getX();
    bounds[4] = firstPoint3D.getY();
    bounds[5] = firstPoint3D.getZ();

    for(double eps = 0; eps <= 1; eps+=0.001)
    {
        Vector p(point(eps));
        double lx = p.getX();
        double ly = p.getY();
        double lz = p.getZ();
        if(lx < bounds[0]) bounds[0] = lx;
        if(ly < bounds[1]) bounds[1] = ly;
        if(lz < bounds[2]) bounds[2] = lz;
        if(lx > bounds[3]) bounds[3] = lx;
        if(ly > bounds[4]) bounds[4] = ly;
        if(lz > bounds[5]) bounds[5] = lz;
    }
}

void Bezier::draw(View* view, const Camera* camera, unsigned int color)
{
    CurveRender(this, 1+0.001).draw(view, camera, color);
}

double* Bezier::getBounds() const
{
    double* result = new double[6];
    for(int i = 0; i < 6; i++)
    {
        result[i] = bounds[i];
    }

    return result;
}
