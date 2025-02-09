#include "../include/Sphere.hh"

namespace Geometry {
    Sphere::Sphere(Point3D c, float r = 0) {
        this->center = c;
        this->radius = r;
    }
    bool Sphere::sphere_sphere_interaction(const Sphere& other) const {
        Point3D d = this->center - other.center;
        float dist2 = d * d;
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = this->radius + other.radius;
        return dist2 <= radiusSum * radiusSum;
    }
}