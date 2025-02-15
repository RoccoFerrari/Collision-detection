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
    // Returns the squared distance between point c and segment ab
    float GeometryUtils::sq_dist_point_segment(Point3D a, Point3D b, Point3D c) {
        Point3D ab = b - a, ac = c - a, bc = b - c;
        float e = ac * ab;
        // Handle cases where c projects outside ab
        if (e <= 0.0f) 
            return ac * ac;
        float f = ab * ab;
        if (e >= f) 
            return bc * bc;
        // Handle cases where c projects onto ab
        return ac * ac - e * e / f;
    }
    // Support function: clamp n to lie within the reange [min, max]
    float GeometryUtils::clamp(const float n, const float min, const float max) {
        if(n < min)
            return min;
        if(n > max)
            return max;
        return n;
    }
    // Computer closest points C1 and C2 of S1(s) = P1 + s*(Q1-P1)
    // and S2(t) = P2 + t*(Q2-P2), returning s and t. Function
    // result is squared distance between S1(s) and S2(t)
    float GeometryUtils::closest_point_segment_segment(Point3D p1, Point3D q1, Point3D p2, Point3D q2, float& s, float& t, Point3D& c1,Point3D& c2) {
        float epsilon = std::numeric_limits<float>::epsilon();
        Point3D d1 = q1 - p1; // Direction vector of segment S1
        Point3D d2 = q2 - p2; // Direction vector of segment S2
        Point3D r = p1 - p2;
        float a = d1 * d1; // Squared length of segment S1
        float e = d2 * d2; // Squared length of segment S2
        float f = d2 * r;

        // Check if either or both segments degenerate into points
        if(a <= epsilon && e <= epsilon) {
            // Both segments degenerate into points
            s = t = 0.0f;
            c1 = p1;
            c2 = p2;
            return (c1 - c2) * (c1 - c2);
        }
        if(a <= epsilon) {
            // First element degenerates into a point
            s = 0.0f;
            t = f / e; // s = 0 => t = (b*s + f) / e = f/e
            t = GeometryUtils::clamp(t, 0.0f, 1.0f);
        } else {
            float c = d1 * r;
            if(e <= epsilon) {
                // Second element degenerates into a point
                t = 0.0f;
                s = GeometryUtils::clamp(-c/a, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c/a
            } else {
                // The general nondegenerate case starts here
                float b = d1 * d2;
                float denom = a*e - b*b; // Always nonnegative

                // If segments not parallel, compute closest point on L1 to L2 and
                // clamp to segment S1. Else pick arbitrary s (here 0)
                if(denom != 0.0f)
                    s = GeometryUtils::clamp((b*f - c*e) / denom, 0.0f, 1.0f);
                else
                    s = 0.0f;
                // Copute point on L2 closest to S1(s) using
                // t = ((P1 + D1*s) - P2 * D2) / (D2 * D2) = (b*s + f) / e
                t = (b*s + f) / e;

                // If t in [0, 1] done. Else clamp t, recompute s for new value
                // of t using s = ((P2 + D2*t) - P1 * D1) / (D1 * D1) = (t*b - c) / a
                // and clamp s to [0, 1]
                float tnom = b*s + f;
                if(tnom < 0.0f) {
                    t = 0.0f;
                    s = GeometryUtils::clamp(-c/a, 0.0f, 1.0f);
                } else if(tnom > e) {
                    t = 1.0f;
                    s = GeometryUtils::clamp((b - c) / a, 0.0f, 1.0f);
                } else
                    t = tnom / e;
            }
        }
        c1 = p1 + d1 * s;
        c2 = p2 + d2 * t;
        return (c1 - c2) * (c1 - c2);
    }
}