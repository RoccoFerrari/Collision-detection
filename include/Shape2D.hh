#ifndef SHAPE_2D_HH  // Usa un nome univoco
#define SHAPE_2D_HH

namespace Geometry {

    class Shape2D {
    public:
        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual void move(double dx, double dy) = 0;
        virtual ~Shape2D() = default;
    };

}

#endif