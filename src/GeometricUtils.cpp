#include "../include/GeometricUtils.hh"
#include <limits>
#include <cmath>

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
    // This methods find the minimum area rectangle in the XY plain containing the points
    float GeometryUtils::min_area_rectangle(std::vector<Point2D> pt, Point2D& c, std::vector<Point2D> u) {
        int n = pt.size();
        float minArea = std::numeric_limits<float>::max();

        // Loop through all edges; j trails i by 1, modulo n
        for(int i = 0, j = n - 1; i < n; j = i, ++i) {
            // Get current edge e0 (e0x, e0y), normalized
            Point2D e0 = pt[i] - pt[j];
            float dx = pt[i].getX() - pt[j].getX();
            float dy = pt[i].getY() - pt[j].getY();
            float dist = sqrt(dx * dx + dy * dy);
            e0 = e0 / dist;

            // Get an axis e1 orthogonal to edge e0
            Point2D e1 = Point2D(-e0.getY(), e0.getX()); // = Perp2D(e0)

            // Loop through all points to get maximum extends
            float min0 = 0.0f, min1 = 0.0f, max0 = 0.0f, max1 = 0.0f;
            for(int k = 0; k < n; ++k) {
                // Project points onto axes e0 and e1 and keep track
                // of minimum and maximum values along both axes
                Point2D d = pt[k] - pt[j];
                float dot = d * e0;
                if(dot < min0)
                    min0 = dot;
                if(dot > max0)
                    max0 = dot;
                dot = d * e1;
                if(dot < min1)
                    min1 = dot;
                if(dot > max1)
                    max1 = dot;
            }
            float area = (max0 - min0) * (max1 - min1);

            // If best so far, remember area, center and axes
            if(area < minArea) {
                minArea = area;
                c = pt[j] + (e0 * (min0 + max0) + e1 * (min1 + max1)) * 0.5f;
                u[0] = e0;
                u[1] = e1;
            }
        }
        return minArea;
    }
}