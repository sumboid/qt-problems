#include "Model.h"
#include "Line.h"
#include "Vector.h"
#include "Camera.h"
#include "Bezier.h"

#include <iostream>

Model::Model(View* _view, Camera* _camera):
view(_view), camera(_camera)
{
}

Model::~Model()
{
}


void Model::draw()
{
    view->clear();
    Line(0, 0, 0, 2, 0, 0).draw(view, camera, 0xff0000);
    Line(0, 0, 0, 0, 2, 0).draw(view, camera, 0x00ff00);
    Line(0, 0, 0, 0, 0, 2).draw(view, camera, 0x0000ff);
    Line( 1,  1,  1, -1,  1,  1).draw(view, camera, 0x0);
    Line(-1,  1,  1, -1, -1,  1).draw(view, camera, 0x0);
    Line(-1, -1,  1,  1, -1,  1).draw(view, camera, 0x0);
    Line( 1, -1,  1,  1,  1,  1).draw(view, camera, 0x0);
    Line( 1,  1, -1, -1,  1, -1).draw(view, camera, 0x0);
    Line(-1,  1, -1, -1, -1, -1).draw(view, camera, 0x0);
    Line(-1, -1, -1,  1, -1, -1).draw(view, camera, 0x0);
    Line( 1, -1, -1,  1,  1, -1).draw(view, camera, 0x0);
    Line( 1,  1, -1,  1,  1,  1).draw(view, camera, 0x0);
    Line(-1,  1, -1, -1,  1,  1).draw(view, camera, 0x0);
    Line(-1, -1, -1, -1, -1,  1).draw(view, camera, 0x0);
    Line( 1, -1, -1,  1, -1,  1).draw(view, camera, 0x0);
    Vector v[4] = {Vector(0,0,0), Vector(0,5,5), Vector(0,0,5), Vector(0,5,0)};
    Bezier(v).draw(view, camera, 0x0);
    view->paint();
}

void Model::resize()
{
}
