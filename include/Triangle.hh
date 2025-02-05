#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include "Point3D.hh"
#include "Shape2D.hh"

namespace Geometry {
    class Triangle : public Shape2D {
    private:
        Point3D a, b, c;
    public:
        // Constructors
        Triangle(const Point3D& v1, const Point3D& v2, const Point3D& v3);
        ~Triangle() override = default;

        // Operations with triangles
        double getArea() const override;
        double getPerimeter() const override;
        void move(double dx, double dy) override;
        double getDistance(const Point3D& p1, const Point3D& p2) const;

        // Support function for Barycentric function
        double TriArea2D(double x1, double y1, double x2, double y2, double x3, double y3);
        // Compute barycentric coordinates (u, v, w) for
        // Point3D p with respect to triangle (a, b, c)
        void Barycentric(Point3D a, Point3D b, Point3D c, Point3D p, double& u, double& v, double& w);
        // Test if Point3D p is contained in triangle (a, b, c)
        bool TestPoint3DTriangle(Point3D p, Point3D a, Point3D b, Point3D c);
    };

}

#endif