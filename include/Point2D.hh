// Guard against multiple insertions
#ifndef POINT_2D_HH
#define POINT_2D_HH

namespace Geometry {
    class Point2D {
    private:
        double x;
        double y;
    public:
        // Constructors
        Point2D(double x = 0.0, double y = 0.0);
        Point2D(const Point2D& other);
        ~Point2D() = default;

        // Operator =
        Point2D& operator=(const Point2D& other);

        // Getter methods
        double getX() const;
        double getY() const;
        // Setter methods
        void setX(int x);
        void setY(int y);

        // Operation between Dots
        // Sum
        Point2D operator+(const Point2D& other) const;
        Point2D operator-(const Point2D& other) const;
        void operator+=(const Point2D& other);
        // Scalar product
        double operator*(const Point2D& other) const;
        // Cross product
        double cross2D(const Point2D& p1) const ;
        // Scalar Triple Product
        double stp2D(const Point2D& b, const Point2D& c) const ;
    };
}

#endif