#pragma once
#include "Vector.h"

class Camera
{
public:
    Camera ();
    Camera (const Vector& center, const double* orientation);
    ~Camera ();
    void rotate(const double*);
    void translate(double coef);
    Vector2D project(const Vector& v) const;
    void scale(const double*);
    void reset();
    double getScale() const;

private:
    Vector* center;
    double orientation[3];
    double scaleCoef[3];
    const double speed;
    const int z;
};
