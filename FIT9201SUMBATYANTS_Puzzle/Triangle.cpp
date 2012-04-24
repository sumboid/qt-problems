#include <cmath>
#include "Triangle.h"

Triangle::Triangle(View* _view, const QImage& _image):
    scale(0), view(_view), image(_image)
{
    for(int i = 0; i < 3; ++i)
    {
        imagePoints[i] = Point(0, 0);
    }
}

void Triangle::setImageCoordinates(const Point* coordinates)
{
    for(int i = 0; i < 3; ++i)
    {
        imagePoints[i].first = coordinates[i].first;
        imagePoints[i].second = coordinates[i].second;
    }
}

void Triangle::setScale(const double& _scale)
{
    scale = _scale;
}

std::vector<Point> Triangle::getLine(const Point _x, const Point _y)
{
    Point x = _x;
    Point y = _y;
    std::vector<Point> line;
    const int deltaX = abs(x.first - y.first);
    const int deltaY = abs(y.second - x.second);
    const int signX = x.first < y.first ? 1 : -1;
    const int signY = x.second < y.second ? 1 : -1;

    int error = deltaX - deltaY;
    setPixel(y.first, y.second);
    while(x.first != y.first || x.second != y.second)
    {
        line.insert(Point(x.first, x.second));
        const int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x.first += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            x.second += signY;
        }
    }

    return line;
}

#define LENGTH(x, y) (::sqrt((x.first - y.first) * (x.first - y.first) + \
                             (x.second - y.second) * (x.second - y.second)))

unsigned int Triangle::getColor(const Point& d)
{
//    double cb = ::sqrt((c.first - b.first) * (c.first - b.first) +
//                       (c.second - b.second) * (c.second - b.second));
//    double ca = ::sqrt((c.first - a.first) * (c.first - a.first) +
//                       (c.second - a.second) * (c.second - a.second));
//    double cx = ::sqrt((c.first - x.first) * (c.first - x.first) +
//                       (c.second - x.second) * (c.second - x.second));
    double cb = LENGTH(points[0], points[2]);
    double ca = LENGTH(points[0], points[1]);
    double cd = LENGTH(points[0], d);
    double _cos = ((points[2].first - points[0].first) * (d.first - points[0].first) +
                   (points[2].second - points[0].second) * (d.second - points[0].second)) /
                   (cd * cb);
    double _sin = ::sqrt(1 - _cos * _cos);
    double u = cd * _cos / cb;
    double v = cd * _sin / ca;

    int x, y;
    //Nearest
    if(imagePoints[0].second > imagePoints[1].second)
    {
        x = static_cast<int>(imagePoints[0].first - LENGTH(imagePoints[0], imagePoints[2]) * u + 0.5);
        y = static_cast<int>(imagePoints[0].second - LENGTH(imagePoints[0], imagePoints[1]) * v + 0.5);
    }
    else
    {
        x = static_cast<int>(imagePoints[0].first + LENGTH(imagePoints[0], imagePoints[2]) * u + 0.5);
        y = static_cast<int>(imagePoints[0].second + LENGTH(imagePoints[0], imagePoints[1]) * v + 0.5);
    }

    return image.pixel(x, y);
}

