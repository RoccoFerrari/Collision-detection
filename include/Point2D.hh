// Guard against multiple insertions
#ifndef POINT_2D_HH
#define POINT_2D_HH
#include <array>

namespace Geometry {
    /**
     * @class Point2D.
     * @brief Class that handles 2 dimensions points.
     */
    class Point2D {
    protected:
    /**
     * @brief `std::array<float, 2>` two dimension array which represents X and Y coordinates.
     * @param coordinates.
     */
        std::array<float, 2> coordinates;
    public:
        /**
         * @name Constructors.
         * @{
         */ 

            /**
             * @brief Default constructor that sets the coordinates to X = 0 and Y = 0. It accepts 0, 1 or 2 arguments and sets their coordinates to the value passed to the constructor.
             * @param x Coordinate X.
             * @param y Coordinate Y.
             ```
             // Example:
             Point2D a; // a = (0, 0)
             Point2D b (1); // b = (1, 0)
             Point2D c (1,2); // c = (1, 2)
             ```
             */
            Point2D(float x = 0.0, float y = 0.0);

            /**
             * @brief Copy constructor that sets the coordinates of the current object with the coordinates of the `Point2D` object passed as argument.
             * @param other `Point2D` object.
             ```
             // Example:
            Point2D a(1,2);
            Point2D b(a);
             ```
             */
            Point2D(const Point2D& other);

        /// @}

        /**
         * @brief Default Destructor
         */
        ~Point2D() = default;

        /**
         * @name Operator(s) ovreloading
         * @{
         */
            /**
             * @brief Overloading of the `operator=` operator. It accept a `Point2D` object as argument and returns a reference to a `Point2D` object. This method allows assignement operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b = a;
             ```
             * @param other Point2D object.
             * @return Returns the initialised object with other's value(s).
             */
            Point2D& operator=(const Point2D& other);

            /**
             * @brief Overloading of the `operator==` operator. It accept a `Point2D` object as argument and returns a boolean value: if the two object are equals it returns `true`, otherwise `false`. This method allows comparison operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b(3,4);
             std::cout >> (a == b) ? "true" : "false";
             ```
             * @param other Point2D object.
             * @return Returns a boolean value.
             */
            bool operator==(const Point2D& other);

            /**
             * @brief Overloading of the `operator+` operator. It accept a `Point2D` object as argument and returns a `Point2D` object. This method allows sum operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b(3,4);
             Point2D c = a + b;
             ```
             * @param other Point2D object.
             * @return Returns Point2D object.
             */
            Point2D operator+(const Point2D& other) const;

            /**
             * @brief Overloading of the `operator-` operator. It accept a `Point2D` object as argument and returns a `Point2D` object. This method allows subtraction operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b(3,4);
             Point2D c = a - b;
             ```
             * @param other Point2D object.
             * @return Returns Point2D object.
             */
            Point2D operator-(const Point2D& other) const;

            /**
             * @brief Overloading of the `operator*` operator. It accept a `float` scalar as argument and returns a `Point2D` object. This method allows product operations such as:
             ```
             // Example:
             Point2D a(1,2);
             float b = 3.0f;
             Point2D c = a * b;
             ```
             * @param scalar float argument.
             * @return Returns Point2D object.
             */
            Point2D operator*(float scalar) const ;

            /**
             * @brief Overloading of the `operator/` operator. It accept a `float` scalar as argument and returns a `Point2D` object. This method allows division operations such as:
             ```
             // Example:
             Point2D a(1,2);
             float b = 3.0f;
             Point2D c = a/b;
             ```
             * @param scalar float argument.
             * @return Returns Point2D object.
             */
            Point2D operator/(float scalar) const ;
            
            /**
             * @brief Overloading of the `operator*` operator. It accept a `Point2D` object as argument and returns a `float` value. This method allows scalar product between two points operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b(3,4);
             float c = a * b;
             ```
             * @param other `Point2D` argument.
             * @return Returns `float` value.
             */
            float operator*(const Point2D& other) const;

            /**
             * @brief Overloading of the `operator+=` operator. It accept a `Point2D` object as argument and returns none. This method allows self-sum operations such as:
             ```
             // Example:
             Point2D a(1,2);
             Point2D b(3,4);
             a += b;
             ```
             * @param other `Point2D` object.
             * @return none.
             */
            void operator+=(const Point2D& other);
            
            /**
             * @brief Overloading of the `operator[]` operator (non-const variant). It accept a `int` value and returns a `float` value: the value `0` represents the x-coordinte while `1` represents the y-coordinate. This method allows index, read and (over)write operations such as:
             ```
             // Example:
             Point2D a(1,2);
             float x = a[0];
             float y = a[1];

             a[0] = a[1];
             ```
             * @param index int value.
             * @return `float` value which represent the selected coordinate.
             */
            float operator[](int index);

            /**
             * @brief Overloading of the `operator[]` operator (const variant). It accept a `int` value and returns a `float` value: the value `0` represents the x-coordinte while `1` represents the y-coordinate. This method allows index and only read operations such as:
             ```
             // Example:
             Point2D a(1,2);
             float x = a[0];
             float y = a[1];
             ```
             * @param index int value.
             * @return `float` value which represent the selected coordinate.
             */
            const float& operator[](int index) const;

        /// @}

        /**
         * @name Getters and Setters
         * @{
         */
            /**
             * @brief Method that returns a `float` value: the x-coordinate of the object.
             * @return `float` value.
             */
            float getX() const;

            /**
             * @brief Method that returns a `float` value: the y-coordinate of the object.
             * @return `float` value.
             */
            float getY() const;
            
            /**
             * @brief Method that sets a the x-coordinate of the object with the value passed as argument.
             * @param `float` value.
             */
            void setX(float x);
            /**
             * @brief Method that sets a the y-coordinate of the object with the value passed as argument.
             * @param `float` value.
             */
            void setY(float y);

        /// @}

        /**
         * @brief Method that returns a float value wich represent the cross product between two points.
         * @param p1 `Point2D` object.
         * @return `float` value.
         */
        float cross2D(const Point2D& p1) const ;
        
        /**
         * @brief Method that returns a float value wich represent the Scalar Triple Product (STP) between three points. Geometrically, corresponds to the volume of a parallelepiped formed by three indipendet vectors a, b, c
         * @param b `Point2D` object.
         * @param c `Point2D` object.
         * @return `float` value.
         */
        float stp2D(const Point2D& b, const Point2D& c) const ;
    };
}

#endif