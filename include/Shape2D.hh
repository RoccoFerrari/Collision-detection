#ifndef SHAPE_2D_HH  // Usa un nome univoco
#define SHAPE_2D_HH

namespace Geometry {

    class Shape2D {
    public:
        virtual float getArea() const = 0;
        virtual float getPerimeter() const = 0;
        virtual void move(float dx, float dy) = 0;
        virtual ~Shape2D() = default;
    };

}

#endif