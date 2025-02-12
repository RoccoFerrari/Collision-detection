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
                *imax = i;
            }
            if(proj < minproj) {
                minproj = proj;
                *imin = i;
            }
        }
    }
    // Compute indices to the most separated points of the six points
    // defining the AABB encompassing the point set. Return these as min and max.
    void GeometryUtils::most_separated_points_on_AABB(int& min, int& max, std::vector<Point3D> points) {
        int n = points.size();
        int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
        // First find most extreme points along principal axes
        for(int i = 0; i < n; ++i) {
            if(points[i].getX() < points[minx].getX())
                minx = i;
            if(points[i].getX() > points[maxx].getX())
                maxx = i;
            if(points[i].getY() < points[miny].getY())
                miny = i;
            if(points[i].getY() > points[maxy].getY())
                maxy = i;
            if(points[i].getZ() < points[minz].getZ())
                minz = i;
            if(points[i].getZ() > points[maxz].getZ())
                maxz = i;
        }

        // Compute the squared distances for the three pairs of points
        float dist2x = (points[maxx] - points[minx]) * (points[maxx] - points[minx]);
        float dist2y = (points[maxy] - points[miny]) * (points[maxy] - points[miny]);
        float dist2z = (points[maxz] - points[minz]) * (points[maxz] - points[minz]);

        // Pick the pair (min, max) of points most distant
        min = minx;
        max = maxx;
        if(dist2y > dist2x && dist2y > dist2z) {
            max = maxy;
            min = miny;
        }
        if(dist2z > dist2x && dist2z > dist2y) {
            max = maxz;
            min = minz;
        }
    }
}