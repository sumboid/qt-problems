#pragma once
#include <QRgb>
#include "View.h"
#include "Triangle.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void setSpeed(const int speed);
    void draw() const;
    void setAngle(const double);
    void invertButton(bool);
private:
    void setTrianglesPoints(Triangle& triangle, const int number);


    View* view;
    QImage image;
    vector<Triangle> triangles;
    double angle;
};
