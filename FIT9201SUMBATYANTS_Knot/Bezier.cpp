#include "Bezier.h"
#include "Line.h"
#include <cstdlib>
#include <iostream>

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
    double coeff[4] = {-3 * t * t + 6 * t - 3,
                        9 * t * t - 12 * t + 3,
                       -3 * t * t + 2 * t,
                        3 * t * t};
    return shift(coeff);
}

void Bezier::draw(View* view, const Camera* camera, unsigned int color)
{
    int width = view->getWidth() / 2;
    int height = view->getHeight() / 2;
    double eps = 1;
    double right = 1;
    double left = 0;
    while(true)
    {
        Vector2D tmpVector = camera->project(point(right));
        Vector rv(point(left));
        Vector2D point = camera->project(rv);

        if(abs(tmpVector.x[0] - point.x[0]) - 1 > 0.000001 &&
           abs(tmpVector.x[1] - point.x[1]) - 1 > 0.000001 )
        {
            eps = left + (right - left) / 2;
        std::cout << eps << std::endl;
            right = eps;
            if(1 - right < 0.01)
            {
                break;
            }
            continue;
        }

        left = eps;
        right = 1;
        if(point.z > 0)
        {
            view->setPixel(point.x[0] + width, point.x[1] + height, color);
        }
        std::cout << eps << std::endl;
    }
}
