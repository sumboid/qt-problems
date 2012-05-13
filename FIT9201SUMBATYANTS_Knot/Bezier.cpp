#include "Bezier.h"
#include "Line.h"

Bezier::Bezier(const Vector* _points)
{
    for(int i = 0; i < 4; i++)
    {
        points[i] = _points[i];
    }
}

Vector Bezier::shift(double* coeff)
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

Vector Bezier::point(double t)
{
    double u = 1 - t;
    double coeff[4] = {u * u * u,
                       u * u * t * 3,
                       u * t * t * 3,
                       t * t * t};
    return shift(coeff);
}

Vector Bezier::gradient(double t)
{
    double coeff[4] = {-3 * t * t + 6 * t -3,
                        9 * t * t - 12 * t + 3,
                        -3 * t * t + 2 * t,
                        3 * t * t};
    return shift(coeff);
}

void Bezier::draw(View* view, const Camera* camera, unsigned int color)
{
    Vector p0(point(0));
    double eps = 0.1;
    for(double t = 0; t < 1; t += eps)
    {
        Vector p1(point(t));
        Line(p0, p1).draw(view, camera, color);
        p0 = p1;
    }
}

