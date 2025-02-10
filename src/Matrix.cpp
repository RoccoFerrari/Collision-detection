#include "../include/Matrix.hh"
#include <stdexcept>

namespace Geometry {
    // Constructor
    Matrix::Matrix(int r = 3, int c = 3) : rows(r), cols(c) {
        data.resize(r);
        for (int i = 0; i < r; ++i) 
            data[i].resize(c, 0.0f); 
    }

    // Setter method
    void Matrix::set(int r, int c, double value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value;
        } else 
            throw std::out_of_range("Indexes out of range");
    }

    // Getter method
    double Matrix::get(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return data[r][c];
        } else {
            throw std::out_of_range("Indexes out of range");
            return 0.0f;
        }
    }

    // Method for the product between matrices
    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix sizes not compatible");
            return Matrix(0, 0); // Restituisce una matrice vuota in caso di errore
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Conversion in a Covariance matrix
    void Matrix::covariance_matrix(std::vector<Point3D> points) {
        int n = points.size();
        float oon = 1.0f / (float)n;
        Point3D c = Point3D(0.0f, 0.0f, 0.0f);
        float e00, e11, e22, e01, e02, e12;

        // Compute the center of mass (centroid) of the points
        for(int i = 0; i < n; ++i)
            c += points[i];
        c *= oon;

        // Compute covariance elements
        e00 = e11 = e22 = e01 = e02 = e12 = 0.0f;
        for(int i = 0; i < n; ++i) {
            // Translate points so center of mass is at origin
            Point3D p = points[i] - c;
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
}