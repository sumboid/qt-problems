#include "Model.h"
#include "Line.h"
#include "Vector.h"
#include "Camera.h"
#include "Bezier.h"
#include "Knot.h"
#include "CustomSpline.h"
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
    /*Line( 1,  1,  1, -1,  1,  1).draw(view, camera, 0x0);
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
    */
    double ps[6][3] =
            { {0.7, 0.0, 0.9}
            , {1.0, 1.0, 0.0}
            , {0.0, 1.0, 1.0}
            , {0.9, 0.0, 0.0}
            , {0.9, 0.9, 1.0}
            , {0.0, 1.0, 0.0}};

    double start[3] = {0, 0, 0};
    double end[3] = {1, 1, 2};
    //CustomSpline(start, end).draw(view, camera, 0x0);
    Knot knot(ps, 6);
    knot.draw(view, camera, 0x0);
    /*double* bounds = knot.getBounds();
    Line(bounds[0], bounds[1], bounds[2], bounds[3], bounds[1], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[2], bounds[0], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[2], bounds[0], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[4], bounds[5], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[5], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[1], bounds[5], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[1], bounds[2], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[3], bounds[1], bounds[2], bounds[3], bounds[1], bounds[5]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[4], bounds[2], bounds[3], bounds[4], bounds[2]).draw(view, camera, 0x0);
    Line(bounds[0], bounds[4], bounds[2], bounds[0], bounds[4], bounds[5]).draw(view, camera, 0x0);
    for(int i = 0; i < 6; i++)
    {
        std::cout << bounds[i] << " ";
    }
    std::cout << std::endl;
*/
    view->paint();
}

void Model::resize()
{
}
