// Guard against multiple insertions
#ifndef POINT_3D_HH
#define POINT_3D_HH

namespace Geometry {
    class Point3D {
    private:
        double x;
        double y;
        double z;
    public:
        // Constructors
        Point3D(double x = 0.0, double y = 0.0, double z = 0.0);
        Point3D(const Point3D& other);
        ~Point3D() = default;

        // Operator =
        Point3D& operator=(const Point3D& other);

        // Getter methods
        double getX() const;
        double getY() const;
        double getZ() const;
        // Setter methods
        void setX(int x);
        void setY(int y);
        void setZ(int z);

        // Operation between Dots
        // Sum
        Point3D operator+(const Point3D& other) const;
        Point3D operator-(const Point3D& other) const;
        void operator+=(const Point3D& other);
        // Scalar product
        double operator*(const Point3D& other) const;
        // Cross product
        static Point3D cross3D(const Point3D& p1, const Point3D& p2);
        // Scalar Triple Product
        double stp3D(const Point3D& a, const Point3D& b, const Point3D& c);
    };
}

#endif