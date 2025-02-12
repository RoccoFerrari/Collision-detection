#include "../include/Point3D.hh"
#include <stdexcept>

namespace Geometry {
    // Constructors
    Point3D::Point3D(float x, float y, float z) {
        this->coordinates[0] = x;
        this->coordinates[1] = y;
        this->coordinates[2] = z;
    }
    Point3D::Point3D(const Point3D& other) {
        this->coordinates[0] = other.coordinates[0];
        this->coordinates[1] = other.coordinates[1];
        this->coordinates[2] = other.coordinates[2];
    }

    // Operator =
    Point3D& Point3D::operator=(const Point3D& other) {
        this->coordinates[0] = other.coordinates[0];
        this->coordinates[1] = other.coordinates[1];
        this->coordinates[2] = other.coordinates[2];
        return *this;
    }

    // Getter methods
    float Point3D::getX() const {
        return this->coordinates[0];
    }
    float Point3D::getY() const {
        return this->coordinates[1];
    }
    float Point3D::getZ() const {
        return this->coordinates[2];
    }
    // Setter methods
    void Point3D::setX(float x) {
        this->coordinates[0] = x;
    }
    void Point3D::setY(float y) {
        this->coordinates[1] = y;
    }
    void Point3D::setZ(float z) {
        this->coordinates[2] = z;
    }

    // Operation between Point3Ds
    Point3D Point3D::operator+(const Point3D& other) const {
        float newX = this->coordinates[0] + other.coordinates[0];
        float newY = this->coordinates[1] + other.coordinates[1];
        float newZ = this->coordinates[2] + other.coordinates[2];
        return Point3D(newX, newY, newZ);
    }
    Point3D Point3D::operator-(const Point3D& other) const {
        float newX = this->coordinates[0] - other.coordinates[0];
        float newY = this->coordinates[1] - other.coordinates[1];
        float newZ = this->coordinates[2] - other.coordinates[2];
        return Point3D(newX, newY, newZ);
    }
    void Point3D::operator+=(const Point3D& other) {
        this->coordinates[0] += other.coordinates[0];
        this->coordinates[1] += other.coordinates[1];
        this->coordinates[2] += other.coordinates[2];
    }
    // Overloading operator[]
    float& Point3D::operator[](int index) {
        switch (index) {
        case 0: return coordinates[0];
        case 1: return coordinates[1];
        case 2: return coordinates[2];
        default: throw std::out_of_range("Index out of range");
        }
    }

    // Overloading operator[] - const version
    const float& Point3D::operator[](int index) const {
        switch (index) {
        case 0: return coordinates[0];
        case 1: return coordinates[1];
        case 2: return coordinates[2];
        default: throw std::out_of_range("Index out of range");
        }
    }


    // Scalar/Dot product 
    float Point3D::operator*(const Point3D& other) const {
        return this->coordinates[0] * other.coordinates[0] + this->coordinates[1] * other.coordinates[1] + this->coordinates[2] * other.coordinates[2];
    }
    Point3D Point3D::operator*(float scalar) const {
        return Point3D(this->coordinates[0] * scalar, this->coordinates[1] * scalar, this->coordinates[2] * scalar);
    }
    Point3D& Point3D::operator*=(float scalar) {
        this->coordinates[0] *= scalar;
        this->coordinates[1] *= scalar;
        this->coordinates[2] *= scalar;
        return *this;
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
