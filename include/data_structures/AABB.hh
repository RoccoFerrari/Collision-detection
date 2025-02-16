#ifndef AXIS_ALIGNED_BOUNDING_BOX_HH
#define AXIS_ALIGNED_BOUNDING_BOX_HH
#include "../Point3D.hh"
#include "../Matrix.hh"
#include <vector>
#include <array>

/*
    AABB (Axis-Aligned Bounding Box), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and    testing only those whose AABB of the figures are intersected
*/

    namespace Geometry {
        class AABB {
        private:
            Point3D center; // center point of AABB
            std::array<float, 3> radius; // radius extends (rx, ry, rz)
        public:
            // Constructor
            AABB(Point3D c = {}, float x = 0, float y = 0, float z = 0);

            // Operator[]
            float& operator[](int index);
            const float& operator[](int index) const;

            // Test that evaluates the instersaction between two AABB
            bool test_AABB_AABB_intersection(const AABB& other) const ;

            // Transform AABB A (this) by the matrix M and traslation T,
            // find maximum extends, and store result into AABB B (other)
            void update_AABB(Matrix M, float T[3], AABB& other);

        };
    }

#endif