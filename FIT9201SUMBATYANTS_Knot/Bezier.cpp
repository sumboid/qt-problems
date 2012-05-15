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

void Bezier::draw(View* view, const Camera* camera, unsigned int color)
{
    int width = view->getWidth() / 2;
    int height = view->getHeight() / 2;
    double eps = 1;
    double right = 1;
    double left = 0;
    bool end;

    Vector firstPoint3D = point(0);
    Vector2D firstPoint = camera->project(firstPoint3D);
    if(firstPoint.z > 0)
    {
        //init
        bounds[0] = firstPoint3D.getX();
        bounds[1] = firstPoint3D.getY();
        bounds[2] = firstPoint3D.getZ();
        bounds[3] = firstPoint3D.getX();
        bounds[4] = firstPoint3D.getY();
        bounds[5] = firstPoint3D.getZ();
        view->setPixel(firstPoint.x[0] + width, firstPoint.x[1] + height, color);
    }

    while(true)
    {
        Vector2D tmpVector = camera->project(point(right));
        Vector rv(point(left));
        Vector2D point = camera->project(rv);

        if(abs(tmpVector.x[0] - point.x[0]) > 1 ||
           abs(tmpVector.x[1] - point.x[1]) > 1 )
        {
            if(right - left < 0.00001)
            {
                break;
            }
            eps = left + (right - left) / 2;
            right = eps;
            end = false;
            continue;
        }

        if(end) break;
        end = true;
        left = eps;
        right = 1;
        if(point.z > 0)
        {
            double lx = firstPoint3D.getX();
            double ly = firstPoint3D.getY();
            double lz = firstPoint3D.getZ();
            if(lx > bounds[3]) bounds[3] = lx;
            if(lx < bounds[0]) bounds[0] = lx;
            if(ly > bounds[4]) bounds[4] = ly;
            if(ly < bounds[1]) bounds[1] = ly;
            if(lz > bounds[5]) bounds[5] = lz;
            if(lz < bounds[2]) bounds[2] = lz;

            view->setPixel(point.x[0] + width, point.x[1] + height, color);
        }
    }
    Vector lastPoint3D = point(1);
    Vector2D lastPoint = camera->project(lastPoint3D);
    if(lastPoint.z > 0)
    {
        double lx = lastPoint3D.getX();
        double ly = lastPoint3D.getY();
        double lz = lastPoint3D.getZ();
        if(lx > bounds[3]) bounds[3] = lx;
        if(lx < bounds[0]) bounds[0] = lx;
        if(ly > bounds[4]) bounds[4] = ly;
        if(ly < bounds[1]) bounds[1] = ly;
        if(lz > bounds[5]) bounds[5] = lz;
        if(lz < bounds[2]) bounds[2] = lz;

        view->setPixel(lastPoint.x[0] + width, lastPoint.x[1] + height, color);
    }
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
