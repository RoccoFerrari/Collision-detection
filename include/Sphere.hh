#ifndef SPHERE_HH
#define SPHERE_HH
#include "Point3D.hh"

namespace Geometry {
    // Region R = {(x, y, y) | (x - c.x)^2 + (y - c.y)^2 + (z - c.z)^2 <= r^2}
    class Sphere {
    private:
        Point3D center;
        float radius;
    public:
        Sphere(Point3D c, float r = 0);
        bool sphere_sphere_interaction(const Sphere& other) const ;
    };
}

#endif