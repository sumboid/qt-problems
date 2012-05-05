#pragma once
#include <QRgb>
#include <vector>
#include "View.h"
#include "Triangle.h"
#include "Filter.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void draw();
    void setAngle(const double);
    void invertButton(bool);
    void setFilter(const int);
    void setBlend(const int);
    void init();
private:
    void setTrianglePoints(Triangle& triangle, const int number);
    double getVScale() const;
    double getHScale() const;
    Point getTrianglePosition(Triangle&, const int);

    View* view;
    QImage image;

    std::vector<Triangle*> triangles;
    double angle;
};
