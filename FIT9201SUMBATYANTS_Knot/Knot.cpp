#include "Knot.h"
#include <iostream>

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
    }
}

double* Knot::getBounds() const
{
    double* result = new double[6];
/*
    result[0] = workPoints[0].getX();
    result[1] = workPoints[0].getY();
    result[2] = workPoints[0].getZ();
    result[3] = workPoints[0].getX();
    result[4] = workPoints[0].getY();
    result[5] = workPoints[0].getZ();
*/
    for(int k = 0; k < 6; k++)
    {
        result[k] = bounds[k];
        std::cout << result[k] << " ";
        /*
        if(workPoints[k].getX() < result[0]) result[0] = workPoints[k].getX();
        if(workPoints[k].getY() < result[1]) result[1] = workPoints[k].getY();
        if(workPoints[k].getZ() < result[2]) result[2] = workPoints[k].getZ();
        if(workPoints[k].getX() > result[3]) result[3] = workPoints[k].getX();
        if(workPoints[k].getY() > result[4]) result[4] = workPoints[k].getY();
        if(workPoints[k].getZ() > result[5]) result[5] = workPoints[k].getZ();
        */
    }
    std::cout << std::endl << "-------" << std::endl;
    return result;
}
