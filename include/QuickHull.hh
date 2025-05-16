#ifndef QUICK_HULL_HH
#define QUICK_HULL_HH
#include "Point2D.hh"
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

namespace Geometry {

    /**
     * @class QuickHull.
     * @brief Class that allows to generate a hull from a set of points.
     */
    class QuickHull {
    private:

        /**
         * @brief Support method that finds a the farthest point from a edge. It returns an `Iterator` pointing to this `Point2D`.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.`
         * @param a Point2D
         * @param b Point2D
         * @param begin starting iterator.
         * @param end ending iterator. 
         * @return `Iterator` iterator refered to the farthest point from the edge A-B.
         */
        template <typename Iterator>
        static Iterator point2D_farthest_from_edge(Point2D a, Point2D b, Iterator begin, Iterator end) {
            Point2D e = b - a;
            Point2D eperp = Point2D(-e.getY(), e.getX());

            Iterator it = begin;
            Iterator bestIndex = end;
            float maxVal = -std::numeric_limits<float>::max();
            float rightMostVal = -std::numeric_limits<float>::max();

            for(; it != end; ++it) {
                float d = ((*it - a) * eperp) / std::sqrt(eperp * eperp);
                float r = (*it - a) * e;
                if(d > maxVal || (d == maxVal && r > rightMostVal)) {
                    maxVal = d;
                    rightMostVal = r;
                    bestIndex = it;
                }
            }
            return bestIndex;
        }

        /**
         * @brief Support function that compute a cross product between 3 points
         * @param a `const Point2D&`
         * @param b `const Point2D&`
         * @param c `const Point2D&`
         * @return `float` value that represent the cross product.
         */
        static float cross_product(const Point2D& a, const Point2D& b, const Point2D& c);

        /**
         * @brief Support method that update recursively the `Point2D` hull.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.`
         * @param a Point2D
         * @param b Point2D
         * @param begin starting iterator.
         * @param end ending iterator. 
         * @param hull `vector<Point2D>&` set of the current hull of points.
         */
        template <typename Iterator>
        static void quick_hull_recursive(Point2D a, Point2D b, Iterator begin, Iterator end, std::vector<Point2D>& hull) {
            if (begin == end) 
                return;
            
            auto farthestIndex = QuickHull::point2D_farthest_from_edge(a, b, begin, end);
            if (farthestIndex == end) 
                return;
            
            Point2D c = *farthestIndex;

            std::vector<Point2D> leftSet, rightSet;
            for (Iterator it = begin; it != end; ++it) {
                if (cross_product(a, c, *it) > 0) 
                    leftSet.push_back(*it);
                if (cross_product(c, b, *it) > 0) 
                    rightSet.push_back(*it);
            }

            QuickHull::quick_hull_recursive(a, c, leftSet.begin(), leftSet.end(), hull);
            hull.push_back(c);
            QuickHull::quick_hull_recursive(c, b, rightSet.begin(), rightSet.end(), hull);
        }

    public:

        /**
         * @brief Main method that update recursively the `Point2D` hull. It returns a `vector<Point2D>` that represents the computed `Point2D` hull.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.`
         * @param begin starting iterator.
         * @param end ending iterator.
         * @return `vector<Point2D>` `Point2D` hull set.
         */
        template <typename Iterator>
        static std::vector<Point2D> quick_hull(Iterator begin, Iterator end) {
            using PointType = typename std::iterator_traits<Iterator>::value_type;
            auto distance = std::distance(begin, end);

            if (distance == 0) // Handle n = 0
                return {}; // Return empty vector
            
            if (distance == 1) // Handle n = 1
                return {*begin};
            
            if (distance == 2) // Handle n = 2
                return {*begin, *std::next(begin)};

            // Finds min and max x-coordinate points
            Iterator minIt = begin;
            Iterator maxIt = begin;
            for (Iterator it = begin; it != end; ++it) {
                if (it->getX() < minIt->getX())
                    minIt = it;
                if (it->getX() > maxIt->getX())
                    maxIt = it;
            }

            PointType a = *minIt;
            PointType b = *maxIt;

            std::vector<PointType> pointsCopy;
            for (Iterator it = begin; it != end; ++it) 
                pointsCopy.push_back(*it);

            // Swaps min and max with first 2 elements
            auto firstIt = pointsCopy.begin();
            auto secondIt = std::next(firstIt);
            std::iter_swap(firstIt, std::find(pointsCopy.begin(), pointsCopy.end(), a));
            std::iter_swap(secondIt, std::find(std::next(pointsCopy.begin()), pointsCopy.end(), b));

            // Divides Point2Ds into 2 sets
            std::vector<PointType> upperSet, lowerSet;
            for (auto it = std::next(std::next(pointsCopy.begin())); it != pointsCopy.end(); ++it) {
                if (QuickHull::cross_product(pointsCopy[0], pointsCopy[1], *it) > 0) 
                    upperSet.push_back(*it);
                else if (QuickHull::cross_product(pointsCopy[0], pointsCopy[1], *it) < 0) 
                    lowerSet.push_back(*it);
            }

            // Builds the convex hull recursively
            std::vector<PointType> hull;
            hull.push_back(pointsCopy[0]);

            QuickHull::quick_hull_recursive(pointsCopy[0], pointsCopy[1], upperSet.begin(), upperSet.end(), hull);

            hull.push_back(pointsCopy[1]);

            // Reverse lower set and call recursive function.
            std::reverse(lowerSet.begin(), lowerSet.end()); 
            QuickHull::quick_hull_recursive(pointsCopy[1], pointsCopy[0], lowerSet.begin(), lowerSet.end(), hull);

            return hull;
        }
    };
}
#endif
