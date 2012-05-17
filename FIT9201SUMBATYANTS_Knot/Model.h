#pragma once
#include "View.h"
#include "Camera.h"
#include "Knot.h"

class Model
{
public:
    Model(View* view, Camera* camera);
    ~Model();

    void draw();
    void resize();
private:
    View* view;
    Camera* camera;
    Knot* knot;
    double* bounds;
};
