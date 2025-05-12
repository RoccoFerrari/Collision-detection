#ifndef AXIS_ALIGNED_BOUNDING_BOX_HH
#define AXIS_ALIGNED_BOUNDING_BOX_HH
#include "../Point3D.hh"
#include "../Matrix.hh"
#include <array>
#include <cmath>
#include <stdexcept>

    namespace Geometry {

        /**
         * @class AABB.
         * @brief Axis-Aligned Bounding Box (AABB), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and testing only those whose AABB of the figures are intersected
         */
        class AABB {
        private:

            /**
             * @brief center point of `AABB` object.
             * @param center 
             */
            Point3D center;

            /**
             * @brief `std::array<float, 3>` radius starting from the center point which extends along axis by `radius[0]`, `radius[1]` and `radius[2]`.
             * @param radius 
             */
            std::array<float, 3> radius;

        public:

            /**
             * @name Constructors.
             * @{
             */

                /**
                 * @brief Default constructor that sets the `AABB`'s center's coordinates to X = 0, Y = 0 and Z = 0 and radius of size 0. It accepts 0, 1, 2, 3 or 4 arguments and sets the center to the `Point3D`'s coordinate and the radius' length to the value passed to the constructor.
                 * @param c `Point3D` that represent the center.
                 * @param x Radius along x-coordinate.
                 * @param y Radius along y-coordinate.
                 * @param z Radius along z-coordinate.
                 ```
                // Example:
                Point3D P(9,8,7);
                AABB a;
                AABB b (P); 
                AABB c (P,1);
                AABB d (P,1,2);
                AABB e (P,1,2,3);
                ```
                */
                AABB(Point3D c = {}, float x = 0, float y = 0, float z = 0);

            /// @}

            /**
             * @name Operator(s) ovreloading
             * @{
             */
            
                /**
                 * @brief Overloading of the `operator[]` operator (non-const variant). It accept a `int` value and returns a `float` value: the value `0` represents the radius's x-coordinte; `1` represents the radius's y-coordinate; and `2` represents the radius's z-coordinates. This method allows index, read and (over)write operations such as:
                 ```
                // Example:
                AABB A;
                float x = A[0];
                float y = A[1];
                float z = A[2];

                A[0] = 10.4f;
                ```
                * @param other `Point3D` object.
                * @return `float` value which represent the selected coordinate.
                */
                float& operator[](int index);

                /**
                 * @brief Overloading of the `operator[]` operator (const variant). It accept a `int` value and returns a `float` value: the value `0` represents the radius's x-coordinte; `1` represents the radius's y-coordinate; and `2` represents the radius's z-coordinates. This method allows index and only read operations such as:
                 ```
                // Example:
                AABB A;
                float x = A[0];
                float y = A[1];
                float z = A[2];
                ```
                * @param index `int` value.
                * @return `float` value which represent the selected coordinate.
                */
                const float& operator[](int index) const;

            /// @}

            /**
             * @brief Test that evaluates the instersaction between two `AABB`. It returns a boolean value: `true` if the two `AABB` are intersecting and `false` otherwise.
             * @param other `AABB` object.
             * @return Returns a boolean value.
             */
            bool test_AABB_AABB_intersection(const AABB& other) const ;

            // Transform AABB A (this) by the matrix M and traslation T,
            // find maximum extends, and store result into AABB B (other)
            /**
             * @brief Transforms `this` `AABB` object by the matrix `M` and traslation `T`, finds maximum, extends, and stores result into `other` `AABB` object.
             * @param other `AABB` object.
             * @param T traslation.
             * @param other `AABB` object.
             * @return Returns a boolean value.
             */
            void update_AABB(Matrix M, float T[3], AABB& other);

        };
    }

#endif