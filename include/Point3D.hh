// Guard against multiple insertions
#ifndef POINT_3D_HH
#define POINT_3D_HH
#include "Point2D.hh"

namespace Geometry {
    class Point3D : public Point2D{
    private:
        float coordinate_z;
    public:
        // Constructors
        Point3D(float x = 0.0, float y = 0.0, float z = 0.0);
        Point3D(const Point3D& other);
        Point3D(const Point2D& other, float z);
        ~Point3D() = default;

        // Operator =
        Point3D& operator=(const Point3D& other);

        // Getter methods
        float getZ() const;
        // Setter methods
        void setZ(float z);

        // Operation between Dots
        // Sum
        Point3D operator+(const Point3D& other) const;
        Point3D operator-(const Point3D& other) const;
        Point3D operator-(float scalar) const;
        void operator+=(const Point3D& other);

        // Operator[]
        float& operator[](int index);
        const float& operator[](int index) const;

        // Scalar product
        float operator*(const Point3D& other) const;
        Point3D operator*(float scalar) const;
        Point3D& operator*=(float scalar);
        
        // Cross product
        static Point3D cross3D(const Point3D& p1, const Point3D& p2);
        // Scalar Triple Product
        static float stp3D(const Point3D& a, const Point3D& b, const Point3D& c);
    };
}

#endif