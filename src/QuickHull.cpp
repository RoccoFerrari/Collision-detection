#include "../include/QuickHull.hh"
#include <vector>
#include <algorithm> // Just for std::swap
#include <limits>
#include <cmath>

namespace Geometry {
    int QuickHull::point2D_farthest_from_edge(Point2D a, Point2D b, std::vector<Point2D> p) {
        int n = p.size();
        Point2D e = b - a;
        Point2D eperp = Point2D(-e.getY(), e.getX());

        int bestIndex = -1;
        float maxVal = -std::numeric_limits<float>::max();
        float rightMostVal = -std::numeric_limits<float>::max();

        for(int i = 0; i < n; i++) {
            float d = ((p[i] - a) * eperp) / std::sqrt(eperp * eperp);
            float r = (p[i] - a) * e;
            if(d > maxVal || (d == maxVal && r > rightMostVal)) {
                maxVal = d;
                rightMostVal = r;
                bestIndex = i;
            }
        }
        return bestIndex;
    }
    float QuickHull::cross_product(const Point2D& a, const Point2D& b, const Point2D& c) {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    }
    void QuickHull::quick_hull_recursive(Point2D a, Point2D b, std::vector<Point2D>& points, std::vector<Point2D>& hull) {
        if (points.empty()) {
            return;
        }

        int farthestIndex = QuickHull::point2D_farthest_from_edge(a, b, points);
        if (farthestIndex == -1) {
            return;
        }
        Point2D c = points[farthestIndex];

        std::vector<Point2D> leftSet, rightSet;
        for (const Point2D& p : points) {
            if (cross_product(a, c, p) > 0) {
                leftSet.push_back(p);
            }
            if (cross_product(c, b, p) > 0) {
                rightSet.push_back(p);
            }
        }

        QuickHull::quick_hull_recursive(a, c, leftSet, hull);
        hull.push_back(c);
        QuickHull::quick_hull_recursive(c, b, rightSet, hull);
    }

    std::vector<Point2D> QuickHull::quick_hull(std::vector<Point2D> points) {
        int n = points.size();
        if (n <= 0) // Handle n = 0
            return {}; // Return empty vector
        
        if (n == 1) // Handle n = 1
            return {points[0]};
        
        if (n == 2) // Handle n = 2
            return {points[0], points[1]};
        
        // Create a copy of the points to avoid modifying the original array
        std::vector<Point2D> pointsCopy = points;

        // Finds min and max x-coordinate points
        int minIndex = 0, maxIndex = 0;
        for (int i = 1; i < n; ++i) {
            if (pointsCopy[i].getX() < pointsCopy[minIndex].getX())
                minIndex = i;
            if (pointsCopy[i].getX() > pointsCopy[maxIndex].getX())
                maxIndex = i;
        }

        // Swaps min and max with first 2 elements
        std::swap(pointsCopy[0], pointsCopy[minIndex]);
        std::swap(pointsCopy[1], pointsCopy[maxIndex]);

        // Divides Point2Ds into 2 sets
        std::vector<Point2D> upperSet, lowerSet;
        for (int i = 2; i < n; i++) {
            if (QuickHull::cross_product(pointsCopy[0], pointsCopy[1], pointsCopy[i]) > 0) 
                upperSet.push_back(pointsCopy[i]);
            else if (QuickHull::cross_product(pointsCopy[0], pointsCopy[1], pointsCopy[i]) < 0) 
                lowerSet.push_back(pointsCopy[i]);
        }

        // Builds the convex hull recursively
        std::vector<Point2D> hull;
        hull.push_back(pointsCopy[0]);

        QuickHull::quick_hull_recursive(pointsCopy[0], pointsCopy[1], upperSet, hull);

        hull.push_back(pointsCopy[1]);

        // Reverse lower set and call recursive function.
        std::reverse(lowerSet.begin(), lowerSet.end()); 
        QuickHull::quick_hull_recursive(pointsCopy[1], pointsCopy[0], lowerSet, hull);
        return hull;
    }
}