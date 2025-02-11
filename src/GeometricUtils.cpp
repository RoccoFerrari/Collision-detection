#include "../include/GeometricUtils.hh"
#include <limits>

namespace Geometry {
    void GeometryUtils::extreme_points_along_direction(Point3D& dir, std::vector<Point3D> points, int *imin, int *imax) {

        int n = points.size();
        float maxproj = -std::numeric_limits<float>::max();
        float minproj = std::numeric_limits<float>::max();

        for(int i = 0; i < n; ++i) {
            // Project vector from origin to poin onto direction vector
            float proj = points[i] * dir;
            // Keep track of least and most distant point(s) along direction vector
            if(proj > maxproj) {
                maxproj = proj;
                *imin = i;
            }
            if(proj < minproj) {
                minproj = proj;
                *imax = i;
            }
        }
    }
}