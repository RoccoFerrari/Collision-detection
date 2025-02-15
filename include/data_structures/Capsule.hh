#ifndef CAPSULE_HH
#define CAPSULE_HH
#include "../Point3D.hh"

namespace Geometry {
    // Region R = { x | (x - [a + (b - a)*t])^2 <= r }, 0 <= t <= 1
    // Can seen as a cylinder
    class Capsule {
    private:
        Point3D start; // Medial line segment start point
        Point3D end; // Medial line segment end point
        float radius; // Radius
    public:
        Capsule(Point3D s = {}, Point3D e = {}, float r = 1);
    };
}

#endif 