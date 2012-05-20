#pragma once
#include "Vector.h"

class Curve
{
public:
    virtual ~Curve() {};
    virtual Vector point(double) const = 0;
};
