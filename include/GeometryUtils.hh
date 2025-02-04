#ifndef GEOMETRY_UTILS_HH
#define GEOMETRY_UTILS_HH

#include "Point.hh"
#include <vector>

namespace Geometry {
    class GeometryUtils {
    private:
        int PointFarthestFromEdge(Point a, Point b, Point p[], int n);
    public:
        static std::vector<Point> QuickHull(Point points[], int n);
    };
}
#endif
