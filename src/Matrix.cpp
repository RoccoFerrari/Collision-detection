#include "../include/Matrix.hh"

namespace Geometry {

    Matrix::Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r);
        for (int i = 0; i < r; ++i) 
            data[i].resize(c, 0.0f); 
    }

    void Matrix::set(int r, int c, float value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value;
        } else 
            throw std::out_of_range("Indexes out of range");
    }

    float Matrix::get(int r, int c) const {
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

    const std::vector<float>& Matrix::operator[](int i) const {
        return data[i];
    }

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

    Matrix Matrix::transpose() const {
        Matrix transposed(cols, rows); 
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) 
                transposed.data[j][i] = data[i][j]; 
        }
        return transposed;
    }

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