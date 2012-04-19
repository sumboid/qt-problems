#include "Point.h"

class Mapper {
public:
    Mapper (Point* points, Point* realPoints);
    ~Mapper ();
    Point getRealPoint(const Point&) const;
private:
    Point points[3]; // [c], [a], [b]
    Point realPoints[3]; // [c], [a], [b]
};
