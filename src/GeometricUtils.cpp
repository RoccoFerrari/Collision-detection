#include "../include/GeometricUtils.hh"
#include <limits>
#include <cmath>

namespace Geometry {
    template <typename Iterator>
    void GeometryUtils::extreme_points_along_direction(const Point3D& dir, Iterator begin, Iterator end, int* imin, int* imax) {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;
        using DifferenceType = typename std::iterator_traits<Iterator>::difference_type;

        auto it = begin;
        if (it == end) // Empty container
            return;

        // int n = points.size(); // Questa riga non è necessaria nella versione con iteratori
        float maxproj = -std::numeric_limits<float>::max();
        float minproj = std::numeric_limits<float>::max();
        DifferenceType current_imin = 0;
        DifferenceType current_imax = 0;
        DifferenceType current_index = 0;

        for (; it != end; ++it, ++current_index) {
            // Project vector from origin to poin onto direction vector
            float proj = (*it) * dir;
            // Keep track of least and most distant point(s) along direction vector
            if(proj > maxproj) {
                maxproj = proj;
                current_imax = current_index;
            }
            if(proj < minproj) {
                minproj = proj;
                current_imin = current_index;
            }
        }
        if (imin) *imin = current_imin;
        if (imax) *imax = current_imax;
    }
    // Compute indices to the most separated points of the six points
    // defining the AABB encompassing the point set. Return these as min and max.
    template <typename Iterator>
    void GeometryUtils::most_separated_points_on_AABB(int& min, int& max, Iterator begin, Iterator end) {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;
        using DifferenceType = typename std::iterator_traits<Iterator>::difference_type;

        auto it = begin;
        if (it == nullptr)
            return; // Empty container

        DifferenceType current_index = 0;
        DifferenceType minx_idx = 0, maxx_idx = 0, miny_idx = 0, maxy_idx = 0, minz_idx = 0, maxz_idx = 0;
        ValueType minx_point = *it, maxx_point = *it, miny_point = *it, maxy_point = *it, minz_point = *it, maxz_point = *it;
        // First find most extreme points along principal axes
        for(; it != end; it++) {
            if(it->getX() < minx_point.getX()) {
                minx_point = *it;
                minx_idx = current_index;
            }
            if(it->.getX() > maxx_point.getX()) {
                maxx_point = *it;
                maxx_idx = current_index;
            }
            if(it->.getY() < miny_point.getY()) {
                miny_point = *it;
                miny_idx = current_index;
            }
            if(it->.getY() > maxy_point.getY()) {
                maxy_point = *it;
                maxy_idx = current_index;
            }
            if(it->.getZ() < minz_point.getZ()) {
                minz_point = *it;
                minz_idx = current_index;
            }
            if(it->.getZ() > maxz_point.getZ()) {
                maxz_point = *it;
                maxz_idx = current_index;
            }
        }

        // Compute the squared distances for the three pairs of points
        float dist2x = (maxx_point - minx_point) * (maxx_point - minx_point);
        float dist2y = (maxy_point - miny_point) * (maxy_point - miny_point);
        float dist2z = (maxz_point - minz_point) * (maxz_point - minz_point);

        // Pick the pair (min, max) of points most distant
        min = minx_idx;
        max = maxx_idx;
        if(dist2y > dist2x && dist2y > dist2z) {
            max = maxy_idx;;
            min = miny_idx;
        }
        if(dist2z > dist2x && dist2z > dist2y) {
            max = maxz_idx;
            min = minz_idx;
        }
    }

    // This method finds the minimum area rectangle in the XY plain containing the points.
    // It returns the minimun area and a vector
    template <typename Iterator>
    float GeometryUtils::min_area_rectangle(Iterator begin, Iterator end, Point2D& c, std::pair<Point2D, Point2D> out) {
        using ValueType = typename std::iterator_traits<InputIterator>::value_type;

        auto it_begin = begin;
        auto it_end = end;
        auto n = std::distance(it_begin, it_end);
        float minArea = std::numeric_limits<float>::max();

        if (n < 3) 
            return 0.0f; // No rectangle with less than 3 points
        

        // Loop through all edges; j trails i by 1, modulo n
        for(long long i = 0, j = n - 1; i < n; j = i, ++i) {
            auto it_i = std::next(it_begin, i);
            auto it_j = (i == 0) ? std::prev(it_end) : std::prev(it_i);
            
            // Get current edge e0 (e0x, e0y), normalized
            Point2D e0 = *it_i - *it_j;
            float dx = e0.getX();
            float dy = e0.getY();
            float dist = std::sqrt(dx * dx + dy * dy);
            e0 = e0 / dist;

            // Get an axis e1 orthogonal to edge e0
            Point2D e1 = Point2D(-e0.getY(), e0.getX()); // = Perp2D(e0)

            // Loop through all points to get maximum extends
            float min0 = 0.0f, min1 = 0.0f, max0 = 0.0f, max1 = 0.0f;
            for(auto it_k = it_begin; it_k != it_end; ++it_k) {
                // Project points onto axes e0 and e1 and keep track
                // of minimum and maximum values along both axes
                Point2D d = *it_k - *it_j;
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
                c = *it_j + (e0 * (min0 + max0) + e1 * (min1 + max1)) * 0.5f;
                out.first = e0;
                out.second = e1;
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