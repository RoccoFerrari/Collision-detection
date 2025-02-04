#include "../include/Point.hh"

namespace Geometry {
    // Constructors
    Point::Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point::Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    // Operator =
    Point& Point::operator=(const Point& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    // Getter methods
    double Point::getX() const {
        return this->x;
    }
    double Point::getY() const {
        return this->y;
    }
    double Point::getZ() const {
        return this->z;
    }
    // Setter methods
    void Point::setX(int x) {
        this->x = x;
    }
    void Point::setY(int y) {
        this->y = y;
    }
    void Point::setZ(int z) {
        this->z = z;
    }

    // Operation between Points
    Point Point::operator+(const Point& other) const {
        double newX = this->x + other.x;
        double newY = this->y + other.y;
        double newZ = this->z + other.z;
        return Point(newX, newY, newZ);
    }
    Point Point::operator-(const Point& other) const {
        double newX = this->x - other.x;
        double newY = this->y - other.y;
        double newZ = this->z - other.z;
        return Point(newX, newY, newZ);
    }
    void Point::operator+=(const Point& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }
    // Scalar product
    double Point::operator*(const Point& other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }
    // Scalar Triple Product - geometrically, corresponds to the volume of a parallelepiped
    // formed by three indipendet vectors a, b, c
    double Point::STP(const Point& a, const Point& b, const Point& c) {
        return a * Point(b.getY() * c.getZ() - b.getZ() * c.getY(),
                       b.getZ() * c.getX() - b.getX() * c.getZ(),
                       b.getX() * c.getY() - b.getY() * c.getX());
    }
}