void Triangle::draw(const Point x, const double _angle)
{
    /* Hurdcoar
     *
     *  [a]
     *   |\
     *   | \
     *   |  \
     *   |   \
     *  [c]--[b]
     *
     *  [[c, 0], [a, 1], [b, 2]]
     */

    Points a, b, c = 0;

    //Vodka Absolut
    a.first = scale * (imagePoints[1].first - imagePoints[0].first) + points[0].first;
    a.second = scale * (imagePoints[1].second - imagePoints[0].second) + c.second;

    b.first = scale * (imagePoints[2].first - imagePoints[0].first) + c.first;
    b.second = scale * (imagePoints[2].second - imagePoints[0].second) + c.second;


    //TODO: rotate

    //Setting points and angle for getColor()
    points[0].first = c.first;
    points[0].second = c.second;
    points[1].first = a.first;
    points[1].second = a.second;
    points[2].first = b.first;
    points[2].second = b.second;

    angle = _angle;

    //Search point with min(y)
    vector left, right, bottom; //left, right and bottom lines

    if (a.second >= b.second)
    {
        if (b.second >= c.second)
        {

            if(a.first > b.first)
            {
                /*  a.y >= b.y
                 *  [b]----[a]
                 *   \     /
                 *    \   /
                 *     \ /
                 *     [c]
                 */

                left = getLine(c, b);
                right = getLine(c, a);
                bottom = getLine(b, a);
            }
            else
            {
                /*  a.y >= b.y
                 *  [a]----[b]
                 *   \     /
                 *    \   /
                 *     \ /
                 *     [c]
                 */
                left = getLine(c, a);
                right = getLine(c, b);
                bottom = getLine(a, b);
            }
        }
        else
        {
            if(a.first > c.first)
            {
                /*
                 *  a.y >= c.y
                 *  [c]----[a]
                 *   \     /
                 *    \   /
                 *     \ /
                 *     [b]
                 */
                left = getLine(b, c);
                right = getLine(b, a);
                bottom = getLine(c, a);
            }
            else
            {
                /*  a.y >= c.y
                 *  [a]----[c]
                 *   \     /
                 *    \   /
                 *     \ /
                 *     [b]
                 *
                 *  etc
                 */
                left = getLine(b, a);
                right = getLine(b, c);
                bottom = getLine(a, c);
            }
        }
    }
    else
    {
        if (a.second >= c.second)
        {
            if(a.first > b.first)
            {
                left = getLine(c, b);
                right = getLine(c, a);
                bottom = getLine(b, a);
            }
            else
            {
                left = getLine(c, a);
                right = getLine(c, b);
                bottom = getLine(a, b);
            }
        }
        else
        {
            if(b.first > c.first)
            {
                left = getLine(a, c);
                right = getLine(a, b);
                bottom = getLine(c, b);
            }
            else
            {
                left = getLine(a, b);
                right = getLine(a, c);
                bottom = getLine(b, c);
            }
        }
    }

    //Prepare to start draw
    size_t leftSize = left.size();
    size_t rightSize = right.size();
    size_t bottomSize = bottom.size();

    int lineNumber = left[0].second;

    int l = 0, r = 0, b = 0;

    for(l = 0; l < leftSize; ++l)
    {
        //Search last left pixel on lineNumber
        if(l + 1 != leftSize && left[l + 1].second == lineNumber)
        {
            view->setPixel(left[l].first, left[l].second, 0x0);
            continue;
        }

        view->setPixel(left[l].first, left[l].second, 0x0);

        if(r != rigthSize)
        {
            for(int i = left[l].second + 1; i < right[r].second; ++i)
            {
                view->setPixel(lineNumber, i, getColor(lineNumber, i));
            }

            while(right[r].second < lineNumber + 1)
            {
                view->setPixel(right[r].first, right[r].second, 0x0);
                ++r;
            }
        }
        else
        {
            for(int i = left[l].second + 1; i < bottom[b].second; ++i)
            {
                view->setPixel(lineNumber, i, getColor(lineNumber, i));
            }

            while(bottom[b].second < lineNumber + 1)
            {
                view->setPixel(bottom[b].first, bottom[b].second, 0x0);
                ++b;
            }
        }

        ++lineNumber;
    }

    if(b == 0)
    {
        for(;b < bottomSize; ++b)
        {
            if(b + 1 != bottomSize && bottom[b + 1].second == lineNumber)
            {
                view->setPixel(bottom[b].first, bottom[b].second, 0x0);
                continue;
            }

            view->setPixel(bottom[b].first, bottom[b].second, 0x0);

            for(int i = bottom[b].second + 1; i < right[r].second; ++i)
            {
                view->setPixel(lineNumber, i, getColor(lineNumber, i));
            }

            while(right[r].second < lineNumber + 1)
            {
                view->setPixel(right[r].first, right[r].second, 0x0);
                ++r;
            }

            ++lineNumber;
        }
    }

    return;
}
