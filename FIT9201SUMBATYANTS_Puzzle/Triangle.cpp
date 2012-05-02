/* GPL2.txt */

#include <cmath>
#include <vector>
#include "Triangle.h"

#include <iostream>

Triangle::Triangle(View* _view, const QImage* _image):
    scale(1), view(_view), image(_image)
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

std::vector<Point> Triangle::getLine(const Point& _x, const Point& _y) const
{
    Point x = _x;
    Point y = _y;
    std::vector<Point> line;
    const int deltaX = abs(x.first - y.first);
    const int deltaY = abs(y.second - x.second);
    const int signX = x.first < y.first ? 1 : -1;
    const int signY = x.second < y.second ? 1 : -1;

    int error = deltaX - deltaY;
    while(x.first != y.first || x.second != y.second)
    {
        line.push_back(Point(x.first, x.second));
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

    line.push_back(Point(y.first, y.second));
    return line;
}

#define LENGTH(x, y) (::sqrt((x.first - y.first) * (x.first - y.first) + \
                             (x.second - y.second) * (x.second - y.second)))

unsigned int Triangle::getColor(const Point& d) const
{
    return 0x0;
    double cd = LENGTH(points[0], d);

    if (cd == 0)
    {
        return image->pixel(imagePoints[0].first, imagePoints[0].second);
    }

    double cb = LENGTH(points[0], points[2]);
    double ca = LENGTH(points[0], points[1]);
    double _cos = ((points[2].first - points[0].first) * (d.first - points[0].first) +
                   (points[2].second - points[0].second) * (d.second - points[0].second)) /
                   (cd * cb);
    double _sin = ::sqrt(1 - _cos * _cos);
    double u = cd * _cos / cb;
    double v = cd * _sin / ca;

    //if(d.first < points[0].first)
    //std::cout << //"(" << u << ", " << v << "): 
    //             " cos = " << _cos << " sin = " << _sin << " d.first = " << d.first << " c.first = " << points[0].first << std::endl;
                    //" scal = " <<
//              abs(points[2].first - points[0].first) * abs(d.first - points[0].first) +
//              abs(points[2].second - points[0].second) * abs(d.second - points[0].second) << std::endl; 

    int x, y;
    //Nearest
    if(imagePoints[0].first > imagePoints[2].first)
    {
        x = static_cast<int>(imagePoints[0].first - LENGTH(imagePoints[0], imagePoints[2]) * u + 0.5);
    }
    else
    {
        x = static_cast<int>(imagePoints[0].first + LENGTH(imagePoints[0], imagePoints[2]) * u + 0.5);
    }

    if(imagePoints[0].second > imagePoints[1].second)
    {
        y = static_cast<int>(imagePoints[0].second - LENGTH(imagePoints[0], imagePoints[1]) * v + 0.5);
    }
    else
    {
        y = static_cast<int>(imagePoints[0].second + LENGTH(imagePoints[0], imagePoints[1]) * v + 0.5);
    }

    return image->pixel(x, y);
}

void Triangle::draw(const Point& x, const double _angle)
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

    Point a, b, c = Point(x.first, x.second);

    //Vodka Absolut
    a.first = scale * (imagePoints[1].first - imagePoints[0].first) + c.first;
    a.second = c.second - scale * (imagePoints[0].second - imagePoints[1].second);

    b.first = scale * (imagePoints[2].first - imagePoints[0].first) + c.first;
    b.second = c.second - scale * (imagePoints[0].second - imagePoints[2].second);

    double _cos = ::cos(_angle);
    double _sin = ::sin(_angle);

    a.first = c.first -
        static_cast<int>(static_cast<double>(c.second - a.second) * _sin + 0.5);
    a.second = c.second -
        static_cast<int>(static_cast<double>(c.second - a.second) * _cos + 0.5);

    b.second = c.second -
        static_cast<int>(static_cast<double>(b.first - c.first) * _sin + 0.5);
    b.first = c.first +
        static_cast<int>(static_cast<double>(b.first - c.first) * _cos + 0.5);
    //TODO: rotate

    //Setting points for getColor()
    points[0].first = c.first;
    points[0].second = c.second;
    points[1].first = a.first;
    points[1].second = a.second;
    points[2].first = b.first;
    points[2].second = b.second;

    //Search point with max(y)
    std::vector<Point> left, right, bottom; //left, right and bottom lines

    if (a.second >= b.second)
    {
        if (b.second >= c.second)
        {
            std::cout << "C - top" << std::endl;

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
                bottom = getLine(a, b);
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
            std::cout << "B - top" << std::endl;
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
                bottom = getLine(a, c);
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
            std::cout << "C - top" << std::endl;
            if(a.first > b.first)
            {
                left = getLine(c, b);
                right = getLine(c, a);
                bottom = getLine(a, b);
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
            std::cout << "A - top" << std::endl;
            if(b.first > c.first)
            {
                left = getLine(a, c);
                right = getLine(a, b);
                bottom = getLine(b, c);
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

    int lineNumber = left[0].second - 1;

    size_t l = 0, r = 0, t = 0; //XXX: top

    for(l = 0; l < leftSize; ++l)
    {
        ++lineNumber;

        //Search last left pixel on lineNumber
        if(left[l + 1].second == lineNumber)
        {
            view->setPixel(left[l].first, left[l].second, 0xff0000);
            continue;
        }

        view->setPixel(left[l].first, left[l].second, 0xff0000);

        if(r != rightSize)
        {
            for(int i = left[l].first + 1; i < right[r].first; ++i)
            {
                std::cout << "PEKA" << std::endl;
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }

            while(right[r].second < lineNumber + 1 && r < rightSize)
            {
                std::cout << "YOBA" << std::endl;
                view->setPixel(right[r].first, right[r].second, 0x00ff00);
                ++r;
            }
            if(r == rightSize)
            {
                ++t;
            }
        }
        else
        {
            for(int i = left[l].first + 1; i < bottom[t].first; ++i)
            {
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }

            while(bottom[t].second < lineNumber + 1 && t < bottomSize)
            {
                view->setPixel(bottom[t].first, bottom[t].second, 0x0000ff);
                ++t;
            }
        }

    }
    if(t == 0)
    {
        for(;t < bottomSize; ++t)
        {
            if(t + 1 != bottomSize && bottom[t + 1].second == lineNumber)
            {
                view->setPixel(bottom[t].first, bottom[t].second, 0x0000ff);
                continue;
            }


            view->setPixel(bottom[t].first, bottom[t].second, 0x0000ff);

            //XXX: bugbugbugbugbugbugbugbugb
            for(int i = bottom[t].first + 1; i < right[r].first && r < rightSize; ++i)
            {
                std::cout << "PEKA" << std::endl;
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }

            while(right[r].second < lineNumber + 1 && r < rightSize)
            {
                std::cout << "YOBA" << std::endl;
                view->setPixel(right[r].first, right[r].second, 0x00ff00);
                ++r;
            }

            ++lineNumber;
        }
    }

    return;
}
