#ifndef GEOMETRIC_UTILS_HH
#define GEOMETRIC_UTILS_HH
#include <vector>
#include "Point3D.hh"
#include "Point2D.hh"
#include "QuickHull.hh"

// Class containig several methods useful for a moltitude of situations

namespace Geometry {
    class GeometryUtils {
    private:

    public:
        // Method that returns indice max into pt vector of the most distante point along the direction dir
        // Usable for AABB's creation
        static void extreme_points_along_direction(Point3D& dir, std::vector<Point3D> points, int *imin, int *imax);
        // Compute indices to the most separated points of the six points
        // defining the AABB encompassing the point set. Return these as min and max.
        static void most_separated_points_on_AABB(int& min, int& max, std::vector<Point3D> points);

        // This methods find the minimum area rectangle in the XY plain containing the points
        static float min_area_rectangle(std::vector<Point2D> pt, Point2D& c, std::vector<Point2D> u);
    };
}

#endif