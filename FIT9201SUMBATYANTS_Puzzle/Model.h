#pragma once
#include <QRgb>
#include <vector>
#include <utility>
#include "View.h"
#include "Triangle.h"
#include "Filter.h"

const int NUMBER_OF_TRIANGLES = 32;

class Model
{
public:
    Model(View* view);
    ~Model();

    void draw();
    void setStep(const int);
    void invertButton(bool);
    void setFilter(const int);
    void setBlend(const int);
    void init();
private:
    void setTrianglePoints(Triangle& triangle, const int number);
    double getVScale() const;
    double getHScale() const;
    Point getTrianglePosition(const int);
    double getTriangleAngle(const int);

    View* view;
    QImage image;

    Triangle* triangles[NUMBER_OF_TRIANGLES];
    double angles[NUMBER_OF_TRIANGLES];
    std::pair<double, double> lastPoints[NUMBER_OF_TRIANGLES];
    int step;
};
