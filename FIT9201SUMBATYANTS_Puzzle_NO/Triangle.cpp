#include <cmath>
#include <sstream>
#include <algorithm>
#include "Triangle.h"
#include "Line.h"
#include <QRgb>
#include <iostream>

// Comparators
bool ycomp(const Point& x, const Point& y)
{
    return x.second < y.second;
}
bool xcomp(const Point& x, const Point& y)
{
    return x.first < y.first;
}

#define EQUAL(x, y) (x.first == y.first && x.second == y.second)

Triangle::Triangle(View* _view, const QImage* _image):
vScale(1), hScale(1), filter(NEAREST), view(_view), image(_image), blend(false),
allPixels(0), transparentPixels(0), borderPixels(0)
{
    for(int i = 0; i < 3; ++i)
    {
        imagePoints[i] = Point(0, 0);
    }
}
#define VECT(x, y) (Point(y.first - x.first, y.second - x.second))
#define MUL(x, y) (x.first*y.second - x.second*y.first)
#define SGN(x) (x >= 0 ? 1 : -1)

bool Triangle::checkPoint(const Point& point) const
{
    Point ca = VECT(points[0], points[1]);
    Point cd = VECT(points[0], point);
    Point ab = VECT(points[1], points[2]);
    Point ad = VECT(points[1], point);
    Point bc = VECT(points[2], points[0]);
    Point bd = VECT(points[2], point);

    int mul1 = MUL(ca, cd);
    int mul2 = MUL(ab, ad);
    int mul3 = MUL(bc, bd);

    return ((SGN(mul1) == SGN(mul2)) &&
            (SGN(mul2) == SGN(mul3)) &&
            (SGN(mul3) == SGN(mul1)));
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

void Triangle::setScale(const double& _vscale, const double& _hscale)
{
    vScale = _vscale;
    hScale = _hscale;
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
    double u = cd * _cos / cb;
    double v = cd * _sin / ca;

    double x, y;

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

    if(static_cast<int>(x + 1) >= image->width() || static_cast<int>(y + 1) >= image->height()) return 0x0; //Check bugs
    if(x < 0 || y < 0) return 0x0;
    unsigned int rgb = 0;

    if(filter == NEAREST)
    {
        rgb = image->pixel(x + 1, y + 1);
    }
    else if(filter == BILINEAR)
    {
        int ix = x;
        if (ix > image->width() - 2)
        {
            ix = image->width() - 2;
        }
        int iy = y;
        if (iy > image->height() - 2)
        {
            iy = image->height() - 2;
        }
        double dx = x - ix;
        double dy = y - iy;

        //std::cout << x << " " << ix << " " << y << " " << iy << std::endl;
        double d[] = {(1 - dy) * (1 - dx),
                      dy * (1 - dx),
                      dy * dx,
                      (1 - dy) * dx };
        int p[] = {image->pixel(ix, iy),
                   image->pixel(ix, iy + 1),
                   image->pixel(ix + 1, iy + 1),
                   image->pixel(ix + 1, iy)};

        double rgba[] = {0, 0, 0, 0};
        for(int j = 0; j < 4; j++)
        {
            rgba[0] += qRed(p[j]) * d[j];
            rgba[1] += qGreen(p[j]) * d[j];
            rgba[2] += qBlue(p[j]) * d[j];
            rgba[3] += qAlpha(p[j]) * d[j];
        }
        rgb = qRgba(rgba[0], rgba[1], rgba[2], rgba[3]);
    }

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
    if(false && filter == BILINEAR)
    {
        int yoba;
        std::cin >> yoba;
    }
    allPixels = 0;
    transparentPixels = 0;
    borderPixels = 0;

    Point a, b, c = Point(x.first, x.second);

    //Scale
    a.first = hScale * (imagePoints[1].first - imagePoints[0].first) + (double)c.first + 0.5;
    a.second = c.second - vScale * (imagePoints[0].second - imagePoints[1].second) + 0.5;
    b.first = hScale * (imagePoints[2].first - imagePoints[0].first) + (double)c.first + 0.5;
    b.second = c.second - vScale * (imagePoints[0].second - imagePoints[2].second) + 0.5;

    //Rotate
    double _cos = ::cos(_angle);
    double _sin = ::sin(_angle);

    a.first = c.first -
        static_cast<int>(static_cast<double>(c.second - a.second) * _sin);
    a.second = c.second -
        static_cast<int>(static_cast<double>(c.second - a.second) * _cos);

    b.second = c.second -
        static_cast<int>(static_cast<double>(b.first - c.first) * _sin);
    b.first = c.first +
        static_cast<int>(static_cast<double>(b.first - c.first) * _cos);
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
        if(leftBorder.first + 1 < rightBorder.first)
        {
            for(int i = leftBorder.first + 1; i < rightBorder.first; i++)
            {
                allPixels++;
                view->setPixel(i, lineNumber, getColor(Point(i, lineNumber)));
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

void Triangle::setFilter(const Filter& _filter)
{
    filter = _filter;
}
