#pragma once
#include "View.h"
#include "Camera.h"

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
};
