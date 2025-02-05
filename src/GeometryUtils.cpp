#include "../include/GeometryUtils.hh"
#include <vector>
#include <algorithm> // Just for std::swap
#include <limits>
#include <cmath>

namespace Geometry {
    int GeometryUtils::PointFarthestFromEdge(Point a, Point b, Point p[], int n) {
        Point e = b - a;
        Point eperp = Point(-e.getY(), e.getX(), 0);

        int bestIndex = -1;
        double maxVal = -std::numeric_limits<double>::max();
        double rightMostVal = -std::numeric_limits<double>::max();

        for(int i = 0; i < n; i++) {
            double d = ((p[i] - a) * eperp) / std::sqrt(eperp * eperp);
            double r = (p[i] - a) * e;
            if(d > maxVal || (d == maxVal && r > rightMostVal)) {
                maxVal = d;
                rightMostVal = r;
                bestIndex = i;
            }
        }
        return bestIndex;
    }
    double GeometryUtils::CrossProduct(const Point& a, const Point& b, const Point& c) {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    }
    void GeometryUtils::QuickHullRecursive(Point a, Point b, std::vector<Point>& points, std::vector<Point>& hull) {
        if (points.empty()) {
            return;
        }

        int farthestIndex = GeometryUtils::PointFarthestFromEdge(a, b, points.data(), points.size());
        if (farthestIndex == -1) {
            return;
        }
        Point c = points[farthestIndex];

        std::vector<Point> leftSet, rightSet;
        for (const Point& p : points) {
            if (CrossProduct(a, c, p) > 0) {
                leftSet.push_back(p);
            }
            if (CrossProduct(c, b, p) > 0) {
                rightSet.push_back(p);
            }
        }

        GeometryUtils::QuickHullRecursive(a, c, leftSet, hull);
        hull.push_back(c);
        GeometryUtils::QuickHullRecursive(c, b, rightSet, hull);
    }

    std::vector<Point> GeometryUtils::QuickHull(Point points[], int n) {
        if(n < 3) {
            std::vector<Point> hull(points, points + n);
            return hull;
        }

        // Finds min and max x-coordinate points
        int minIndex = 0, maxIndex = 0;
        for(int i = 1; i < n; ++i) {
            if(points[i].getX() < points[minIndex].getX()) 
                minIndex = i;
            if(points[i].getX() > points[maxIndex].getX())
                maxIndex = i;
        }

        // Swaps min and max with first 2 elements
        std::swap(points[0], points[minIndex]);
        std::swap(points[1], points[maxIndex]);

        // Divides points into 2 sets
        std::vector<Point> upperSet, lowerSet;
        for (int i = 2; i < n; i++){
            if(GeometryUtils::CrossProduct(points[0], points[1], points[i]) > 0)
                upperSet.push_back(points[i]);
            else
                lowerSet.push_back(points[i]);
        }
        // Builds the convex hull ricorsively
        std::vector<Point> hull;
        hull.push_back(points[0]);
        GeometryUtils::QuickHullRecursive(points[0], points[1], upperSet, hull);
        hull.push_back(points[1]);
        GeometryUtils::QuickHullRecursive(points[1], points[0], lowerSet, hull);

        return hull;
    }
}