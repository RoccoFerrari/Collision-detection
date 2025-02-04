// Guard against multiple insertions
#ifndef POINT_HH
#define POINT_HH

namespace Geometry {
    class Point {
    private:
        double x;
        double y;
        double z;
    public:
        // Constructors
        Point(double x = 0.0, double y = 0.0, double z = 0.0);
        Point(const Point& other);
        ~Point() = default;

        // Operator =
        Point& operator=(const Point& other);

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
        Point operator+(const Point& other) const;
        Point operator-(const Point& other) const;
        void operator+=(const Point& other);
        // Scalar product
        double operator*(const Point& other) const;
        // Scalar Triple Product
        double STP(const Point& a, const Point& b, const Point& c);
    };
}

#endif