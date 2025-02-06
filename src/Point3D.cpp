#include "../include/Point3D.hh"

namespace Geometry {
    // Constructors
    Point3D::Point3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point3D::Point3D(const Point3D& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    // Operator =
    Point3D& Point3D::operator=(const Point3D& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    // Getter methods
    float Point3D::getX() const {
        return this->x;
    }
    float Point3D::getY() const {
        return this->y;
    }
    float Point3D::getZ() const {
        return this->z;
    }
    // Setter methods
    void Point3D::setX(int x) {
        this->x = x;
    }
    void Point3D::setY(int y) {
        this->y = y;
    }
    void Point3D::setZ(int z) {
        this->z = z;
    }

    // Operation between Point3Ds
    Point3D Point3D::operator+(const Point3D& other) const {
        float newX = this->x + other.x;
        float newY = this->y + other.y;
        float newZ = this->z + other.z;
        return Point3D(newX, newY, newZ);
    }
    Point3D Point3D::operator-(const Point3D& other) const {
        float newX = this->x - other.x;
        float newY = this->y - other.y;
        float newZ = this->z - other.z;
        return Point3D(newX, newY, newZ);
    }
    void Point3D::operator+=(const Point3D& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }
    // Scalar product
    float Point3D::operator*(const Point3D& other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }
    // Cross product (vectorial product)
    Point3D Point3D::cross3D(const Point3D& p1, const Point3D& p2) {
        float x = p1.getY() * p2.getZ() - p1.getZ() * p2.getY();
        float y = p1.getZ() * p2.getX() - p1.getX() * p2.getZ();
        float z = p1.getX() * p2.getY() - p1.getY() * p2.getX();
        return Point3D(x, y, z);
    }
    // Scalar Triple Product - geometrically, corresponds to the volume of a parallelepiped
    // formed by three indipendet vectors a, b, c
    float Point3D::stp3D(const Point3D& a, const Point3D& b, const Point3D& c) {
        return a * Point3D(b.getY() * c.getZ() - b.getZ() * c.getY(),
                       b.getZ() * c.getX() - b.getX() * c.getZ(),
                       b.getX() * c.getY() - b.getY() * c.getX());
    }
}
