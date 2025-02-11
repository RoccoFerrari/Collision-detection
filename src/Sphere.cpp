#include "../include/Sphere.hh"
#include <cmath>

namespace Geometry {
    Sphere::Sphere(Point3D c, float r) {
        this->center = c;
        this->radius = r;
    }
    bool Sphere::sphere_sphere_intersection(const Sphere& other) const {
        Point3D d = this->center - other.center;
        float dist2 = d * d;
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = this->radius + other.radius;
        return dist2 <= radiusSum * radiusSum;
    }

    // Compute indices to the most separated points of the six points
    // defining the AABB encompassing the point set. Return these as min and max.
    void Sphere::most_separated_points_on_AABB(int& min, int& max, std::vector<Point3D> points) const {
        int n = points.size();
        int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
        // First find most extreme points along principal axes
        for(int i = 0; i < n; ++i) {
            if(points[i].getX() < points[minx].getX())
                minx = i;
            if(points[i].getX() > points[maxx].getX())
                maxx = i;
            if(points[i].getY() < points[miny].getY())
                miny = i;
            if(points[i].getY() > points[maxy].getY())
                maxy = i;
            if(points[i].getZ() < points[minz].getZ())
                minz = i;
            if(points[i].getZ() < points[maxz].getZ())
                maxz = i;
        }

        // Compute the squared distances for the three pairs of points
        float dist2x = (points[maxx] - points[minx]) * (points[maxx] - points[minx]);
        float dist2y = (points[maxy] - points[miny]) * (points[maxy] - points[miny]);
        float dist2z = (points[maxz] - points[minz]) * (points[maxz] - points[minz]);

        // Pick the pair (min, max) of points most distant
        min = minx;
        max = maxx;
        if(dist2y > dist2x && dist2y > dist2z) {
            max = maxy;
            min = miny;
        }
        if(dist2z > dist2x && dist2z > dist2y) {
            max = maxz;
            min = minz;
        }
    }

    void Sphere::sphere_from_distant_points(std::vector<Point3D> points) {
        // Find the most separeted point pair defining the encompassing AABB
        int min, max;
        most_separated_points_on_AABB(min, max, points);

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

    void Sphere::ritter_sphere(Sphere& sphere, std::vector<Point3D> points) {
        int n = points.size();
        // Get sphere encompassing two approximately most distant points
        sphere.sphere_from_distant_points(points);

        // Grow sphere to include all points
        for(int i = 0; i < n; ++i)
            sphere.update_sphere_with_outer_point(points[i]);
    }
}