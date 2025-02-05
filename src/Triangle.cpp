#include "../include/Point.hh"
#include "../include/Triangle.hh"
#include <cmath>

namespace Geometry {

    // Constructors
    Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3) : a(v1), b(v2), c(v3) {}
    // Operations with triangles
    double Triangle::getArea() const {
        double s = (getPerimeter() / 2);
        return std::sqrt(s * (s - getDistance(a, b)) * (s - getDistance(b, c)) * (s - getDistance(c, a)));
    }
    double Triangle::getPerimeter() const {
        return getDistance(a, b) + getDistance(b, c) + getDistance(c, a);
    }
    void Triangle::move(double dx, double dy) {
        a.setX(a.getX() + dx);
        a.setY(a.getY() + dy);
        b.setX(b.getX() + dx);
        b.setY(a.getY() + dy);
        c.setX(c.getX() + dx);
        c.setY(c.getY() + dy);
    }
    double Triangle::getDistance(const Point& p1, const Point& p2) const {
        return std::sqrt(std::pow(p1.getX() - p2.getX(), 2) + std::pow(p1.getY() - p2.getY(), 2));
    }
    
    // Compute barycentric coordinates (u, v, w) for
    // point p with respect to triangle (a, b, c)
    void Triangle::Barycentric(Point a, Point b, Point c, Point p, double& u, double& v, double& w) {
        // Unnormalized triangle normal
        Point m = Point::Cross(b - a, a - c);
        // Nominators and one-over-denominator for u and v ratios
        double nu, nv, ood;
        double x = std::abs(m.getX()), y = std::abs(m.getY()), z = std::abs(m.getZ());
        // Computes areas in plane of largest projection
        if(x >= y && x>=z) {
            // x is largest, project to the yz plane
            nu = TriArea2D(p.getY(), p.getZ(), b.getY(), b.getZ(), c.getY(), c.getZ()); // Area of PBC in yz plane
            nv = TriArea2D(p.getY(), p.getZ(), c.getY(), c.getZ(), a.getY(), a.getZ()); // Area of PCA in yz plane
            ood = 1.0 / m.getX();                                                       // 1/(2*area of ABC in yz plane)
        } else if (y >= x && y >= z) {
            // y is largest, project to the xz plane
            nu = TriArea2D(p.getX(), p.getZ(), b.getX(), b.getZ(), c.getX(), c.getZ()); 
            nv = TriArea2D(p.getX(), p.getZ(), c.getX(), c.getZ(), a.getX(), a.getZ()); 
            ood = 1.0 / -m.getY();  
        } else {
            // z is largest, project to the xy plane
            nu = TriArea2D(p.getX(), p.getY(), b.getX(), b.getY(), c.getX(), c.getY()); 
            nv = TriArea2D(p.getX(), p.getY(), c.getX(), c.getY(), a.getX(), a.getY()); 
            ood = 1.0 / m.getZ();
        }
        u = nu * ood;
        v = nv * ood;
        w = 1.0 -u - v;
    }
    double Triangle::TriArea2D(double x1, double y1, double x2, double y2, double x3, double y3) {
        return (x1-x2)*(y2-y3) - (x2-x3)*(y1-y2);
    }
    bool Triangle::TestPointTriangle(Point p, Point a, Point b, Point c) {
        double u, v, w;
        Barycentric(a, b, c, p, u, v, w);
        return v >= 0.0 && w >= 0.0 && (v + w) <= 1.0;
    }
}