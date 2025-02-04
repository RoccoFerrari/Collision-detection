#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include "Point.hh"
#include "Shape2D.hh"

namespace Geometry {
    class Triangle : public Shape2D {
    private:
        Point a, b, c;
    public:
        // Constructors
        Triangle(const Point& v1, const Point& v2, const Point& v3);
        ~Triangle() override = default;

        // Operations with triangles
        double getArea() const override;
        double getPerimeter() const override;
        void move(double dx, double dy) override;
        

        // Compute barycentric coordinates (u, v, w) for
        // point p with respect to triangle (a, b, c)
        void Barycentric(Point a, Point b, Point c, Point p, double& u, double& v, double& w);
        // Test if point p is contained in triangle (a, b, c)
        bool TestPointTriangle(Point p, Point a, Point b, Point c);
    };

}

#endif