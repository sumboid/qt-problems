#include <QImage>
#include "Filter.h"
#include "Point.h"

class Mapper {
public:
    Mapper (const Point* realPoints,
            const QImage& image);
    ~Mapper ();
    void setPoints(const Point* points);
    void setScale(const double scale);
    void setFilter(const Filter type);
    unsigned int getColor(const Point&) const;
private:
    Point points[3]; // [c], [a], [b]
    Point realPoints[3]; // [c], [a], [b]
    double scale;
    const QImage& image;
    Filter filter;
};
