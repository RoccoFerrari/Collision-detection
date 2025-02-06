#include "../include/AABB.hh"
#include <cmath>

namespace Geometry {
    AABB::AABB(Point3D c, float x, float y, float z) {
        this->center = c;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    bool AABB::test_AABB_intersection(const AABB& other) const {
        if(abs(this->center.getX() - other.center.getX()) > (this->x + other.x))
            return false;
        if(abs(this->center.getY() - other.center.getY()) > (this->y + other.y))
            return false;
        if(abs(this->center.getZ() - other.center.getZ()) > (this->z + other.z))
            return false;
        return true;
    }
}