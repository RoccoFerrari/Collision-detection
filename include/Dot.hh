// Guard against multiple insertions
#ifndef DOT_H
#define DOT_H

namespace Geometry {
    class Dot {
    private:
        double x;
        double y;
    public:
        // Constructors
        Dot(double x = 0.0, double y = 0.0);
        Dot(const Dot& other);
        ~Dot() = default;

        // Operator =
        Dot& operator=(const Dot& other);

        // Getter methods
        double getX() const;
        double getY() const;
        // Setter methods
        void setX(int x);
        void setY(int y);
    };
}

#endif