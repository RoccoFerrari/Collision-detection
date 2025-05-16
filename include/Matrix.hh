#ifndef MATRIX_HH
#define MATRIX_HH
#include <stdexcept>
#include <cmath>
#include <iterator>
#include <vector>
#include "Point3D.hh"

namespace Geometry {

    /**
     * @class Matrix.
     * @brief Class modeling a Matrix.
     */
    class Matrix {
    private:

        /**
         * @brief Internal matrix.
         * @param data 
         */
        std::vector<std::vector<float>> data; 

        /**
         * @brief Number of rows.
         * @param rows 
         */
        int rows;

        /**
         * @brief Number of colons.
         * @param cols 
         */
        int cols;

        /**
         * @brief Support functions that compute 2-by-2 symmetric Schur decomposition. Given an n-by-n symmetric matrix and indeces `p`, `q` such that $1 \le p < q \le n$, computes a sine-cosine pair `(s, c)` that will serve to form a Jacobi rotation matrix.
         * @param p first index
         * @param q second index
         * @param c cosine
         * @param s sine
         */
        void sym_schur_2x2(int p, int q, float& c, float& s);
    public:

        /**
         * @name Constructors.
         * @{
         */

            /**
             * @brief Constructor that initializes a matrix with only 0s and a defined size (3x3).
             * @param r number of rows
             * @param c number of cols
             */
            Matrix(int r = 3, int c = 3);

        /// @}

        // Setter method

        /**
         * @name Setter and Getter method(s).
         * @{
         */
        
            /**
             * @brief Method that sets a `float` value in `r` and `c` position.
             * @return none.
             */
            void set(int r, int c, float value);

            /**
             * @brief Method that returns a `float` value in `r` and `c` position.
             * @return `float` value.
             */
            float get(int r, int c) const ;
        
        /// @}

        /**
         * @name Operator(s) ovreloading
         * @{
         */

            /**
             * @brief Overloading of the `operator[]` operator (non-const variant). It accept a `int` value and returns a `vector<float>` object that represents a col of the matrix. This method allows index, read and (over)write operations such as:
             ```
             // Example:
             Matrix a(10,10);
             float x = a[0][0];
             vector<float> y = a[1];
             a[10][2] = a[2][8];
             ```
             * @param i int value.
             * @return `vector<float>` object which represent the selected coordinate.
             */
            std::vector<float>& operator[](int i);

            /**
             * @brief Overloading of the `operator[]` operator (const variant). It accept a `int` value and returns a `vector<float>` object that represents a col of the matrix. This method allows index and read operations such as:
             ```
             // Example:
             Matrix a(10,10);
             float x = a[0][0];
             vector<float> y = a[1];
             ```
             * @param i int value.
             * @return `vector<float>` object which represent the selected coordinate.
             */
            const std::vector<float>& operator[](int i) const ;
            
            /**
             * @brief Overloading of the `operator*` operator. It accept a `Matrix` objject and returns a `Matrix` object that represents new computed matrix. This method allows product operations such as:
             ```
             // Example:
             Matrix a(4,4);
             Matrix b(4,4);
             Matrix c = a * b;
             ```
             * @param other .
             * @return `vector<float>` object which represent the selected coordinate.
             */
            Matrix operator*(const Matrix& other) const ;

            // Operato= 
            Matrix& operator=(const Matrix& other);

        /// @}

        // Create a new transposed matrix
        Matrix transpose() const ;

        // Creation of a covariance matrix
        template <typename Iterator>
        inline void covariance_matrix(Iterator begin, Iterator end) {
            using ValueType = typename std::iterator_traits<Iterator>::value_type;

            // Calculate the number of points
            size_t n = std::distance(begin, end);
            if (n == 0) return; // Handle empty container

            float oon = 1.0f / static_cast<float>(n);
            Point3D centroid(0.0f, 0.0f, 0.0f);
            float e00, e11, e22, e01, e02, e12;

            // Compute the center of mass (centroid) of the points (sample average)
            for(auto it = begin; it != end; ++it)
                centroid += *it;
            centroid *= oon;

            // Compute covariance elements
            e00 = e11 = e22 = e01 = e02 = e12 = 0.0f;
            for(auto it = begin; it != end; ++it) {
                // Translate points so center of mass is at origin
                Point3D p = *it - centroid;
                // Compute covariance of translated points
                e00 += p.getX() * p.getX();
                e11 += p.getY() * p.getY();
                e22 += p.getZ() * p.getZ();
                e01 += p.getX() * p.getY();
                e02 += p.getX() * p.getZ();
                e12 += p.getY() * p.getZ();
            }
            // Fill in the covariance matrix elements
            this->set(0, 0, e00 * oon);
            this->set(1, 1, e11 * oon);
            this->set(2, 2, e22 * oon);
            this->set(0, 1, e01 * oon);
            this->set(0, 2, e02 * oon);
            this->set(1, 2, e12 * oon);
            this->set(1, 0, e01 * oon);
            this->set(2, 0, e02 * oon);
            this->set(2, 1, e12 * oon);
        }

        // Computes the eigenvectors and eigenvalues of the symmetric matricx A using
        // the classic Jacobi method od iteratively updating A as A = J^T * A * J,
        // where J = J(p, q, theta) is the Jacobi rotation matrix
        //
        // On exit, V will contain the eigenvectors, and the diagonal elements
        // of A are corresponding eigenvalues
        static void jacobi(Matrix& A, Matrix& V);
    }; 
}

#endif