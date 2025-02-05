#ifndef QUICK_HULL_HH
#define QUICK_HULL_HH

#include "Point2D.hh"
#include <vector>

namespace Geometry {
    class QuickHull {
    private:
        static int point2D_farthest_from_edge(Point2D a, Point2D b, Point2D p[], int n);
        static double cross_product(const Point2D& a, const Point2D& b, const Point2D& c);
        static void quick_hull_recursive(Point2D a, Point2D b, std::vector<Point2D>& Point2Ds, std::vector<Point2D>& hull);
    public:
        static std::vector<Point2D> quick_hull(std::vector<Point2D> points);
    };
}
#endif
