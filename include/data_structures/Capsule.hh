#ifndef CAPSULE_HH
#define CAPSULE_HH
#include "../Point3D.hh"
#include "Sphere.hh"

namespace Geometry {

    /**
     * @class Capsule.
     * @brief Bounding box that can seen as a cylinder. Its region is:
     * $$
     * R = \{ \; x \; | \; (x - [\;a + (b - a) \cdot t \; ]\;)^2 \le \; r, \quad 0 \; \le \; t \; \le \; 1 \; \}
     * $$
     */
    class Capsule {
    private:

        /**
         * @brief Medial line segment start point.
         * @param start 
         */
        Point3D start;

        /**
         * @brief Medial line segment end point.
         * @param start 
         */
        Point3D end;

        /**
         * @brief Radius starting from the center point(s) (start/end) from which extends by its value.
         * @param radius 
         */
        float radius; 

    public:
        
        /**
         * @name Constructors.
         * @{
         */

            /**
             * @brief Default constructor that sets the `Capsule`'s center's coordinates to X = 0, Y = 0 and Z = 0 and radius of size 0. It accepts 0, 1, 2 or 3 arguments and sets the object along the axis formed between the two `Point3D` with the radius' length to the value passed to the constructor.
             * @param s `Point3D` that represent the start point.
             * @param e `Point3D` that represent the end point.
             * @param r radius.
             ```
             // Example:
             Point3D S(9,8,7);
             Point3D E(5,6,7);
             Capsule a;
             Capsule b (S); 
             Capsule c (S,E);
             Capsule d (S,E,5);
             ```
             */
            Capsule(Point3D s = {}, Point3D e = {}, float r = 1);

        /// @}

        /**
         * @brief Test that evaluates the instersaction between `Capsule` and `Sphere` objects. It returns a boolean value: `true` if the two bounding box are intersecting and `false` otherwise.
         * @param s `Sphere` object.
         * @return Returns a boolean value.
         */
        bool test_capsule_sphere_intersection(const Sphere& s) const ;
        
        /**
         * @brief Test that evaluates the instersaction between two `Capsule`. It returns a boolean value: `true` if the two `Capsule` are intersecting and `false` otherwise.
         * @param other `Capsule` object.
         * @return Returns a boolean value.
         */
        bool test_capsule_intersection(const Capsule& other) const ;
    };
}

#endif 