/* GPL2.txt */

#include <cmath>
#include <vector>
#include <algorithm>
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

Point Triangle::getLine(const Point& _x, const Point& _y) const
{
    Point x = _x;
    Point y = _y;
    const int deltaX = abs(x.first - y.first);
    const int deltaY = abs(y.second - x.second);
    const int signX = x.first < y.first ? 1 : -1;
    const int signY = x.second < y.second ? 1 : -1;

    int error = deltaX - deltaY;
    while(x.first != y.first || x.second != y.second)
    {
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
        return Point(x.first, x.second);
    }

    return Point(y.first, y.second);
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

// Comparator
bool ycomp(const Point& x, const Point& y)
{
    return x.first > y.first;
}

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
    Point bottomBorder;

    if(sortPoints[left].second < sortPoints[right].second)
    {
        bottomBorder = sortPoints[left];
    }
    else
    {
        bottomBorder = sortPoints[right];
    }

    while(sortPoints[left] != leftBorder)
    {
        //view->setPixel(leftBorder.first, leftBorder.second, 0xff0000);
        for(int i = leftBorder.first + 1; i < rightBorder.first - 1; i++)
        {
            view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
        }
        while(rightBorder.second == lineNumber)
        {
            view->setPixel(rightBorder.first, lineNumber, 0x00ff00);
            if(rightBorder == sortPoints[right])
            {
                break;
            }
            rightBorder = getLine(rightBorder, sortPoints[right]);
        }
        while(leftBorder.second == lineNumber)
        {
            view->setPixel(leftBorder.first, lineNumber, 0xff0000);
            if(leftBorder == sortPoints[left])
            {
                break;
            }
            leftBorder = getLine(leftBorder, sortPoints[left]);
        }
        lineNumber++;
    }
/*
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
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }

            while(right[r].second < lineNumber + 1 && r < rightSize)
            {
                view->setPixel(right[r].first, right[r].second, 0x00ff00);
                ++r;
            }
            //if(r == rightSize)
            //{
            //    ++t;
            //}
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
    if(t == 1)
    {
        std::cout << "YOBA1" << std::endl;
        for(;t < bottomSize; ++t)
        {
            if(t + 1 != bottomSize && bottom[t + 1].second == lineNumber)
            {
                view->setPixel(bottom[t].first, bottom[t].second, 0x0000ff);
                continue;
            }

            view->setPixel(bottom[t].first, bottom[t].second, 0x0000ff);

            std::cout << bottom[t].first + 1 << " " << right[r].first << std::endl;
            for(int i = bottom[t].first + 1; i < right[r].first && r < rightSize; ++i)
            {
                std::cout << "YOBA" << std::endl;
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }

            while(right[r].second < lineNumber + 1 && r < rightSize)
            {
                view->setPixel(right[r].first, right[r].second, 0x00ff00);
                ++r;
            }

            ++lineNumber;
        }
    }
*/
    return;
}
