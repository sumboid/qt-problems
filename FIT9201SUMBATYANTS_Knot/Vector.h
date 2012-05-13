#pragma once

struct Vector2D
{
    int x[2];
    double z;
};

class Vector
{
public:
    Vector(const Vector& vector);
    Vector();
    Vector (const double x0,
            const double x1,
            const double x2,
            const double x3);
    Vector (const double x0,
            const double x1,
            const double x2);
    double magnitude();
    void normalize();
    void multiply(const double&);
    void subtract(const Vector&);
    void add(const Vector&);
    void scale(const double*);
    Vector2D project(const double&) const;
    void translate(const Vector&);
    void rotate(const double*);
    void print() const;

private:
    void multm(double matrix[4][4]);
    const double* getCoordinates() const;
    void rotateHelper(const int number, const double angle);
    double x[4];
};
