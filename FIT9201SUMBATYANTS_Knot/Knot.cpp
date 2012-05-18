#include "Knot.h"
#include <iostream>

namespace
{
    const int SCALE = 50;
}

Knot::Knot(double points[6][3], int n)
{
    for(int i = 0; i < n; i++)
    {
        initPoints.push_back(Vector(points[i][0], points[i][1], points[i][2]));
    }

    generatePoints();
}

void Knot::generatePoints()
{
    const int n = initPoints.size();

    for(int i = 0; i < n; i++)
    {
        Vector ip0 = initPoints[(i + n - 1) % n];
        Vector wp0 = initPoints[i];
        Vector ip2 = initPoints[(i + 1) % n];

        Vector tmp(ip2);
        tmp.subtract(ip0);
        tmp.normalize();
        tmp.multiply(SCALE);
        Vector wp1(wp0);
        wp1.subtract(tmp);
        Vector wp2(wp0);
        wp2.add(tmp);

        workPoints.push_back(Vector(wp1));
        workPoints.push_back(Vector(wp0));
        workPoints.push_back(Vector(wp2));
    }
}


void Knot::draw(View* view, const Camera* camera, unsigned int color)
{
    const int n = workPoints.size();
    for(int i = 1; i < n; i+=3)
    {
        Vector bPoints[4];
        for(int k = 0; k < 4; k++)
        {
            bPoints[k] = workPoints[(i + k) % n];
        }
        Bezier bezier(bPoints);
        bezier.draw(view, camera, color);
    }
}

double* Knot::getBounds()
{
    const int n = workPoints.size();
    for(int i = 1; i < n; i+=3)
    {
        Vector bPoints[4];
        for(int k = 0; k < 4; k++)
        {
            bPoints[k] = workPoints[(i + k) % n];
        }
        Bezier bezier(bPoints);
        double* newBounds = bezier.getBounds();

        if(i == 1)
        {
            for(int i = 0; i < 6; i++)
            {
                bounds[i] = newBounds[i];
            }
        }
        else
        {
            for(int i = 0; i < 3; i++)
            {
                if(newBounds[i] < bounds[i]) bounds[i] = newBounds[i];
            }
            for(int i = 3; i < 6; i++)
            {
                if(newBounds[i] > bounds[i]) bounds[i] = newBounds[i];
            }
        }
        delete newBounds;
    }

    double* result = new double[6];
    for(int k = 0; k < 6; k++)
    {
        result[k] = bounds[k];
    }

    return result;
}
