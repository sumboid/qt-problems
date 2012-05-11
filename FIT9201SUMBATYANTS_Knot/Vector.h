#pragma once

struct Vector2D
{
    int x[2];
};

class Vector {
public:
    Vector(const Vector& vector);
    Vector (const double x0,
            const double x1,
            const double x2,
            const double x3);
    double magnitude();
    void normalize();
    void multiply(const double&);
    void subtract(const Vector&);
    void add(const Vector&);
    void scale(const double*);
    Vector2D project(const double&) const;
    void translate(const Vector&);
    void rotate(const double*);

private:
    void multm(double matrix[4][4]);
    const double* getCoordinates() const;
    void rotateHelper(const int number, const double angle);
    double x[4];
};
