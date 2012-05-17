#include "Vector.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Vector::Vector() {}
Vector::Vector(const Vector& vector)
{
    const double* c = vector.getCoordinates();
    for(int i = 0; i < 4; i++)
    {
        x[i] = c[i];
    }
}

Vector::Vector(const double x0,
               const double x1,
               const double x2,
               const double x3)
{
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
    x[3] = x3;
}

Vector::Vector(const double x0,
               const double x1,
               const double x2)
{
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
    x[3] = 1;
}

double Vector::magnitude()
{
    return sqrt(x[0] * x[0] +
                x[1] * x[1] +
                x[2] * x[2]) / abs(x[3]);
}


void Vector::normalize()
{
    x[3] *= magnitude();
}

void Vector::multiply(const double& coef)
{
    x[3] /= coef;
}

void Vector::subtract(const Vector& vector)
{
    Vector v = vector;
    v.multiply(-1);
    add(v);
}

void Vector::add(const Vector& vector)
{
    translate(vector);
}

void Vector::scale(const double* coef)
{
    double matrix[4][4] = {{coef[0], 0, 0, 0},
                           {0, coef[1], 0, 0},
                           {0, 0, coef[2], 0},
                           {0, 0, 0, 1}};
    multm(matrix);
}

Vector2D Vector::project(const double& coef) const
{
    double matrix[4][4] = {{1, 0, 0 ,0},
                           {0, 1, 0, 0},
                           {0, 0, 1, 0},
                           {0, 0, -1 / coef, 1}};
    Vector tmp(*this);
    tmp.multm(matrix);
    const double* coord = tmp.getCoordinates();
    Vector2D result;
    result.x[0] = coord[0] / coord[3];
    result.x[1] = coord[1] / coord[3];
    result.z = coord[2] / coord[3];
    return result;
}
void Vector::translate(const Vector& vector)
{
    const double* coord = vector.getCoordinates();
    double matrix[4][4] = {{1, 0, 0, coord[0]/coord[3]},
                           {0, 1, 0, coord[1]/coord[3]},
                           {0, 0, 1, coord[2]/coord[3]},
                           {0, 0, 0, 1}};
    multm(matrix);
}

const double* Vector::getCoordinates() const
{
    return x;
}

void Vector::multm(double matrix[4][4])
{
    double newCoordinates[4];
    for(int i = 0; i < 4; i++)
    {
        newCoordinates[i] = 0;
        for(int k = 0; k < 4; k++)
        {
            newCoordinates[i] += matrix[i][k] * x[k];
        }
    }
    for(int i = 0; i < 4; i++)
    {
        x[i] = newCoordinates[i];
    }
}

void Vector::rotate(const double* angle)
{
    for(int i = 2; i >= 0; i--)
    {
        rotateHelper(i, angle[i]);
    }
}

void Vector::rotateHelper(const int number, const double angle)
{
    double _sin = sin(angle);
    double _cos = cos(angle);

    double matrix[3][4][4] = {{
                               {1, 0, 0, 0},
                               {0, _cos, -_sin, 0},
                               {0, _sin, _cos, 0},
                               {0, 0, 0, 1}
                              },
                              {
                               {_cos, 0, _sin, 0},
                               {0, 1, 0, 0},
                               {-_sin, 0, _cos, 0},
                               {0, 0, 0, 1}
                              },
                              {
                               {_cos, -_sin, 0, 0},
                               {_sin, _cos, 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}
                              }
                             };
    multm(matrix[number]);
};

void Vector::print() const
{
    std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << std::endl;
}

double Vector::getX() const
{
    return x[0]/x[3];
}

double Vector::getY() const
{
    return x[1]/x[3];
}

double Vector::getZ() const
{
    return x[2]/x[3];
}
