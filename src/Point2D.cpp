#include "../include/Point2D.hh"
#include <stdexcept>

namespace Geometry {
    // Constructors
    Point2D::Point2D(float x, float y) {
        this->coordinates[0] = x;
        this->coordinates[1] = y;
    }
    Point2D::Point2D(const Point2D& other) {
        this->coordinates[0] = other.coordinates[0];
        this->coordinates[1] = other.coordinates[1];
    }

    // Operator =
    Point2D& Point2D::operator=(const Point2D& other) {
        this->coordinates[0] = other.coordinates[0];
        this->coordinates[1] = other.coordinates[1];
        return *this;
    }

    // Operator ==
    bool Point2D::operator==(const Point2D& other) {
        return (this->coordinates[0] == other.coordinates[0]) && (this->coordinates[1] == other.coordinates[1]);
    }

    // Getter methods
    float Point2D::getX() const {
        return this->coordinates[0];
    }
    float Point2D::getY() const {
        return this->coordinates[1];
    }
    // Setter methods
    void Point2D::setX(int x) {
        this->coordinates[0] = x;
    }
    void Point2D::setY(int y) {
        this->coordinates[1] = y;
    }

    // Operation between Point2Ds
    Point2D Point2D::operator+(const Point2D& other) const {
        float newX = this->coordinates[0] + other.coordinates[0];
        float newY = this->coordinates[1] + other.coordinates[1];
        return Point2D(newX, newY);
    }
    Point2D Point2D::operator-(const Point2D& other) const {
        float newX = this->coordinates[0] - other.coordinates[0];
        float newY = this->coordinates[1] - other.coordinates[1];
        return Point2D(newX, newY);
    }
    void Point2D::operator+=(const Point2D& other) {
        this->coordinates[0] += other.coordinates[0];
        this->coordinates[1] += other.coordinates[1];
    }
    // Overloading operator[]
    float& Point2D::operator[](int index) {
        switch (index) {
        case 0: return coordinates[0];
        case 1: return coordinates[1];
        default: throw std::out_of_range("Index out of range");
        }
    }

    // Overloading operator[] - const version
    const float& Point2D::operator[](int index) const {
        switch (index) {
        case 0: return coordinates[0];
        case 1: return coordinates[1];
        default: throw std::out_of_range("Index out of range");
        }
    }
    Point2D Point2D::operator/(float scalar) const {
        return Point2D(this->coordinates[0] / scalar, this->coordinates[1] / scalar);
    }
    Point2D Point2D::operator*(float scalar) const {
        return Point2D(this->coordinates[0] * scalar, this->coordinates[1] * scalar);
    }
    // Scalar product
    float Point2D::operator*(const Point2D& other) const {
        return this->coordinates[0] * other.coordinates[0] + this->coordinates[1] * other.coordinates[1];
    }
    // Cross product (vectorial product)
    float Point2D::cross2D(const Point2D& other) const {
        return this->coordinates[0] * other.coordinates[0] - this->coordinates[0] * other.coordinates[0];
    }
    // Scalar Triple Product - geometrically, corresponds to the volume of a parallelepiped
    // formed by three indipendet vectors a, b, c
    float Point2D::stp2D(const Point2D& b, const Point2D& c) const {
    return (b.coordinates[0] - this->coordinates[0]) * (c.coordinates[1] - this->coordinates[1]) - (b.coordinates[1] - this->coordinates[1]) * (c.coordinates[0] - this->coordinates[0]);
  }
}
