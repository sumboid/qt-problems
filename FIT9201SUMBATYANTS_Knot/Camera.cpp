#include "Camera.h"
#include <cstdlib>

Camera::Camera():
center(Vector(0, 0, -5)), pseudoCenter(Vector(0, 0, 0)), speed(1), z(-500)
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = 0;
    }
}

void Camera::rotate(const double* rotateCoef)
{
    for(int i = 0; i < 3; i++)
    {
       orientation[i] += rotateCoef[i];
    }
}

void Camera::translate(double coef)
{
    Vector v(0, 0, -z);
    v.normalize();
    v.multiply(coef * speed);
    center.translate(v);
}

Vector2D Camera::project(const Vector& _v) const
{
    Vector v(_v);
    v.subtract(pseudoCenter);
    v.rotate(orientation);
    v.add(pseudoCenter);
    v.subtract(center);
    return v.project(z);
}

void Camera::reset()
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = 0;
    }
    center = Vector(0, 0, -5);
}

void Camera::setCenter(const Vector& v)
{
    pseudoCenter = v;
}
