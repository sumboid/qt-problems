#include "Triangle.h"
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <QRgb>
#include "Line.h"

#include <iostream>

// Comparator
bool ycomp(const Point& x, const Point& y)
{
    return x.second < y.second;
}
bool xcomp(const Point& x, const Point& y)
{
    return x.first < y.first;
}

#define EQUAL(x, y) (x.first == y.first && x.second == y.second)

Triangle::Triangle(View* _view, const Image* _image):
view(_view), image(_image), blend(false),
allPixels(0), transparentPixels(0), borderPixels(0)
{
    for(int i = 0; i < 3; ++i)
    {
        imagePoints[i] = Point(0, 0);
    }
}

bool Triangle::checkPoint(const Point& point) const
{
    if(EQUAL(points[0], point) ||
       EQUAL(points[1], point) ||
       EQUAL(points[2], point))
    {
        return true;
    }

    Point cpoint[4] = { points[0], points[1], points[2], point };
    std::sort(cpoint, cpoint + 4, xcomp);
    if(EQUAL(cpoint[0], point) || EQUAL(cpoint[3], point))
    {
        return false;
    }
    std::sort(cpoint, cpoint + 4, ycomp);
    if(EQUAL(cpoint[0], point) || EQUAL(cpoint[3], point))
    {
        return false;
    }

    return true;
}

const char* Triangle::getInfo() const
{
    std::stringstream info;
    info << "Border: " << borderPixels <<
            ", All: " << allPixels <<
            ", Opacity: " << allPixels - transparentPixels;

    return info.str().c_str();
}

void Triangle::setImageCoordinates(const Point* coordinates)
{
    for(int i = 0; i < 3; ++i)
    {
        imagePoints[i].first = coordinates[i].first;
        imagePoints[i].second = coordinates[i].second;
    }
}

#define LENGTH(x, y) (::sqrt((x.first - y.first) * (x.first - y.first) + \
                             (x.second - y.second) * (x.second - y.second)))


#define MIX(x, y, a)  (qRgba(qRed(x) * a + qRed(y) * (1 - a),\
                             qGreen(x) * a + qGreen(y) * (1 - a),\
                             qBlue(x) * a + qBlue(y) * (1 - a),\
                             qAlpha(x) * a + qAlpha(y) * (1 - a)))

unsigned int Triangle::getColor(const Point& d)
{
    double cd = LENGTH(points[0], d);
    double cb = LENGTH(points[0], points[2]);
    double ca = LENGTH(points[0], points[1]);

    double _cos = ((points[2].first - points[0].first) * (d.first - points[0].first) +
                   (points[2].second - points[0].second) * (d.second - points[0].second)) /
                   (cd * cb);
    double _sin;
    if(static_cast<int>(_cos) == 1)
    {
        _sin = 0;
    }
    else
    {
        _sin = ::sqrt(1 - _cos * _cos);
    }
    int x = cd * _cos + 0.5;
    int y = cd * _sin + 0.5;

    if(imagePoints[0].first > imagePoints[2].first)
    {
        x = imagePoints[0].first - x;
    }
    else
    {
        x = imagePoints[0].first + x;
    }

    if(imagePoints[0].second > imagePoints[1].second)
    {
        y = imagePoints[0].second - y;
    }
    else
    {
        y = imagePoints[0].second + y;
    }

    if(x >= image->width() || y >= image->height()) return 0x0;

    unsigned int rgb = image->pixel(x, y);

    if(blend)
    {
        int alpha = (rgb >> 24) & 0xff; 
        if(alpha != 0xff)
        {
            rgb = MIX(rgb, view->getColor(d.first, d.second), alpha / (float)0xff);
            transparentPixels++;
        }
    }

    return rgb;
}



void Triangle::setPoints(const Point& x, const double _angle)
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
    a.first = (imagePoints[1].first - imagePoints[0].first) + c.first;
    a.second = c.second - (imagePoints[0].second - imagePoints[1].second);
    b.first = (imagePoints[2].first - imagePoints[0].first) + c.first;
    b.second = c.second - (imagePoints[0].second - imagePoints[2].second);

    //Rotate
    double _cos = ::cos(_angle);
    double _sin = ::sin(_angle);

    a.first = c.first -
        static_cast<int>(static_cast<double>(c.second - a.second) * _sin) + 0.5;
    a.second = c.second -
        static_cast<int>(static_cast<double>(c.second - a.second) * _cos) + 0.5;

    b.second = c.second -
        static_cast<int>(static_cast<double>(b.first - c.first) * _sin) + 0.5;
    b.first = c.first +
        static_cast<int>(static_cast<double>(b.first - c.first) * _cos) + 0.5;
    //Setting points for getColor()
    points[0].first = c.first;
    points[0].second = c.second;
    points[1].first = a.first;
    points[1].second = a.second;
    points[2].first = b.first;
    points[2].second = b.second;
}

void Triangle::draw(const Point& x, const double _angle)
{
    allPixels = 0;
    transparentPixels = 0;
    borderPixels = 0;
    setPoints(x, _angle);
    //Search point with max(y)
    enum Position {TOP = 0, MIDDLE = 1, BOTTOM = 2};

    Point sortPoints[3] = {points[0], points[1], points[2]};
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

    while(!EQUAL(sortPoints[BOTTOM], leftBorder))
    {
        if(leftBorder.first + 1 < rightBorder.first)
        {
            for(int i = leftBorder.first + 1; i < rightBorder.first; i++)
            {
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
                allPixels++;
            }
        }
        else
        {
            for(int i = rightBorder.first + 1; i < leftBorder.first; i++)
            {
                allPixels++;
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
            }
        }

        while(rightBorder.second == lineNumber)
        {
            if(EQUAL(rightBorder, sortPoints[MIDDLE]))
            {
                rightBorder = bottomBorder;
                rightLine = bottomLine;
            }
            if(EQUAL(rightBorder, sortPoints[BOTTOM]))
            {
                break;
            }
            rightBorder = rightLine.next();
        }
        while(leftBorder.second == lineNumber)
        {
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

    leftBorder = sortPoints[TOP];
    rightBorder = sortPoints[TOP];
    bottomBorder = sortPoints[MIDDLE];

    leftLine = Line(sortPoints[TOP], sortPoints[left]);
    rightLine = Line(sortPoints[TOP], sortPoints[right]);
    bottomLine = Line(sortPoints[MIDDLE], sortPoints[BOTTOM]);

    while(leftBorder != sortPoints[left])
    {
        view->setPixel(leftBorder.first, leftBorder.second, 0x0);
        leftBorder = leftLine.next();
        allPixels++;
        borderPixels++;
    }
    while(rightBorder != sortPoints[right])
    {
        view->setPixel(rightBorder.first, rightBorder.second, 0x0);
        rightBorder = rightLine.next();
        allPixels++;
        borderPixels++;
    }
    while(bottomBorder != sortPoints[BOTTOM])
    {
        view->setPixel(bottomBorder.first, bottomBorder.second, 0x0);
        bottomBorder = bottomLine.next();
        allPixels++;
        borderPixels++;
    }

    allPixels++;
    borderPixels++;
    view->setPixel(sortPoints[BOTTOM].first, sortPoints[BOTTOM].second, 0x0);

}

void Triangle::setBlend(const bool _blend)
{
    blend = _blend;
}
