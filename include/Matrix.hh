#ifndef MATRIX_HH
#define MATRIX_HH
#include <stdexcept>
#include <cmath>
#include <iterator>
#include <vector>
#include "Point3D.hh"

namespace Geometry {
    class Matrix {
    private:
        std::vector<std::vector<float>> data; // Internal matrix
        int rows;
        int cols;

        // Support functions
        // 2-by-2 symmetric Schur decomposition. 
        // Given an n-by-n symmetric matrix and indeces p, q
        // cuch that 1 <= p < q <= n, computes a sine-cosine
        // pair (s, c) that will serve to form a Jacobi rotation matrix.
        void sym_schur_2x2(int p, int q, float& c, float& s);
    public:
        // Constructor: initialize a matrix with only 0s and a defined size (3x3)
        Matrix(int r = 3, int c = 3);

        // Setter method
        void set(int r, int c, double value);
        // Getter method
        double get(int r, int c) const ;

        // operator[] 
        std::vector<float>& operator[](int i);
        // operator[] (const version)
        const std::vector<float>& operator[](int i) const ;
        
        // Method for the product between matrices
        Matrix operator*(const Matrix& other) const ;

        // Operato= 
        Matrix& operator=(const Matrix& other);

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