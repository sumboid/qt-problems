#pragma once
#include "View.h"

class Model
{
public:
    Model(View* view);
    ~Model();

    void draw();
    void resize();
private:
    View* view;
};
