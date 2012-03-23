#ifndef MODELSIN_H
#define MODELSIN_H

#include "View.h"

class ModelSin
{
public:
    ModelSin(View* view);
    ~ModelSin();

    void setFunction();
    void setAxis();
    void update();
    void clear();
private:
    View* view;
    bool func;
    bool axis;

    void drawFunction();
    void drawAxis();
};

#endif // MODELSIN_H
