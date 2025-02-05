#ifndef GEOMETRY_UTILS_HH
#define GEOMETRY_UTILS_HH

#include "Point.hh"
#include <vector>

namespace Geometry {
    class GeometryUtils {
    private:
        static int PointFarthestFromEdge(Point a, Point b, Point p[], int n);
        static double CrossProduct(const Point& a, const Point& b, const Point& c);
        static void QuickHullRecursive(Point a, Point b, std::vector<Point>& points, std::vector<Point>& hull);
    public:
        static std::vector<Point> QuickHull(Point points[], int n);
    };
}
#endif
