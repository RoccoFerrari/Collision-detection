// Guard against multiple insertions
#ifndef DOT_H
#define DOT_H

namespace Geometry {
    class Dot {
    private:
        double x;
        double y;
        double z;
    public:
        // Constructors
        Dot(double x = 0.0, double y = 0.0, double z = 0.0);
        Dot(const Dot& other);
        ~Dot() = default;

        // Operator =
        Dot& operator=(const Dot& other);

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
        Dot operator+(const Dot& other) const;
        void operator+=(const Dot& other);
        // Scalar product
        double operator*(const Dot& other) const;
    };
}

#endif