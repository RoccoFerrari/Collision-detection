#include "../include/Matrix.hh"
#include <stdexcept>
#include <cmath>

namespace Geometry {
    // Constructor
    Matrix::Matrix(int r, int c) : rows(r), cols(c) {
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
    // Operator[]
    std::vector<float>& Matrix::operator[](int i) {
        return data[i];
    }

    // operator[] (const version)
    const std::vector<float>& Matrix::operator[](int i) const {
        return data[i];
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

    Matrix& Matrix::operator=(const Matrix& other) {
        if (this == &other)
            return *this;
        data.clear();
        data.resize(other.rows, std::vector<float>(other.cols));

        rows = other.rows;
        cols = other.cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Create a new transposed matrix
    Matrix Matrix::transpose() const {
        Matrix transposed(cols, rows); 
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) 
                transposed.data[j][i] = data[i][j]; 
        }
        return transposed;
    }

    // Creation of a covariance matrix
    void Matrix::covariance_matrix(std::vector<Point3D> points) {
        int n = points.size();
        float oon = 1.0f / (float)n;
        Point3D c = Point3D(0.0f, 0.0f, 0.0f);
        float e00, e11, e22, e01, e02, e12;

        // Compute the center of mass (centroid) of the points (sample average)
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
    // Support function
    // 2-by-2 symmetric Schur decomposition. 
    // Given an n-by-n symmetric matrix and indeces p, q
    // cuch that 1 <= p < q <= n, computes a sine-cosine
    // pair (s, c) that will serve to form a Jacobi rotation matrix.
    void Matrix::sym_schur_2x2(int p, int q, float& c, float& s) {
        if(abs(this->get(p, q)) > 0.0001f) {
            float r = (this->get(q, q) - this->get(p, p)) / (2.0f * this->get(p, q));
            float t;
            if(r >= 0.0f)
                t = 1.0f / (r + sqrt(1.0f + r*r));
            else
                t = -1.0f / (-r + sqrt(1.0f + r*r));
            c = 1.0f / sqrt(1.0f + t*t);
            s = t * c;
        } else {
            c = 1.0f;
            s = 0.0f;
        }
    }

    // Computes the eigenvectors and eigenvalues of the symmetric matricx A using
    // the classic Jacobi method od iteratively updating A as A = J^T * A * J,
    // where J = J(p, q, theta) is the Jacobi rotation matrix
    //
    // On exit, V will contain the eigenvectors, and the diagonal elements
    // of A are corresponding eigenvalues
    void Matrix::jacobi(Matrix& A, Matrix& V) {
        int i, j, n, p, q;
        float prevoff, c, s;
        Matrix J, b, t;

        // Initialize V to identify matrix
        for(i = 0; i < 3; ++i) {
            V[i][0] = V[i][1] = V[i][2] = 0.0f;
            V[i][i] = 1.0f;
        }

        // Reapeat for some maximum number of iterations
        const int MAX_ITERATIONS = 50;
        for(n = 0; n < MAX_ITERATIONS; ++n) {
            // Find largest off-diagonal absolute element a[p][q]
            p = 0;
            q = 1;
            for(i = 0; i < 3; ++i) {
                for(j = 0; j < 3; ++j) {
                    if(i == j) 
                        continue;
                    if(abs(A[i][j]) > abs(A[p][q])) {
                        p = i;
                        q = j;
                    }
                }
            }

            // Compute the Jacobi rotation matrix J(p, q, theta)
            A.sym_schur_2x2(p, q, c, s);
            for(i = 0; i < 3; ++i) {
                J[i][0] = J[i][1] = J[i][2] = 0.0f;
                J[i][i] = 1.0f;
            }
            J[p][p] = c;
            J[p][q] = s;
            J[q][p] = -s;
            J[q][q] = c;

            // Cumulate rotations into whta will contain the eigenvectors
            V = V * J;

            // Make 'a' more diagonal, until just eigenvalues remain on diagonal
            A = (J.transpose() * A) * J;

            // Compute 'norm' of off-diagonal elements
            float off = 0.0f;
            for(i = 0; i < 3; ++i) {
                for(j = 0; j < 3; ++j) {
                    if(i == j)
                        continue;
                    off += A[i][j] * A[i][j];
                }
            }
            // Stop when norm no longer decreasing
            if(n > 2 && off >= prevoff)
                return;

            prevoff = off;
        }
    }
}