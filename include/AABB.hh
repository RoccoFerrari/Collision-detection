#ifndef AXIS_ALIGNED_BOUNDING_BOX_HH
#define AXIS_ALIGNED_BOUNDING_BOX_HH
#include "Point3D.hh"
#include <vector>

/*
    AABB (Axis-Aligned Bounding Box), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and    testing only those whose AABB of the figures are intersected
*/

    namespace Geometry {
        class AABB {
        private:
            Point3D center; // center point of AABB
            float x; // radius extends (rx, ry, rz)
            float y;
            float z;
        public:
            AABB(Point3D c, float x = 0, float y = 0, float z = 0);
            bool test_AABB_intersection(const AABB& other) const ;
        };
    }

#endif