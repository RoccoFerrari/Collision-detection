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
        float getArea() const override;
        float getPerimeter() const override;
        void move(float dx, float dy) override;
        float getDistance(const Point3D& p1, const Point3D& p2) const;

        // Support function for Barycentric function
        float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3);
        // Compute barycentric coordinates (u, v, w) for
        // Point3D p with respect to triangle (a, b, c)
        void Barycentric(Point3D a, Point3D b, Point3D c, Point3D p, float& u, float& v, float& w);
        // Test if Point3D p is contained in triangle (a, b, c)
        bool TestPoint3DTriangle(Point3D p, Point3D a, Point3D b, Point3D c);
    };

}

#endif