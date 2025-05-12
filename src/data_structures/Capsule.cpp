#include "../include/data_structures/Capsule.hh"
#include "../include/GeometricUtils.hh"

namespace Geometry {
    
    Capsule::Capsule(Point3D s, Point3D e, float r) {
        this->start = s;
        this->end = e;
        this->radius = r;
    }

    bool Capsule::test_capsule_sphere_intersection(const Sphere& s) const {

        // Compute (squared) distance between sphere center and capsule line segment
        float dist2 = GeometryUtils::sq_dist_point_segment(this->start, this->end, s.getCenter());
        // If (squared) distance smaller than (squared) sum of radii, they collide
        float radius_sc = s.getRadius() + this->radius;
        return dist2 <= radius_sc * radius_sc;
    }
    
    bool Capsule::test_capsule_intersection(const Capsule& other) const {

        // Compute (squared) distance between the inner structures of the capsules
        float s, t;
        Point3D c1, c2;
        float dist2 = GeometryUtils::closest_point_segment_segment(this->start, this->end, other.start, other.end, s, t, c1, c2);
        // If (squared) distance smaller than (squared sum) of radii, they collide
        float radius_cc = this->radius + other.radius;
        return dist2 <= radius * radius;
    }
}