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
        // Support function: clamp n to lie within the reange [min, max]
        static float clamp(const float n, const float min, const float max);
    public:
        // Method that returns indice max into pt vector of the most distante point along the direction dir
        // Usable for AABB's creation
        static void extreme_points_along_direction(Point3D& dir, std::vector<Point3D> points, int *imin, int *imax);
        // Compute indices to the most separated points of the six points
        // defining the AABB encompassing the point set. Return these as min and max.
        static void most_separated_points_on_AABB(int& min, int& max, std::vector<Point3D> points);

        // This methods find the minimum area rectangle in the XY plain containing the points
        static float min_area_rectangle(std::vector<Point2D> pt, Point2D& c, std::vector<Point2D> u);

        // Returns the squared distance between point c and segment ab
        static float sq_dist_point_segment(Point3D a, Point3D b, Point3D c);

        // Computer closest points C1 and C2 of S1(s) = P1 + s*(Q1-P1)
        // and S2(t) = P2 + t*(Q2-P2), returning s and t. Function
        // result is squared distance between S1(s) and S2(t)
        static float closest_point_segment_segment(Point3D p1, Point3D q1, Point3D p2, Point3D q2, float& s, float& t, Point3D& c1, Point3D& c2);
    };
}

#endif