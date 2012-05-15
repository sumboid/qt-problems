#include "Model.h"
#include "Line.h"
#include "Vector.h"
#include "Camera.h"
#include "Bezier.h"
#include "Knot.h"
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
    double ps[6][3] =
        { {-1.0, -1.0, -1.0}
        , {-1.0, 1.0, 0.0}
        , {0.0, 2.0, 1.0}
        , {0.5, 1.5, 1.1}
        , {1.0, 1.0,  1.0}
        , {1.0, 1.0, -1.0}
        };

    Knot(ps, 6).draw(view, camera, 0x0);
    view->paint();
}

void Model::resize()
{
}
