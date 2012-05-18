#include "CurveRender.h"
#include "Vector.h"
#include <cstdlib>

CurveRender::CurveRender(const Curve* _curve, double _bound):
    curve(_curve), bound(_bound) {}

void CurveRender::draw(View* view, const Camera* camera, unsigned int color)
{
    int width = view->getWidth() / 2;
    int height = view->getHeight() / 2;
    double eps = 1;
    double right = bound;
    double left = 0;
    bool end;

    Vector2D firstPoint = camera->project(curve->point(0));
    if(firstPoint.z > 0)
    {
        view->setPixel(firstPoint.x[0] + width, firstPoint.x[1] + height, color);
    }

    while(true)
    {
        Vector2D tmpVector = camera->project(curve->point(right));
        Vector rv(curve->point(left));
        Vector2D point = camera->project(rv);

        if(abs(tmpVector.x[0] - point.x[0]) > 1 ||
           abs(tmpVector.x[1] - point.x[1]) > 1 )
        {
            if(right - left < 0.00001)
            {
                break;
            }
            eps = left + (right - left) / 2;
            right = eps;
            end = false;
            continue;
        }

        if(end) break;
        end = true;
        left = eps;
        right = bound;
        if(point.z > 0)
        {
            view->setPixel(point.x[0] + width, point.x[1] + height, color);
        }
    }
    Vector2D lastPoint = camera->project(curve->point(bound));
    if(lastPoint.z > 0)
    {
        view->setPixel(lastPoint.x[0] + width, lastPoint.x[1] + height, color);
    }
}
