// Guard against multiple insertions
#ifndef POINT_2D_HH
#define POINT_2D_HH

namespace Geometry {
    class Point2D {
    private:
        float coordinates[2];
    public:
        // Constructors
        Point2D(float x = 0.0, float y = 0.0);
        Point2D(const Point2D& other);
        ~Point2D() = default;

        // Operator =
        Point2D& operator=(const Point2D& other);

        // Getter methods
        float getX() const;
        float getY() const;
        // Setter methods
        void setX(int x);
        void setY(int y);

        // Operation between Dots
        // Sum
        Point2D operator+(const Point2D& other) const;
        Point2D operator-(const Point2D& other) const;
        void operator+=(const Point2D& other);
        // Operator[]
        float& operator[](int index);
        const float& operator[](int index) const;
        // Scalar product
        float operator*(const Point2D& other) const;
        // Cross product
        float cross2D(const Point2D& p1) const ;
        // Scalar Triple Product
        float stp2D(const Point2D& b, const Point2D& c) const ;
    };
}

#endif