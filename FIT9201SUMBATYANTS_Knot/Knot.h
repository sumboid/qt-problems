#pragma once
#include <vector>
#include "Bezier.h"
#include "Vector.h"
#include "Camera.h"
#include "View.h"

class Knot : public Drawable
{
public:
    Knot (double points[6][3], int n);

    virtual void draw(View* view, const Camera* camera, unsigned int color);
    double* getBounds() const;
private:
    void generatePoints();
    std::vector<Vector> workPoints;
    std::vector<Vector> initPoints;

    double bounds[6]; //minx miny minz maxx maxy maxz
};
