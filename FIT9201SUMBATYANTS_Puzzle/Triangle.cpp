/* GPL2.txt */

#include <cmath>
#include <vector>
#include <algorithm>
#include "Triangle.h"
#include "Line.h"

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

#define LENGTH(x, y) (::sqrt((x.first - y.first) * (x.first - y.first) + \
                             (x.second - y.second) * (x.second - y.second)))

unsigned int Triangle::getColor(const Point& d) const
{
    //return 0x0;
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

// Comparator
bool ycomp(const Point& x, const Point& y)
{
    return x.second < y.second;
}

#define EQUAL(x, y) (x.first == y.first && x.second == y.second)
#define PRINT(a, x) (std::cout << a << " = (" << x.first << ", " << x.second << ")" << std::endl)

void Triangle::draw(const Point& x, const double _angle)
{
    /*
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

    //Scale
    a.first = scale * (imagePoints[1].first - imagePoints[0].first) + c.first;
    a.second = c.second - scale * (imagePoints[0].second - imagePoints[1].second);

    b.first = scale * (imagePoints[2].first - imagePoints[0].first) + c.first;
    b.second = c.second - scale * (imagePoints[0].second - imagePoints[2].second);

    //Rotate
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

    //Setting points for getColor()
    points[0].first = c.first;
    points[0].second = c.second;
    points[1].first = a.first;
    points[1].second = a.second;
    points[2].first = b.first;
    points[2].second = b.second;

    //Search point with max(y)
    enum Position {TOP = 0, MIDDLE = 1, BOTTOM = 2};

    Point sortPoints[3] = {c, a, b};
    std::sort(sortPoints, sortPoints + 3, ycomp);
    Position left, right;

    if(sortPoints[MIDDLE].first > sortPoints[BOTTOM].first)
    {
        left = BOTTOM;
        right = MIDDLE;
    }
    else
    {
        left = MIDDLE;
        right = BOTTOM;
    }

    int lineNumber = sortPoints[TOP].second;

    Point leftBorder = sortPoints[TOP], rightBorder = sortPoints[TOP];
    Point bottomBorder = sortPoints[MIDDLE];

    Line leftLine(sortPoints[TOP], sortPoints[left]);
    Line rightLine(sortPoints[TOP], sortPoints[right]);
    Line bottomLine(sortPoints[MIDDLE], sortPoints[BOTTOM]);

    PRINT("top", sortPoints[TOP]);
    PRINT("middle", sortPoints[MIDDLE]);
    PRINT("bottom", sortPoints[BOTTOM]);
    PRINT("left", sortPoints[left]);
    PRINT("right", sortPoints[right]);

    std::cout << "-----------" << std::endl;

    while(!EQUAL(sortPoints[BOTTOM], leftBorder))
    {
        //view->setPixel(leftBorder.first, leftBorder.second, 0xff0000);
        for(int i = leftBorder.first + 1; i < rightBorder.first; i++)
        {
            view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
        }

        while(rightBorder.second == lineNumber)
        {
            view->setPixel(rightBorder.first, rightBorder.second, 0x00ff00);
            if(EQUAL(rightBorder, sortPoints[MIDDLE]))
            {
                rightBorder = bottomBorder;
                rightLine = bottomLine;
            }
            if(EQUAL(rightBorder, sortPoints[BOTTOM]))
            {
                break;
            }
            PRINT("point",rightBorder);
            PRINT("bottom",sortPoints[BOTTOM]);
            rightBorder = rightLine.next();
        }
        while(leftBorder.second == lineNumber)
        {
            view->setPixel(leftBorder.first, leftBorder.second, 0xff0000);
            if(EQUAL(leftBorder, sortPoints[BOTTOM]))
            {
                break;
            }
            if(EQUAL(leftBorder, sortPoints[MIDDLE]))
            {
                leftBorder = bottomBorder;
                leftLine = bottomLine;
            }
            leftBorder = leftLine.next();
        }
        lineNumber++;
    }
}
