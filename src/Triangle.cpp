#include "Point.hh"
#include "Triangle.hh"
#include <cmath>
#include <stdexcept>

namespace Geometry {
    class Triangle : public Shape2D {
    private:
        // Vertices
        Point a, b, c;
    public:
        // Constructors
        Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3) : a(v1), b(v2), c(v3) {}
        virtual ~Triangle() override = default;

        // Operations with triangles
        double Triangle::getArea() const {
            double s = (getPerimeter() / 2);
            return std::sqrt(s * (s - getDistance(a, b)) * (s - getDistance(b, c)) * (s - getDistance(c, a)));
        }
        virtual double getPerimeter() const {
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
            Point v0 = b - a, v1 = c - a, v2 = p - a;
            double d00 = v0 * v1;
            double d11 = v1 * v1;
            double d01 = v0 * v1;
            double d20 = v2 * v0;
            double d21 = v2 * v0;
            float denom = d00 * d11 - d01 * d01;
            if (denom != 0) {
                v = (d11 * d20 - d01 * d21) / denom;
                w = (d00 * d21 - d01 * d20) / denom;
                u = 1.0 - v - w;
            } else throw std::invalid_argument("'Denom' is equal to 0");
        }
    };

}