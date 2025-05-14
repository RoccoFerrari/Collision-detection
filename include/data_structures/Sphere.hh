#ifndef SPHERE_HH
#define SPHERE_HH
#include <iterator>
#include <cmath>
#include "../Point3D.hh"
#include "../include/Matrix.hh"
#include "../include/GeometricUtils.hh"

namespace Geometry {
    // Region R = {(x, y, y) | (x - c.x)^2 + (y - c.y)^2 + (z - c.z)^2 <= r^2}

    /**
     * @class Sphere.
     * @brief Sphere-shaped bounding box. Its region is:
     * $$
     * R = \{ \; (x,y,z) \; | \; (x - c.x)^2+(y-c.y)^2+(z-c.z)^2 \le r^2 \}
     * $$
     */

    class Sphere {
    private:
    
        /**
         * @brief center point of `Sphere` object.
         * @param center 
         */
        Point3D center;

        /**
         * @brief Radius of the sphere.
         * @param radius 
         */
        float radius;

    public:

        /**
         * @brief Support method for computing intersections.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.
         * @param begin starting iterator.
         * @param end ending iterator.
         * @return none. 
         */
        template <typename Iterator>
        inline void sphere_from_distant_points(Iterator begin, Iterator end) {

            // Find the most separeted point pair defining the encompassing AABB
            std::pair<Iterator, Iterator> min_max = GeometryUtils::most_separated_points_on_AABB(begin, end);

            auto it_min = min_max.first;
            auto it_max = min_max.second;

            // Set up sphere to just encompass these two points
            if (it_min != end && it_max != end) {
                this->center = (*it_min + *it_max) * 0.5f;
                this->radius = (*it_max - this->center) * (*it_max - this->center);
                this->radius = sqrt(this->radius);
            } else {
                // Not enough points
                this->center = Point3D(0.0f, 0.0f, 0.0f);
                this->radius = 0.0f;
            }
        }

        /**
         * @brief Support method that update the perimeter of the sphere with an outer point: given sphere `this` and point `p`, update `this` to just encompass `p`.
         * @param point Point which update the sphere's perimeter
         * @return none. 
         */
        void update_sphere_with_outer_point(Point3D& point);

        // Eigen sphere uses matrix rotation to approximate a more accurated bounding sphere

        /**
         * @brief Method that creates an Eigen sphere.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.
         * @param begin starting iterator.
         * @param end ending iterator.
         * @return none. 
         */
        template <typename Iterator>
        inline void eigen_sphere(Iterator begin, Iterator end) {
            Matrix m, v;

            // Compute the covariance matrix m
            m.covariance_matrix(begin, end);
            // Decompose it into eigenvectors (in v) and eigenvalues (in m)
            Matrix::jacobi(m, v);

            // Find the component with largest magnitude eigenvalue (largest spread)
            Point3D e;
            int maxc = 0;
            float maxf, maxe = abs(m[0][0]);
            if((maxf = abs(m[1][1])) > maxe) 
                maxc = 1, maxe = maxf;
            if((maxf = abs(m[2][2])) > maxe)
                maxc = 2, maxe = maxf;
            e[0] = v[0][maxc];
            e[1] = v[1][maxc];
            e[2] = v[2][maxc];

            // Find the most extreme points along direction 'e'
            auto min_max = GeometryUtils::extreme_points_along_direction(e, begin, end);
            Point3D minpt = *min_max.first;
            Point3D maxpt = *min_max.second;
            float dist = sqrt((maxpt - minpt) * (maxpt - minpt));
            this->radius = dist * 0.5f;
            this->center = (minpt + maxpt) * 0.5f;
        }
        
        /**
         * @name Constructors.
         * @{
         */

            /**
                 * @brief Default constructor that sets the `Sphere`'s center's coordinates to X = 0, Y = 0 and Z = 0 and radius of size 1. It accepts 0, 1 or 2 arguments and sets the center to the `Point3D`'s coordinate and the radius' length to the value passed to the constructor.
                 * @param c `Point3D` that represent the center.
                 * @param r Radius from the center.
                 ```
                // Example:
                Point3D P(9,8,7);
                Sphere a;
                Sphere b (P); 
                Sphere c (P,10);
                ```
                */
            Sphere(Point3D c = {}, float r = 1);

        /// @}

        /**
         * @name Getters and Setters
         * @{
         */

            /**
             * @brief Method that returns a `float` value: center `Point3D` object.
             * @return `float` value.
             */
            Point3D getCenter() const ;

            /**
             * @brief Method that returns a `float` value: the radius of the object.
             * @return `float` value.
             */
            float getRadius() const ;

        /// @}

        bool test_sphere_sphere_intersection(const Sphere& other) const ;

        /**
         * @brief Method that creates a Ritter sphere: it is an approximate bounding sphere but quite inexpensive.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.
         * @param begin starting iterator.
         * @param end ending iterator.
         * @return none. 
         */
        template <typename Iterator>
        inline void ritter_sphere(Iterator begin, Iterator end) {
            // Get sphere encompassing two approximately most distant points
            this->sphere_from_distant_points(begin, end);

            // Grow sphere to include all points
            for(; begin != end; ++begin)
                this->update_sphere_with_outer_point(*begin);
        }

        /**
         * @brief Method that creates a Ritter Eigen sphere: is an approximate bounding sphere. It uses matrix transforms for a better approximation.
         * @tparam `Iterator` Type that represent the Iterators of a container which supports them.
         * @param begin starting iterator.
         * @param end ending iterator.
         * @return none. 
         */
        template <typename Iterator>
        inline void ritter_eigen_sphere(Iterator begin, Iterator end) {
            // Start with sphere from maximum spread
            this->eigen_sphere(begin, end);

            // Grow sphere to include all points
            for(; begin != end; ++begin) 
                this->update_sphere_with_outer_point(*begin);
    
        }

    };
}

#endif