#include "../include/data_structures/OBB.hh"
#include "../include/Matrix.hh"
#include <cmath>
#include <limits>

namespace Geometry {
    OBB::OBB(Point3D center, Point3D local_x, Point3D local_y , Point3D local_z, Point3D halfwidth) {
        this->center = center;
        this->local_axes[0] = local_x;
        this->local_axes[1] = local_y;
        this->local_axes[2] = local_z;
        this->halfwidth = halfwidth;
    }

    bool OBB::test_OBB_OBB_intersection(const OBB& other) const {
        
        // Get the machine epsilon for the float type
        float epsilon = std::numeric_limits<float>::epsilon();
        float ra, rb;
        Matrix R, AbsR;

        // Compute rotation matrix expressing 'other' in 'this' 's coordinate frame
        for(int i = 0; i < 3; ++i) 
            for(int j = 0; j < 3; ++j)
                R[i][j] = this->local_axes[i] * other.local_axes[j];
        
        // Compute translation vector t
        Point3D t = other.center - this->center;
        // Bring transaltion into a's coordinate frame
        t = Point3D(t * this->local_axes[0], t * this->local_axes[2], t * this->local_axes[3]);

        // Compute common subexpressions. Add in an epsilon term to
        // counteract arithmetic errors when two edges are parallel and
        // their product is (near) null
        for(int i = 0; i< 3; ++i)
            for(int j = 0; j < 3; ++j)
                AbsR[i][j] = abs(R[i][j]) + epsilon;

        // Test axes L = A0, L = A1, L = A2
        for(int i = 0; i < 3; ++i) {
            ra = this->halfwidth[i];
            rb = other.halfwidth[0] * AbsR[i][0] + other.halfwidth[1] * AbsR[i][1] + other.halfwidth[2] * AbsR[i][2];
            if(abs(t[i]) > ra + rb)
                return false;
        }

        // Test axes L = B0, L = B1, L = B2
        for(int i = 0; i < 3; ++i) {
            ra = this->halfwidth[0] * AbsR[0][i] + this->halfwidth[1] * AbsR[1][i] + this->halfwidth[2] * AbsR[2][i];
            rb = other.halfwidth[i];
            if(abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
                return false;
        }

        // Test axes L = A0 x B0
        ra = this->halfwidth[1] * AbsR[2][0] + this->halfwidth[2] * AbsR[1][0];
        rb = other.halfwidth[1] * AbsR[0][2] + other.halfwidth[2] * AbsR[0][1];
        if(abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
            return false;

        // Test axis L = A0 x B1
        ra = this->halfwidth[1] * AbsR[2][1] + this->halfwidth[2] * AbsR[1][1];
        rb = other.halfwidth[0] * AbsR[0][2] + other.halfwidth[2] * AbsR[0][0];
        if(abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
            return false;

        // Test axis L = A0 x B2
        ra = this->halfwidth[1] * AbsR[2][2] + this->halfwidth[2] * AbsR[1][2];
        rb = other.halfwidth[0] * AbsR[0][1] + other.halfwidth[1] * AbsR[0][0];
        if(abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
            return false;

        // Test axis L = A1 x B0
        ra = this->halfwidth[0] * AbsR[2][0] + this->halfwidth[2] * AbsR[0][0];
        rb = other.halfwidth[1] * AbsR[1][2] + other.halfwidth[2] * AbsR[1][1];
        if(abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
            return false;

        // Test axis L = A1 x B1
        ra = this->halfwidth[0] * AbsR[2][1] + this->halfwidth[2] * AbsR[0][1];
        rb = other.halfwidth[0] * AbsR[1][2] + other.halfwidth[2] * AbsR[1][0];
        if(abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
            return false;

        // Test axis L = A1 x B2
        ra = this->halfwidth[0] * AbsR[2][2] + this->halfwidth[2] * AbsR[0][2];
        rb = other.halfwidth[0] * AbsR[1][1] + other.halfwidth[1] * AbsR[1][0];
        if(abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
            return false;

        // Test axis L = A2 x B0
        ra = this->halfwidth[0] * AbsR[1][0] + this->halfwidth[1] * AbsR[0][0];
        rb = other.halfwidth[1] * AbsR[2][2] + other.halfwidth[2] * AbsR[2][1];
        if(abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
            return false;

        // Test axis L = A2 x B1
        ra = this->halfwidth[0] * AbsR[1][1] + this->halfwidth[1] * AbsR[0][1];
        rb = other.halfwidth[0] * AbsR[2][2] + other.halfwidth[2] * AbsR[2][0];
        if(abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
            return false;
        
        // Test axis L = A2 x B2
        ra = this->halfwidth[0] * AbsR[1][2] + this->halfwidth[1] * AbsR[0][2];
        rb = other.halfwidth[0] * AbsR[2][1] + other.halfwidth[1] * AbsR[2][0];
        if(abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
            return false;

        // Since no separating axis is found, The OBBs must be intersecting
        return true;
    }
}