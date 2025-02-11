#ifndef MATRIX_HH
#define MATRIX_HH
#include <vector>
#include "../include/Point3D.hh"

namespace Geometry {
    class Matrix {
    private:
        std::vector<std::vector<float>> data; // Internal matrix
        int rows;
        int cols;

        // Support function
        // 2-by-2 symmetric Schur decomposition. 
        // Given an n-by-n symmetric matrix and indeces p, q
        // cuch that 1 <= p < q <= n, computes a sine-cosine
        // pair (s, c) that will serve to form a Jacobi rotation matrix.
        static void sym_schur_2x2(Matrix mat, int p, int q, float& c, float& s);
    public:
        // Constructor: initialize a matrix with only 0s and a defined size
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

        // Conversion in a Covariance matrix
        void covariance_matrix(std::vector<Point3D> points);

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