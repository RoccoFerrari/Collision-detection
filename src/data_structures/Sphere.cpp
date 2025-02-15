#include "../include/data_structures/Sphere.hh"
#include "../include/Matrix.hh"
#include "../include/GeometricUtils.hh"
#include <cmath>

namespace Geometry {
    Sphere::Sphere(Point3D c, float r) {
        this->center = c;
        this->radius = r;
    }

    Point3D Sphere::getCenter() const {
        return this->center;
    }
    float Sphere::getRadius() const {
        return this->radius;
    }

    bool Sphere::test_sphere_sphere_intersection(const Sphere& other) const {
        Point3D d = this->center - other.center;
        float dist2 = d * d;
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = this->radius + other.radius;
        return dist2 <= radiusSum * radiusSum;
    }

    void Sphere::sphere_from_distant_points(std::vector<Point3D> points) {
        // Find the most separeted point pair defining the encompassing AABB
        int min, max;
        GeometryUtils::most_separated_points_on_AABB(min, max, points);

        // Set up sphere to just encompass these two points
        this->center = (points[min] + points[max]) * 0.5f;
        this->radius = (points[max] - this->center) * (points[max] - this->center);
        this->radius = sqrt(this->radius);
    }
    // Given sphere this and point p, update s to just encompass p
    void Sphere::update_sphere_with_outer_point(Point3D& point) {
        // Compute squared distance between point and sphere center
        Point3D d = point - this->center;
        float dist2 = d * d;
        // Update only this if point p is outside it
        if(dist2 > this->radius * this->radius) {
            float dist = sqrt(dist2);
            float newRadius = (this->radius + dist) * 0.5f;
            float k = (newRadius - this->radius) / dist;
            this->radius = newRadius;
            this->center += d * k;
        }
    }

    void Sphere::ritter_sphere(std::vector<Point3D> points) {
        int n = points.size();
        // Get sphere encompassing two approximately most distant points
        this->sphere_from_distant_points(points);

        // Grow sphere to include all points
        for(int i = 0; i < n; ++i)
            this->update_sphere_with_outer_point(points[i]);
    }
    // Eigen sphere uses matrix rotation to approximate a more accurated bounding sphere
    void Sphere::eigen_sphere(std::vector<Point3D> points) {
        int n = points.size();
        Matrix m, v;

        // Compute the covariance matrix m
        m.covariance_matrix(points);
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
        int imin, imax;
        GeometryUtils::extreme_points_along_direction(e, points, &imin, &imax);
        Point3D minpt = points[imin];
        Point3D maxpt = points[imax];
        float dist = sqrt((maxpt - minpt) * (maxpt - minpt));
        this->radius = dist * 0.5f;
        this->center = (minpt + maxpt) * 0.5f;
    }
    void Sphere::ritter_eigen_sphere(Sphere& s, std::vector<Point3D> points) {
        int n = points.size();

        // Start with sphere from maximum spread
        s.eigen_sphere(points);

        // Grow sphere to include all points
        for(int i = 0; i < n; ++i) 
            s.update_sphere_with_outer_point(points[i]);
    }
}