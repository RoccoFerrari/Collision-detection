#include "../include/Point3D.hh"
#include "../include/Triangle.hh"
#include <cmath>

namespace Geometry {

    // Constructors
    Triangle::Triangle(const Point3D& v1, const Point3D& v2, const Point3D& v3) : a(v1), b(v2), c(v3) {}
    // Operations with triangles
    float Triangle::getArea() const {
        float s = (getPerimeter() / 2);
        return std::sqrt(s * (s - getDistance(a, b)) * (s - getDistance(b, c)) * (s - getDistance(c, a)));
    }
    float Triangle::getPerimeter() const {
        return getDistance(a, b) + getDistance(b, c) + getDistance(c, a);
    }
    void Triangle::move(float dx, float dy) {
        a.setX(a.getX() + dx);
        a.setY(a.getY() + dy);
        b.setX(b.getX() + dx);
        b.setY(a.getY() + dy);
        c.setX(c.getX() + dx);
        c.setY(c.getY() + dy);
    }
    float Triangle::getDistance(const Point3D& p1, const Point3D& p2) const {
        return std::sqrt(std::pow(p1.getX() - p2.getX(), 2) + std::pow(p1.getY() - p2.getY(), 2));
    }
    
    // Compute barycentric coordinates (u, v, w) for
    // Point3D p with respect to triangle (a, b, c)
    void Triangle::Barycentric(Point3D a, Point3D b, Point3D c, Point3D p, float& u, float& v, float& w) {
        // Unnormalized triangle normal
        Point3D m = Point3D::cross3D(b - a, a - c);
        // Nominators and one-over-denominator for u and v ratios
        float nu, nv, ood;
        float x = std::abs(m.getX()), y = std::abs(m.getY()), z = std::abs(m.getZ());
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
    float Triangle::TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3) {
        return (x1-x2)*(y2-y3) - (x2-x3)*(y1-y2);
    }
    bool Triangle::TestPoint3DTriangle(Point3D p, Point3D a, Point3D b, Point3D c) {
        float u, v, w;
        Barycentric(a, b, c, p, u, v, w);
        return v >= 0.0 && w >= 0.0 && (v + w) <= 1.0;
    }
}