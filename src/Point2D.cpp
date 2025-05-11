#include "../include/Point2D.hh"
#include <stdexcept>

namespace Geometry {
    // Constructors
    Point2D::Point2D(float x, float y) : coordinates({x, y}) {}

    Point2D::Point2D(const Point2D& other) {
        this->setX(other.getX());
        this->setY(other.getY());
    }

    // Operator =
    Point2D& Point2D::operator=(const Point2D& other) {
        this->setX(other.getX());
        this->setY(other.getY());
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
        float newX = this->getX() + other.getX();
        float newY = this->getY() + other.getY();
        return Point2D(newX, newY);
    }
    Point2D Point2D::operator-(const Point2D& other) const {
        float newX = this->getX() - other.getX();
        float newY = this->getY() - other.getY();
        return Point2D(newX, newY);
    }
    void Point2D::operator+=(const Point2D& other) {
        this->setX(other.getX() + this->getX());
        this->setY(other.getY() + this->getY());
    }
    // Overloading operator[]
    float Point2D::operator[](int index) {
        switch (index) {
            case 0: return this->getX();
            case 1: return this->getY();
            default: throw std::out_of_range("Index out of range");
        }
    }

    // Overloading operator[] - const version
    const float& Point2D::operator[](int index) const {
        switch (index) {
            case 0: return this->getX();
            case 1: return this->getY();
            default: throw std::out_of_range("Index out of range");
        }
    }
    Point2D Point2D::operator/(float scalar) const {
        return Point2D(this->getX() / scalar, this->getY() / scalar);
    }
    Point2D Point2D::operator*(float scalar) const {
        return Point2D(this->getX() * scalar, this->getY() * scalar);
    }
    // Scalar product
    float Point2D::operator*(const Point2D& other) const {
        return this->getX() * other.getX() + this->getY() * other.getY();
    }
    // Cross product (vectorial product)
    float Point2D::cross2D(const Point2D& other) const {
        return this->getX() * other.getY() - this->getY() * other.getX();
    }
    // Scalar Triple Product - geometrically, corresponds to the volume of a parallelepiped
    // formed by three indipendet vectors a, b, c
    float Point2D::stp2D(const Point2D& b, const Point2D& c) const {
        return (b.getX() - this->getX()) * (c.getY() - this->getY()) - (b.getY() - this->getY()) * (c.getX() - this->getX());
    }
}
