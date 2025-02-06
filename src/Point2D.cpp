#include "../include/Point2D.hh"

namespace Geometry {
    // Constructors
    Point2D::Point2D(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Point2D::Point2D(const Point2D& other) {
        this->x = other.x;
        this->y = other.y;
    }

    // Operator =
    Point2D& Point2D::operator=(const Point2D& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    // Getter methods
    float Point2D::getX() const {
        return this->x;
    }
    float Point2D::getY() const {
        return this->y;
    }
    // Setter methods
    void Point2D::setX(int x) {
        this->x = x;
    }
    void Point2D::setY(int y) {
        this->y = y;
    }

    // Operation between Point2Ds
    Point2D Point2D::operator+(const Point2D& other) const {
        float newX = this->x + other.x;
        float newY = this->y + other.y;
        return Point2D(newX, newY);
    }
    Point2D Point2D::operator-(const Point2D& other) const {
        float newX = this->x - other.x;
        float newY = this->y - other.y;
        return Point2D(newX, newY);
    }
    void Point2D::operator+=(const Point2D& other) {
        this->x += other.x;
        this->y += other.y;
    }
    // Scalar product
    float Point2D::operator*(const Point2D& other) const {
        return this->x * other.x + this->y * other.y;
    }
    // Cross product (vectorial product)
    float Point2D::cross2D(const Point2D& other) const {
        return this->x * other.y - this->y * other.x;
    }
    // Scalar Triple Product - geometrically, corresponds to the volume of a parallelepiped
    // formed by three indipendet vectors a, b, c
    float Point2D::stp2D(const Point2D& b, const Point2D& c) const {
    return (b.x - x) * (c.y - y) - (b.y - y) * (c.x - x);
  }
}
