#ifndef LOZENGE_HH
#define LOZENGE_HH
#include "../Point3D.hh"
#include <array>

namespace Geometry {

    /**
     * @class Lozenge.
     * @brief Bounding box that can seen as box with rounded vertices, less expensive than OBB in cases of close proximity. Its region is:
     * $$
     * R = \{ \; x \; | \; (x - [\;a + u[0] \cdot s + u[1] \cdot t \; ]\;)^2 \le \; r, \quad 0 \le \; s, t \le 1 \; \}
     * $$
     */
    class Lozenge {
    private:

        /**
         * @brief Origin.
         * @param center 
         */
        Point3D center;

        /**
         * @brief `std::array<Point3D, 2>` The two edges axes of the rectangle.
         * @param edge 
         */
        std::array<Point3D, 2> edge;
        
        /**
         * @brief Radius starting from the origin from which extends by its value.
         * @param radius 
         */
        float radius; 
    public:
        
        /**
         * @name Constructors.
         * @{
         */
            /**
             * @brief Default constructor that sets the `Lozenge`'s center's coordinates to X = 0, Y = 0 and Z = 0 and radius of size 0. It accepts 0, 1, 2 or 3 arguments and sets the object along the axis formed between the two `Point3D` with the radius' length to the value passed to the constructor.
             * @param c `Point3D` that represent the origin.
             * @param e0 `Point3D` that represent the first delimitation point.
             * @param e1 `Point3D` that represent the second delimitation point.
             * @param r radius.
             ```
             // Example:
             Point3D C(9,8,7);
             Point3D E0(5,6,7);
             Point3D E1(3,4,5);
             Lozenge a;
             Lozenge b (C); 
             Lozenge c (C,E0);
             Lozenge d (C,E0,E1);
             Lozenge e (C,E0,E1,15);
             ```
             */
            Lozenge(Point3D c = {}, Point3D e0 = {}, Point3D e1 = {}, float r = 1);

        /// @}
    };
}

#endif 