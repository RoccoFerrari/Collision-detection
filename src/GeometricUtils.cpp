#include "../include/GeometricUtils.hh"

namespace Geometry {
    
    float GeometryUtils::sq_dist_point_segment(Point3D a, Point3D b, Point3D c) {
        Point3D ab = b - a, ac = c - a, bc = b - c;
        float e = ac * ab;
        // Handle cases where c projects outside ab
        if (e <= 0.0f) 
            return ac * ac;
        float f = ab * ab;
        if (e >= f) 
            return bc * bc;
        // Handle cases where c projects onto ab
        return ac * ac - e * e / f;
    }
    // Support function: clamp n to lie within the reange [min, max]
    float GeometryUtils::clamp(const float n, const float min, const float max) {
        if(n < min)
            return min;
        if(n > max)
            return max;
        return n;
    }
    
    float GeometryUtils::closest_point_segment_segment(Point3D p1, Point3D q1, Point3D p2, Point3D q2, float& s, float& t, Point3D& c1,Point3D& c2) {
        float epsilon = std::numeric_limits<float>::epsilon();
        Point3D d1 = q1 - p1; // Direction vector of segment S1
        Point3D d2 = q2 - p2; // Direction vector of segment S2
        Point3D r = p1 - p2;
        float a = d1 * d1; // Squared length of segment S1
        float e = d2 * d2; // Squared length of segment S2
        float f = d2 * r;

        // Check if either or both segments degenerate into points
        if(a <= epsilon && e <= epsilon) {
            // Both segments degenerate into points
            s = t = 0.0f;
            c1 = p1;
            c2 = p2;
            return (c1 - c2) * (c1 - c2);
        }
        if(a <= epsilon) {
            // First element degenerates into a point
            s = 0.0f;
            t = f / e; // s = 0 => t = (b*s + f) / e = f/e
            t = GeometryUtils::clamp(t, 0.0f, 1.0f);
        } else {
            float c = d1 * r;
            if(e <= epsilon) {
                // Second element degenerates into a point
                t = 0.0f;
                s = GeometryUtils::clamp(-c/a, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c/a
            } else {
                // The general nondegenerate case starts here
                float b = d1 * d2;
                float denom = a*e - b*b; // Always nonnegative

                // If segments not parallel, compute closest point on L1 to L2 and
                // clamp to segment S1. Else pick arbitrary s (here 0)
                if(denom != 0.0f)
                    s = GeometryUtils::clamp((b*f - c*e) / denom, 0.0f, 1.0f);
                else
                    s = 0.0f;
                // Copute point on L2 closest to S1(s) using
                // t = ((P1 + D1*s) - P2 * D2) / (D2 * D2) = (b*s + f) / e
                t = (b*s + f) / e;

                // If t in [0, 1] done. Else clamp t, recompute s for new value
                // of t using s = ((P2 + D2*t) - P1 * D1) / (D1 * D1) = (t*b - c) / a
                // and clamp s to [0, 1]
                float tnom = b*s + f;
                if(tnom < 0.0f) {
                    t = 0.0f;
                    s = GeometryUtils::clamp(-c/a, 0.0f, 1.0f);
                } else if(tnom > e) {
                    t = 1.0f;
                    s = GeometryUtils::clamp((b - c) / a, 0.0f, 1.0f);
                } else
                    t = tnom / e;
            }
        }
        c1 = p1 + d1 * s;
        c2 = p2 + d2 * t;
        return (c1 - c2) * (c1 - c2);
    }
} // namespace Geometry