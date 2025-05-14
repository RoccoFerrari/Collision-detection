#ifndef ORIENTED_BOUNDING_BOX_HH
#define ORIENTED_BOUNDING_BOX_HH
#include "../Point3D.hh"
#include <array>

/*
    OBB (Oriented Bounding Box), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and    testing only those whose OBB of the figures are intersected. The differences between AABB and OBB are that OBBs are oriented dipending
    on the object they are refered to, while AABB are oriented always by the axes.
*/
namespace Geometry {

    /**
     * @class OBB.
     * @brief Oriented Bounding Box (OBB), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and testing only those whose OBB of the figures are intersected. The differences between AABB and OBB are that OBBs are oriented dipending on the object they are refered to, while AABB are oriented always by the axes. Its region is:
     * $$
     * R = \{ \; x \; | \; x = \; c \; + u[0] \cdot r + u[1] \cdot s \;+ u[2] \cdot t \;\}, \;|r| \le e[0], \; |s| \le e[1], \; |t| \le e[2]   
     * $$
     */
    class OBB {
    private:

        /**
         * @brief center point of `OBB` object.
         * @param center 
         */
        Point3D center;

        /**
         * @brief `std::array<Point3D, 3>` which represent the local x, y, z axes.
         * @param radius 
         */
        std::array<Point3D, 3> local_axes;

        /**
         * @brief Positive halfwidth extends of OBB along each axis.
         * @param halfwidth 
         */
        Point3D halfwidth;

    public:
        /**
         * @name Constructors.
         * @{
         */

            /**
             * @brief Default constructor that sets the `OBB`'s center's coordinates to X = 0, Y = 0 and Z = 0 and halfwidth of size 1. It accepts 0, 1, 2, 3 or 4 arguments and sets the center to the `Point3D`'s coordinate and the radius' length to the value passed to the constructor. Finally, it sets its axes refered to the object bounded. 
             * @param center `Point3D` that represent the center.
             * @param local_x Versor for x-coordinate.
             * @param local_y Versor for y-coordinate.
             * @param local_z Versor for z-coordinate.
             * @param halfwidth Positive halfwidth extends of OBB along each axis.
             ```
            // Example:
            Point3D C(9,8,7);
            Point3D X(9,8,7);
            Point3D Y(1,2,3);
            Point3D Z(9,8,7);
            Point3D H(9,8,7);
            OBB a;
            OBB b (C); 
            OBB c (C,X);
            OBB d (C,X,Y);
            OBB e (C,X,Y,Z);
            OBB f (C,X,Y,Z,H);
            ```
            */
            OBB(Point3D center = {}, Point3D local_x = {}, Point3D local_y = {}, Point3D local_z = {}, Point3D halfwidth = {1,1,1});

        /// @}

        /**
         * @brief Test that evaluates the instersaction between two `OBB`. It returns a boolean value: `true` if the two `OBB` are intersecting and `false` otherwise. It is possible to show that at most 15 of these separating axes must be tested to correctly determine the OBB overlap status. These axes correspond to the three coordinate axes of A, the three coordinate axes of B, and the nine axes perpendicular to an axis from each. If the boxes fail to overlap on any of the 15 axes, they are not intersecting. If no axis provides this early out, it follows that the boxes must be overlapping.
         * @param other `OBB` object.
         * @return Returns a boolean value.
         */
        bool test_OBB_OBB_intersection(const OBB& other) const ;
    };
}

#endif