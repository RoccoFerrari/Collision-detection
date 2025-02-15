#include "../include/data_structures/Capsule.hh"

namespace Geometry {
    Capsule::Capsule(Point3D s, Point3D e, float r) {
        this->start = s;
        this->end = e;
        this->radius = r;
    }
}