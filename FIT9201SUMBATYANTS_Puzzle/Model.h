#pragma once
#include <QRgb>
#include <vector>
#include "View.h"
#include "Triangle.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void setSpeed(const int speed);
    void draw();
    void setAngle(const double);
    void invertButton(bool);
private:
    void setTrianglePoints(Triangle& triangle, const int number);
    double getScale() const;

    View* view;
    QImage image;
    std::vector<Triangle> triangles;
    double angle;
};
