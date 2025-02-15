#include "../include/data_structures/Lozenge.hh"

namespace Geometry {
    Lozenge::Lozenge(Point3D c, Point3D e0, Point3D e1, float r) {
        this->center = c;
        this->edge[0] = e0;
        this->edge[1] = e1;
        this->radius = r;
    }
}