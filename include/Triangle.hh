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
        // probably this fun is to move in another file
        void Barycentric(Point a, Point b, Point c, Point p, double& u, double& v, double& w);
    };

}

#endif