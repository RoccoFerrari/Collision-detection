// Guard against multiple insertions
#ifndef POINT_3D_HH
#define POINT_3D_HH
#include <stdexcept>
#include "Point2D.hh"

namespace Geometry {
    /**
     * @class Point3D.
     * @brief Class that handles 3 dimensions points.
     */
    class Point3D : public Point2D{
    private:
    /**
     * @brief `std::array<float, 3>` three dimension array which represents X and Y coordinates.
     * @param coordinate_z.
     */
        float coordinate_z;
    public:
        /**
         * @name Constructors.
         * @{
         */
            /**
             * @brief Default constructor that sets the coordinates to X = 0, Y = 0 and Z = 0. It accepts 0, 1, 2 or 3 arguments and sets their coordinates to the value passed to the constructor.
             * @param x Coordinate X.
             * @param y Coordinate Y.
             * @param z Coordinate Z.
             ```
             // Example:
             Point3D a; // a = (0, 0, 0)
             Point3D b (1); // b = (1, 0, 0)
             Point3D c (1,2); // c = (1, 2, 0)
             Point3D d (1,2,3); // c = (1, 2, 3)
             ```
             */
            Point3D(float x = 0.0, float y = 0.0, float z = 0.0);

            /**
             * @brief Copy constructor that sets the coordinates of the current object with the coordinates of the `Point3D` object passed as argument.
             * @param other `Point3D` object.
             ```
             // Example:
             Point3D a(1,2);
             Point3D b(a);
             ```
             */
            Point3D(const Point3D& other);

            /**
             * @brief Copy constructor that sets the coordinates X and Y of the current object with the coordinates X and Y of the `Point2D` object passed as argument, then is added a Z coordinate to convert the object into `Point3D`.
             * @param other `Point2D` object.
             ```
             // Example:
            Point3D a(1,2);
            Point3D b(a);
             ```
             */
            Point3D(const Point2D& other, float z);
        /// @}

        /**
         * @brief Default Destructor
         */
        ~Point3D() = default;

        /**
         * @name Operator(s) ovreloading
         * @{
         */

            /**
             * @brief Overloading of the `operator=` operator. It accept a `Point3D` object as argument and returns a reference to a `Point3D` object. This method allows assignement operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b = a;
             ```
             * @param other Point3D object.
             * @return Returns the initialised object with other's value(s).
             */
            Point3D& operator=(const Point3D& other);

            /**
             * @brief Overloading of the `operator+` operator. It accept a `Point3D` object as argument and returns a `Point3D` object. This method allows sum operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b(3,4,5);
             Point3D c = a + b;
             ```
             * @param other Point3D object.
             * @return Returns Point3D object.
             */
            Point3D operator+(const Point3D& other) const;

            /**
             * @brief Overloading of the `operator-` operator. It accept a `Point3D` object as argument and returns a `Point3D` object. This method allows subtraction operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b(3,4,5);
             Point3D c = a - b;
             ```
             * @param other Point3D object.
             * @return Returns Point3D object.
             */
            Point3D operator-(const Point3D& other) const;

            /**
             * @brief Overloading of the `operator-` operator. It accept a `float` scalar as argument and returns a `Point3D` object. This method allows division operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             float b = 3.0f;
             Point3D c = a/b;
             ```
             * @param scalar float argument.
             * @return Returns Point3D object.
             */
            Point3D operator-(float scalar) const;

            /**
             * @brief Overloading of the `operator+=` operator. It accept a `Point3D` object as argument and returns none. This method allows self-sum operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b(3,4,5);
             a += b;
             ```
             * @param other `Point3D` object.
             * @return none.
             */
            void operator+=(const Point3D& other);

            /**
             * @brief Overloading of the `operator[]` operator (non-const variant). It accept a `int` value and returns a `float` value: the value `0` represents the x-coordinte; `1` represents the y-coordinate; and `2` represents the z-coordinates. This method allows index, read and (over)write operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             float x = a[0];
             float y = a[1];
             float z = a[2];

             a[0] = a[1];
             ```
             * @param index int value.
             * @return `float` value which represent the selected coordinate.
             */
            float& operator[](int index);

            /**
             * @brief Overloading of the `operator[]` operator (const variant). It accept a `int` value and returns a `float` value: the value `0` represents the x-coordinte; `1` represents the y-coordinate; and `2` represents the z-coordinates. This method allows index and only read operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             float x = a[0];
             float y = a[1];
             float z = a[2];
             ```
             * @param other Point3D object.
             * @return `float` value which represent the selected coordinate.
             */
            const float& operator[](int index) const;

            /**
             * @brief Overloading of the `operator*` operator. It accept a `Point3D` object as argument and returns a `float` value. This method allows scalar product between two points operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b(3,4,5);
             float c = a * b;
             ```
             * @param other `Point3D` argument.
             * @return Returns `float` value.
             */
            float operator*(const Point3D& other) const;

            /**
             * @brief Overloading of the `operator*` operator. It accept a `float` scalar as argument and returns a `Point3D` object. This method allows product operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             float b = 3.0f;
             Point3D c = a * b;
             ```
             * @param scalar float argument.
             * @return Returns Point3D object.
             */
            Point3D operator*(float scalar) const;

            /**
             * @brief Overloading of the `operator*=` operator. It accept a `Point3D` object as argument and returns none. This method allows self-sum operations such as:
             ```
             // Example:
             Point3D a(1,2,3);
             Point3D b(3,4,5);
             a += b;
             ```
             * @param other `Point3D` object.
             * @return none.
             */
            Point3D& operator*=(float scalar);

        /// @}

        /**
         * @name Getters and Setters
         * @{
         */
            /**
             * @brief Method that returns a `float` value: the z-coordinate of the object.
             * @return `float` value.
             */
            float getZ() const;
            
            /**
             * @brief Method that sets a the z-coordinate of the object with the value passed as argument.
             * @param `float` value.
             */
            void setZ(float z);

        /// @}
        
        /**
         * @brief Method that returns a float value wich represent the cross product between two points.
         * @param p1 `Point3D` object.
         * @return `float` value.
         */
        static Point3D cross3D(const Point3D& p1, const Point3D& p2);
        
        /**
         * @brief Method that returns a float value wich represent the Scalar Triple Product (STP) between three points. Geometrically, corresponds to the volume of a parallelepiped formed by three indipendet vectors a, b, c
         * @param b `Point3D` object.
         * @param c `Point3D` object.
         * @return `float` value.
         */
        float stp3D(const Point3D& b, const Point3D& c);
    };
}

#endif