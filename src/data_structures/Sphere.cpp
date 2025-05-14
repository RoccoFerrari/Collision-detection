#include "../include/data_structures/Sphere.hh"

namespace Geometry {
    Sphere::Sphere(Point3D c, float r) {
        this->center = c;
        this->radius = r;
    }

    Point3D Sphere::getCenter() const {
        return this->center;
    }
    float Sphere::getRadius() const {
        return this->radius;
    }

    bool Sphere::test_sphere_sphere_intersection(const Sphere& other) const {
        Point3D d = this->center - other.center;
        float dist2 = d * d;
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = this->radius + other.radius;
        return dist2 <= radiusSum * radiusSum;
    }

    void Sphere::update_sphere_with_outer_point(Point3D& point) {
        // Compute squared distance between point and sphere center
        Point3D d = point - this->center;
        float dist2 = d * d;
        // Update only this if point p is outside it
        if(dist2 > this->radius * this->radius) {
            float dist = sqrt(dist2);
            float newRadius = (this->radius + dist) * 0.5f;
            float k = (newRadius - this->radius) / dist;
            this->radius = newRadius;
            this->center += d * k;
        }
    }
}