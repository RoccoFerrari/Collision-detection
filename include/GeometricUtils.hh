#ifndef GEOMETRIC_UTILS_HH
#define GEOMETRIC_UTILS_HH
#include <iterator> 
#include <limits>
#include <cmath>
#include "Point3D.hh"
#include "Point2D.hh"
#include "QuickHull.hh"

namespace Geometry {

     /**
     * @class GeometriyUtils.
     * @brief Class containig several methods useful for a moltitude of situations.
     */
    class GeometryUtils {
    private:

        /**
         * @brief Support function: clamp n to lie within the range [min, max]
         * @param n `float`
         * @param min min value
         * @param max max value
         * @return `float` value that represent the min or max value.
         */
        static float clamp(const float n, const float min, const float max);
    public:
        // Method that returns index max into pt vector of the most distant point along the direction dir
        // Usable for AABB's creation
        template <typename Iterator>
        inline static std::pair<Iterator, Iterator> extreme_points_along_direction(const Point3D& dir, Iterator begin, Iterator end) {
            using ValueType = typename std::iterator_traits<Iterator>::value_type;
            using DifferenceType = typename std::iterator_traits<Iterator>::difference_type;

            auto it = begin;
            if (it == end) // Empty container
                return std::make_pair(end, end);

            // int n = points.size(); // Questa riga non è necessaria nella versione con iteratori
            float maxproj = -std::numeric_limits<float>::max();
            float minproj = std::numeric_limits<float>::max();
            DifferenceType current_imin = 0;
            DifferenceType current_imax = 0;
            DifferenceType current_index = 0;
            auto min = it;
            auto max = it;

            for (; it != end; ++it, ++current_index) {
                // Project vector from origin to poin onto direction vector
                float proj = (*it) * dir;
                // Keep track of least and most distant point(s) along direction vector
                if(proj > maxproj) {
                    maxproj = proj;
                    max = it;
                }
                if(proj < minproj) {
                    minproj = proj;
                    min = it;
                }
            }
            return std::make_pair(min, max);
        }

        // Compute indices to the most separated points of the six points
        // defining the AABB encompassing the point set. Return these as min and max.
        template <typename Iterator>
        inline static std::pair<Iterator, Iterator> most_separated_points_on_AABB(Iterator begin, Iterator end) {
            using ValueType = typename std::iterator_traits<Iterator>::value_type;

            auto it = begin;
            if (it == nullptr)
                return std::make_pair(end, end); // Empty container

            Iterator current_index = 0; 
            Iterator minx_it = it, maxx_it = it, miny_it = it, maxy_it = it, minz_it = it, maxz_it = it;
            ValueType minx_point = *it, maxx_point = *it, miny_point = *it, maxy_point = *it, minz_point = *it, maxz_point = *it;

            // First find most extreme points along principal axes
            for(; it != end; it++) {
                if(it->getX() < minx_point.getX()) {
                    minx_point = *it;
                    minx_it = it;
                }
                if(it->getX() > maxx_point.getX()) {
                    maxx_point = *it;
                    maxx_it = it;
                }
                if(it->getY() < miny_point.getY()) {
                    miny_point = *it;
                    miny_it = it;
                }
                if(it->getY() > maxy_point.getY()) {
                    maxy_point = *it;
                    maxy_it = it;
                }
                if(it->getZ() < minz_point.getZ()) {
                    minz_point = *it;
                    minz_it = it;
                }
                if(it->getZ() > maxz_point.getZ()) {
                    maxz_point = *it;
                    maxz_it = it;
                }
            }
            // Compute the squared distances for the three pairs of points
            float dist2x = (maxx_point - minx_point) * (maxx_point - minx_point);
            float dist2y = (maxy_point - miny_point) * (maxy_point - miny_point);
            float dist2z = (maxz_point - minz_point) * (maxz_point - minz_point);

            // Pick the pair (min, max) of points most distant
            Iterator min = minx_it;
            Iterator max = maxx_it;
            if(dist2y > dist2x && dist2y > dist2z) {
                max = maxy_it;
                min = miny_it;
            }
            if(dist2z > dist2x && dist2z > dist2y) {
                max = maxz_it;
                min = minz_it;
            }
            return std::make_pair(min, max);
        }

        // This methods find the minimum area rectangle in the XY plain containing the points
        template <typename Iterator>
        inline static float min_area_rectangle(Iterator begin, Iterator end, Point2D& c, std::pair<Point2D, Point2D> out) {
            using ValueType = typename std::iterator_traits<Iterator>::value_type;

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
        static float sq_dist_point_segment(Point3D a, Point3D b, Point3D c);

        // Computer closest points C1 and C2 of S1(s) = P1 + s*(Q1-P1)
        // and S2(t) = P2 + t*(Q2-P2), returning s and t. Function
        // result is squared distance between S1(s) and S2(t)
        static float closest_point_segment_segment(Point3D p1, Point3D q1, Point3D p2, Point3D q2, float& s, float& t, Point3D& c1, Point3D& c2);
    };
}

#endif