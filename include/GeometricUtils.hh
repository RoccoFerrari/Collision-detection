#ifndef GEOMETRIC_UTILS_HH
#define GEOMETRIC_UTILS_HH
#include <vector>
#include "Point3D.hh"

// Class containig several methods useful for a moltitude of situations

namespace Geometry {
    class GeometryUtils {
    private:

    public:
        // Method that returns indice max into pt vector of the most distante point along the direction dir
        // Usable for AABB's creation
        static void extreme_points_along_direction(Point3D& dir, std::vector<Point3D> points, int *imin, int *imax);
    };
}

#endif