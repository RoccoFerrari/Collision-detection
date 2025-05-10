#include "../include/QuickHull.hh"

namespace Geometry {

    float QuickHull::cross_product(const Point2D& a, const Point2D& b, const Point2D& c) {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    }
}