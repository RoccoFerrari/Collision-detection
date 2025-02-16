#ifndef LOZENGE_HH
#define LOZENGE_HH
#include "../Point3D.hh"
#include <array>

namespace Geometry {
    // Region R = { x | (x - [a + u[0]*s + u[1]*t])^2 <= r }, 0 <= s,t <= 1
    // Can seen as box with rounded vertices, less expensive than OBB in cases of close proximity
    class Lozenge {
    private:
        Point3D center; // Origin
        std::array<Point3D, 2> edge; // The two edges axes of the rectangle
        float radius; // Radius
    public:
        Lozenge(Point3D c = {}, Point3D e0 = {}, Point3D e1 = {}, float r = 1);
    };
}

#endif 