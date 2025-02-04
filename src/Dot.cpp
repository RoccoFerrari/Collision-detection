#include "../include/Dot.hh"

namespace Geometry {
    // Constructors
    Dot::Dot(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Dot::Dot(const Dot& other) {
        this->x = other.x;
        this->y = other.y;
    }

    // Operator =
    Dot& Dot::operator=(const Dot& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    // Getter methods
    double Dot::getX() const {
        return this->x;
    }
    double Dot::getY() const {
        return this->y;
    }
    // Setter methods
    void Dot::setX(int x) {
        this->x = x;
    }
    void Dot::setY(int y) {
        this->y = y;
    }
}
