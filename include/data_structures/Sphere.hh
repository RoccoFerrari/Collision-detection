#ifndef SPHERE_HH
#define SPHERE_HH
#include "../Point3D.hh"
#include <vector>

namespace Geometry {
    // Region R = {(x, y, y) | (x - c.x)^2 + (y - c.y)^2 + (z - c.z)^2 <= r^2}
    class Sphere {
    private:
        Point3D center;
        float radius;

    public:
        // Support methods for computing intersections
        void sphere_from_distant_points(std::vector<Point3D> points);
        void update_sphere_with_outer_point(Point3D& point);

        // Eigen sphere uses matrix rotation to approximate a more accurated bounding sphere
        void eigen_sphere(std::vector<Point3D> points);
    
        Sphere(Point3D c = {}, float r = 1);

        Point3D getCenter() const ;
        float getRadius() const ;

        bool test_sphere_sphere_intersection(const Sphere& other) const ;

        // Ritter sphere is an approximate bounding sphere. It is not optimal ma quite inexpensive.
        void ritter_sphere(std::vector<Point3D> points);
        // Ritter sphere is an approximate bounding sphere. It uses matrix transforms for a better approximation.
        static void ritter_eigen_sphere(Sphere& s, std::vector<Point3D> points);
    };
}

#endif