#ifndef GEOMETRIC_UTILS_HH
#define GEOMETRIC_UTILS_HH
#include <iterator> 
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
        // Method that returns index max into pt vector of the most distant point along the direction dir
        // Usable for AABB's creation
        template <typename Iterator>
        static void extreme_points_along_direction(const Point3D& dir, Iterator begin, Iterator end, int* imin, int* imax);

        // Compute indices to the most separated points of the six points
        // defining the AABB encompassing the point set. Return these as min and max.
        template <typename Iterator>
        static void most_separated_points_on_AABB(int& min, int& max, Iterator begin, Iterator end);

        // This methods find the minimum area rectangle in the XY plain containing the points
        template <typename Iterator>
        static float min_area_rectangle(Iterator begin, Iterator end, Point2D& c, std::pair<Point2D, Point2D> out);

        // Returns the squared distance between point c and segment ab
        static float sq_dist_point_segment(Point3D a, Point3D b, Point3D c);

        // Computer closest points C1 and C2 of S1(s) = P1 + s*(Q1-P1)
        // and S2(t) = P2 + t*(Q2-P2), returning s and t. Function
        // result is squared distance between S1(s) and S2(t)
        static float closest_point_segment_segment(Point3D p1, Point3D q1, Point3D p2, Point3D q2, float& s, float& t, Point3D& c1, Point3D& c2);
    };
}

#endif