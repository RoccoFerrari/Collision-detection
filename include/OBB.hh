#ifndef ORIENTED_BOUNDING_BOX_HH
#define ORIENTED_BOUNDING_BOX_HH
#include "Point3D.hh"

/*
    OBB (Oriented Bounding Box), is a fitting-figure box that allows you to optimize collisions by eliminating impossible ones and    testing only those whose OBB of the figures are intersected. The differences between AABB and OBB are that OBBs are oriented dipending
    on the object they are refered to, while AABB are oriented always by the axes.
*/
namespace Geometry {
    // Region R = { x | x = c + r*u[0] + s*u[1] + t*u[2] }, |r| <= e[0], |s| <= e[1], |t| <= e[2]
    class OBB {
    private:
        Point3D center;
        Point3D local_axes[3]; // Local x, y, z-axes
        Point3D halfwidth;  // Positive halfwidth extends of OBB along each axis
    public:
        OBB(Point3D center = {}, Point3D local_x = {}, Point3D local_y = {}, Point3D local_z = {}, Point3D halfwidth = {1,1,1});

        bool test_OBB_intersection(OBB& other) const ;
    };
}

#endif