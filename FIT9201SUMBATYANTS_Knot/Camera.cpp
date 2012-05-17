#include "Camera.h"
#include <cstdlib>

Camera::Camera():
center(new Vector(0, 0, -5)), speed(1), z(-1000)
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = 0;
        scaleCoef[i] = 1.;
    }
}

Camera::~Camera()
{
    delete center;
}

Camera::Camera (const Vector& _center, const double* _orientation):
center(new Vector(_center)), speed(0.1), z(-100)
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = +_orientation[i];
        scaleCoef[i] = 30.;
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
    center->translate(v);
}

Vector2D Camera::project(const Vector& _v) const
{
    Vector v(_v);
    v.rotate(orientation);
    v.subtract(*center);
    return v.project(z);
}

void Camera::scale(const double* _scaleCoef)
{
    for(int i = 0; i < 3; i++)
    {
        scaleCoef[i] += _scaleCoef[i];
    }
}

void Camera::reset()
{
    for(int i = 0; i < 3; i++)
    {
        orientation[i] = 0;
        scaleCoef[i] = 1;
    }
    delete center;
    center = new Vector(0, 0, 0);
}

double Camera::getScale() const
{
    return scaleCoef[0];
}
