#include "../include/GeometryUtils.hh"
#include <vector>
#include <algorithm> // Just for std::swap
#include <limits>
#include <cmath>
#include <iostream>

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
        if (n <= 0) // Handle n = 0
            return {}; // Return empty vector
        
        if (n == 1) // Handle n = 1
            return {points[0]};
        
        if (n == 2) // Handle n = 2
            return {points[0], points[1]};
        
        // Create a copy of the points to avoid modifying the original array
        std::vector<Point> pointsCopy(points, points + n);

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

        // Divides points into 2 sets
        std::vector<Point> upperSet, lowerSet;
        for (int i = 2; i < n; i++) {
            if (GeometryUtils::CrossProduct(pointsCopy[0], pointsCopy[1], pointsCopy[i]) > 0){
                std::cout << "Ordine dei punti aggiunti a upperSet: (" << pointsCopy[i].getX() << ", " << pointsCopy[i].getY() << ")" << std::endl;
                upperSet.push_back(pointsCopy[i]);}
            else if (GeometryUtils::CrossProduct(pointsCopy[0], pointsCopy[1], pointsCopy[i]) < 0){
                std::cout << "Ordine dei punti aggiunti a lowerSet: (" << pointsCopy[i].getX() << ", " << pointsCopy[i].getY() << ")" << std::endl;
                lowerSet.push_back(pointsCopy[i]);}
        }
        // Builds the convex hull recursively
        std::vector<Point> hull;
        std::cout << "Punti aggiunti a hull: (" << pointsCopy[0].getX() << ", " << pointsCopy[0].getY() << ")" << std::endl;
        hull.push_back(pointsCopy[0]);
        GeometryUtils::QuickHullRecursive(pointsCopy[0], pointsCopy[1], upperSet, hull);
        std::cout << "Punti aggiunti a hull: (" << pointsCopy[1].getX() << ", " << pointsCopy[1].getY() << ")" << std::endl;
        hull.push_back(pointsCopy[1]);

        // Reverse lower set and call recursive function.
        std::reverse(lowerSet.begin(), lowerSet.end()); 
        GeometryUtils::QuickHullRecursive(pointsCopy[1], pointsCopy[0], lowerSet, hull);
        std::cout << "Ordine finale di Hull prima di essere ritornato: " << std::endl;
        for (const auto& point : hull) {
           std::cout << "(" << point.getX() << ", " << point.getX() << ")" << std::endl;
        }
        return hull;
    }
}