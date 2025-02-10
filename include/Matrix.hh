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
    public:
        // Constructor: initialize a matrix with only 0s and a defined size
        Matrix(int r = 3, int c = 3);

        // Setter method
        void set(int r, int c, double value);
        // Getter method
        double get(int r, int c) const ;
        
        // Method for the product between matrices
        Matrix operator*(const Matrix& other) const ;

        // Conversion in a Covariance matrix
        void covariance_matrix(std::vector<Point3D> points);
    }; 
}

#endif