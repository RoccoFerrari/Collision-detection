#include "../include/Dot.hh"

namespace Geometry {
    // Constructors
    Dot::Dot(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Dot::Dot(const Dot& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    // Operator =
    Dot& Dot::operator=(const Dot& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    // Getter methods
    double Dot::getX() const {
        return this->x;
    }
    double Dot::getY() const {
        return this->y;
    }
    double Dot::getZ() const {
        return this->z;
    }
    // Setter methods
    void Dot::setX(int x) {
        this->x = x;
    }
    void Dot::setY(int y) {
        this->y = y;
    }
    void Dot::setZ(int z) {
        this->z = z;
    }
}
