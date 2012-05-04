#include <cmath>
#include <vector>
#include <algorithm>
#include "Triangle.h"
#include "Line.h"
#include <QRgb>

#include <iostream>

Triangle::Triangle(View* _view, const QImage* _image):
    scale(1), view(_view), image(_image), blend(false), filter(NEAREST)
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


#define MIX(x, y, a)  (qRgba(qRed(x) * a + qRed(y) * (1 - a),\
                             qGreen(x) * a + qGreen(y) * (1 - a),\
                             qBlue(x) * a + qBlue(y) * (1 - a),\
                             qAlpha(x) * a + qAlpha(y) * (1 - a)))

unsigned int Triangle::getColor(const Point& d) const
{
    double cd = LENGTH(points[0], d);

    if (cd < 0.1)
    {
        return image->pixel(imagePoints[0].first, imagePoints[0].second);
    }

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
    double u = cd * _cos / cb;
    double v = cd * _sin / ca;

    float x, y;

    if(imagePoints[0].first > imagePoints[2].first)
    {
        x = (imagePoints[0].first - LENGTH(imagePoints[0], imagePoints[2]) * u);
    }
    else
    {
        x = (imagePoints[0].first + LENGTH(imagePoints[0], imagePoints[2]) * u);
    }

    if(imagePoints[0].second > imagePoints[1].second)
    {
        y = (imagePoints[0].second - LENGTH(imagePoints[0], imagePoints[1]) * v);
    }
    else
    {
        y = (imagePoints[0].second + LENGTH(imagePoints[0], imagePoints[1]) * v);
    }

    if(static_cast<int>(x+0.5) >= image->width() || static_cast<int>(y+0.5) >= image->height()) return 0x0;

    unsigned int rgb = 0;

    if(filter == NEAREST)
    {
        rgb = image->pixel(x + 0.5, y + 0.5);
    }
    else if(filter == BILINEAR)
    {
        int ix = (int) x;
        int iy = (int) y;
        double dx = x - ix;
        double dy = y - iy;

        double d[] = { (1 - dy) * (1 - dx), dy * (1 - dx), dy * dx, (1 - dy) * dx };
        int p[] = { image->pixel(ix, iy), image->pixel(ix, iy + 1), image->pixel(ix + 1, iy + 1), image->pixel(ix + 1, iy) };

        double rgba[] = {0, 0, 0, 0};
        for (int j = 0; j < 4; j++) 
        {
            rgba[0] += qRed(p[j]) * d[j];
            rgba[1] += qGreen(p[j]) * d[j];
            rgba[2] += qBlue(p[j]) * d[j];
        }
        rgba[3] = qAlpha(p[0]);
        rgb = qRgba(rgba[0], rgba[1], rgba[2], rgba[3]);
    }

    if(blend)
    {
        float alpha = ((rgb >> 24) & 0xFF) / (float) 0xff;
        rgb = MIX(rgb, 0xffffff, alpha);
    }

    rgb |= 0xff000000;

    return rgb;
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
    a.first = scale * (imagePoints[1].first - imagePoints[0].first) + c.first + 0.5;
    a.second = c.second - scale * (imagePoints[0].second - imagePoints[1].second) + 0.5;
    b.first = scale * (imagePoints[2].first - imagePoints[0].first) + c.first + 0.5;
    b.second = c.second - scale * (imagePoints[0].second - imagePoints[2].second) + 0.5;

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


    while(!EQUAL(sortPoints[BOTTOM], leftBorder))
    {
        for(int i = leftBorder.first + 1; i < rightBorder.first; i++)
        {
            view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
        }

        while(rightBorder.second == lineNumber)
        {
            view->setPixel(rightBorder.first, rightBorder.second, 0x0);
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
            view->setPixel(leftBorder.first, leftBorder.second, 0x0);
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

void Triangle::setBlend(const bool _blend)
{
    blend = _blend;
}

void Triangle::setFilter(const Filter& _filter)
{
    filter = _filter;
}
