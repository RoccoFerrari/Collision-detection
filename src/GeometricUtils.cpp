#include "../include/GeometricUtils.hh"
#include <limits>

namespace Geometry {
    int GeometryUtils::extreme_point_along_direction(Point3D& dir, std::vector<Point3D> points) {

        int n = points.size();
        float maxproj = -std::numeric_limits<double>::max();
        int maxindex = -1;

        for(int i = 0; i < n; ++i) {
            // Project vector from origin to poin onto direction vector
            float proj = points[i] * dir;
            // Keep track of least distant point alogn direction vector
            if(proj > maxproj) {
                maxproj = proj;
                maxindex = i;
            }
        }
        return maxindex;
    }
}