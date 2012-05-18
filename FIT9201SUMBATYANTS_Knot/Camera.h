#pragma once
#include "Vector.h"

class Camera
{
public:
    Camera ();
    Camera (const Vector& center, const double* orientation);
    void rotate(const double*);
    void translate(double coef);
    Vector2D project(const Vector& v) const;
    void reset();
    void setCenter(const Vector&);

private:
    Vector center;
    double orientation[3];
    const double speed;
    const int z;
    Vector pseudoCenter;
};
