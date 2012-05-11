#pragma once
#include "View.h"
#include "Camera.h"

class Drawable
{
    virtual void draw(View* view, const Camera* camera, unsigned int color) = 0;
};
