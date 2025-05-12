#include "../include/Point3D.hh"

namespace Geometry {

    Point3D::Point3D(float x, float y, float z) : Point2D(x, y), coordinate_z(z) {}

    Point3D::Point3D(const Point3D& other) {
        this->setX(other.getX());
        this->setY(other.getY());
        this->setZ(other.getZ());
    }

    Point3D::Point3D(const Point2D& other, float z) : coordinate_z(z) {
        this->setX(other.getX());
        this->setY(other.getY());
    }

    Point3D& Point3D::operator=(const Point3D& other) {
        if(this != &other) {
            this->setX(other.getX());
            this->setY(other.getY());
            this->setZ(other.getZ());
        }
        return *this;
    }

    float Point3D::getZ() const {
        return this->coordinate_z;
    }
    
    void Point3D::setZ(float z) {
        this->coordinate_z = z;
    }

    Point3D Point3D::operator+(const Point3D& other) const {
        float newX = this->getX() + other.getX();
        float newY = this->getY() + other.getY();
        float newZ = this->getZ() + other.getZ();
        return Point3D(newX, newY, newZ);
    }

    Point3D Point3D::operator-(const Point3D& other) const {
        float newX = this->getX() - other.getX();
        float newY = this->getY() - other.getY();
        float newZ = this->getZ() - other.getZ();
        return Point3D(newX, newY, newZ);
    }

    Point3D Point3D::operator-(float scalar) const {
        float newX = this->getX() - scalar;
        float newY = this->getY() - scalar;
        float newZ = this->getZ() - scalar;
        return Point3D(newX, newY, newZ);
    }

    void Point3D::operator+=(const Point3D& other) {
        this->setX(other.getX() + this->getX());
        this->setY(other.getY() + this->getY());
        this->setZ(other.getZ() + this->getZ());
    }
    
    float& Point3D::operator[](int index){
        switch (index) {
            case 0: return this->coordinates[0];
            case 1: return this->coordinates[1];
            case 2: return this->coordinate_z;
            default: throw std::out_of_range("Index out of range");
        }
    }

    const float& Point3D::operator[](int index) const {
        switch (index) {
            case 0: return this->getX();
            case 1: return this->getY();
            case 2: return this->getZ();
            default: throw std::out_of_range("Index out of range");
        }
    }

    float Point3D::operator*(const Point3D& other) const {
        return this->getX() * other.getX() + this->getY() * other.getY() + this->getZ() * other.getZ();
    }

    Point3D Point3D::operator*(float scalar) const {
        return Point3D(this->getX() * scalar, this->getY() * scalar, this->getZ() * scalar);
    }

    Point3D& Point3D::operator*=(float scalar) {
        this->setX(scalar + this->getX());
        this->setY(scalar + this->getY());
        this->setZ(scalar + this->getZ());
        return *this;
    }
    
    Point3D Point3D::cross3D(const Point3D& p1, const Point3D& p2) {
        float x = p1.getY() * p2.getZ() - p1.getZ() * p2.getY();
        float y = p1.getZ() * p2.getX() - p1.getX() * p2.getZ();
        float z = p1.getX() * p2.getY() - p1.getY() * p2.getX();
        return Point3D(x, y, z);
    }
    
    float Point3D::stp3D(const Point3D& b, const Point3D& c) {
        return (*this) * Point3D(b.getY() * c.getZ() - b.getZ() * c.getY(),
                       b.getZ() * c.getX() - b.getX() * c.getZ(),
                       b.getX() * c.getY() - b.getY() * c.getX());
    }
}
