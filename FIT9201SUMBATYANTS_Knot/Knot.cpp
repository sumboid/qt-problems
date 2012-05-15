#include "Knot.h"

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
    const int n = initPoints.size();
    for(int i = 1; i < n; i+=3)
    {
        Vector bPoints[4];
        for(int k = 0; k < 4; k++)
        {
            bPoints[k] = workPoints[(i + k) % n];
        }
        Bezier(bPoints).draw(view, camera, color);
    }
}
