#include "../include/data_structures/AABB.hh"
#include <cmath>
#include <stdexcept>

namespace Geometry {
    AABB::AABB(Point3D c, float x, float y, float z) {
        this->center = c;
        this->radius[0] = x;
        this->radius[1] = y;
        this->radius[2] = z;
    }

    // Overloading operator[]
    float& AABB::operator[](int index) {
        switch (index) {
        case 0: return this->radius[0];
        case 1: return this->radius[1];
        case 2: return this->radius[2];
        default: throw std::out_of_range("Index out of range");
        }
    }

    // Overloading operator[] - const version
    const float& AABB::operator[](int index) const {
        switch (index) {
        case 0: return this->radius[0];
        case 1: return this->radius[1];
        case 2: return this->radius[2];
        default: throw std::out_of_range("Index out of range");
        }
    }

    bool AABB::test_AABB_AABB_intersection(const AABB& other) const {
        if(abs(this->center.getX() - other.center.getX()) > (this->radius[0] + other.radius[0]))
            return false;
        if(abs(this->center.getY() - other.center.getY()) > (this->radius[1] + other.radius[1]))
            return false;
        if(abs(this->center.getZ() - other.center.getZ()) > (this->radius[2] + other.radius[2]))
            return false;
        return true;
    }
    // Transform AABB A (this) by the matrix M and traslation T,
    // find maximum extends, and store result into AABB B (other)
    void AABB::update_AABB(Matrix M, float T[3], AABB& other) {
        for(int i = 0; i < 3; ++i) {
            other.center[i] = T[i];
            other.radius[i] = 0.0f;
            for(int j = 0; j < 3; ++j) {
                other.center[i] += M[i][j] * this->center[j];
                other.radius[i] += abs(M[i][j]) * this->radius[j];
            }
        }
    }
}