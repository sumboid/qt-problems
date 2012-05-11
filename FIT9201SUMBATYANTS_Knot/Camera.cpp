#include "Camera.h"

Camera::Camera ():
center(new Vector(0, 0, 0, 1)), speed(0.1), z(-500)
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = 0;
        scaleCoef[i] = 10.;
    }
}

Camera::~Camera()
{
    delete center;
}

Camera::Camera (const Vector& _center, const double* _orientation):
center(new Vector(_center)), speed(0.1), z(-500)
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = -_orientation[i];
        scaleCoef[i] = 10.;
    }
}


void Camera::rotate(const double* rotateCoef)
{
    for(int i = 0; i < 3; i++)
    {
       orientation[i] -= rotateCoef[i];
    }
}

void Camera::translate(double coef)
{
    Vector v(0, 0, z, 1);
    v.normalize();
    v.rotate(orientation);
    v.multiply(coef * speed);
    center->translate(v);
}

Vector2D Camera::project(const Vector& _v) const
{
    Vector v(_v);
    v.subtract(*center);
    v.rotate(orientation);
    v.scale(scaleCoef);
    return v.project(z);
}

void Camera::scale(const double* _scaleCoef)
{
    for(int i = 0; i < 3; i++)
    {
        scaleCoef[i] += _scaleCoef[i];
    }
}
