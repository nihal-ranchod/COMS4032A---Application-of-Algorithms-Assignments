#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip> 
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Function -> generate random square matrix
vector<vector<int>> generateRandomMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size)); // 2D vector of size x size, initialized to 0
    random_device rd; // random device to seed the generator
    mt19937 gen(rd()); // Merseinne Twister engine seeded with rd
    uniform_int_distribution<> dis(1, 100); // uniform distribution between 1 and 100
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Function -> print matrix (for debugging)
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << setw(5) << val << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;
}

// Standard SQUARE-MATRIX-MULTIPLY ----------------------------------------------------
vector<vector<int>> squareMatrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
//--------------------------------------------------------------------------------------

// SQUARE-MATRIX-MULTIPLY-RECURSIVE ----------------------------------------------------

// Function -> add two matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> squareMatrixMultiplyRecursive(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1){
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<vector<int>> A11(newSize, vector<int>(newSize));
        vector<vector<int>> A12(newSize, vector<int>(newSize));
        vector<vector<int>> A21(newSize, vector<int>(newSize));
        vector<vector<int>> A22(newSize, vector<int>(newSize));
        vector<vector<int>> B11(newSize, vector<int>(newSize));
        vector<vector<int>> B12(newSize, vector<int>(newSize));
        vector<vector<int>> B21(newSize, vector<int>(newSize));
        vector<vector<int>> B22(newSize, vector<int>(newSize));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        vector<vector<int>> C11 = add(squareMatrixMultiplyRecursive(A11, B11), squareMatrixMultiplyRecursive(A12, B21));
        vector<vector<int>> C12 = add(squareMatrixMultiplyRecursive(A11, B12), squareMatrixMultiplyRecursive(A12, B22));
        vector<vector<int>> C21 = add(squareMatrixMultiplyRecursive(A21, B11), squareMatrixMultiplyRecursive(A22, B21));
        vector<vector<int>> C22 = add(squareMatrixMultiplyRecursive(A21, B12), squareMatrixMultiplyRecursive(A22, B22));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }

    return C;
}
//--------------------------------------------------------------------------------------

// STRASSSEN'S ALGORITHM ---------------------------------------------------------------

vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

vector<vector<int>> strassensAlgorithm(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<vector<int>> A11(newSize, vector<int>(newSize));
        vector<vector<int>> A12(newSize, vector<int>(newSize));
        vector<vector<int>> A21(newSize, vector<int>(newSize));
        vector<vector<int>> A22(newSize, vector<int>(newSize));
        vector<vector<int>> B11(newSize, vector<int>(newSize));
        vector<vector<int>> B12(newSize, vector<int>(newSize));
        vector<vector<int>> B21(newSize, vector<int>(newSize));
        vector<vector<int>> B22(newSize, vector<int>(newSize));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        vector<vector<int>> S1 = subtract(B12, B22);
        vector<vector<int>> S2 = add(A11, A12);
        vector<vector<int>> S3 = add(A21, A22);
        vector<vector<int>> S4 = subtract(B21, B11);
        vector<vector<int>> S5 = add(A11, A22);
        vector<vector<int>> S6 = add(B11, B22);
        vector<vector<int>> S7 = subtract(A12, A22);
        vector<vector<int>> S8 = add(B21, B22);
        vector<vector<int>> S9 = subtract(A11, A21);    
        vector<vector<int>> S10 = add(B11, B12);

        vector<vector<int>> P1 = strassensAlgorithm(A11, S1);
        vector<vector<int>> P2 = strassensAlgorithm(S2, B22);
        vector<vector<int>> P3 = strassensAlgorithm(S3, B11);
        vector<vector<int>> P4 = strassensAlgorithm(A22, S4);
        vector<vector<int>> P5 = strassensAlgorithm(S5, S6);
        vector<vector<int>> P6 = strassensAlgorithm(S7, S8);
        vector<vector<int>> P7 = strassensAlgorithm(S9, S10);

        vector<vector<int>> C11 = add(subtract(add(P5, P4), P2), P6);
        vector<vector<int>> C12 = add(P1, P2);
        vector<vector<int>> C21 = add(P3, P4);
        vector<vector<int>> C22 = subtract(subtract(add(P5, P1), P3), P7);

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }

    }

    return C;
}
//--------------------------------------------------------------------------------------


// Measure running time of algorithm
template <typename Func>
long long measureTime(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main(){
    // Range of dimensions
    vector<int> dimensions = {2, 4, 8, 16, 32, 64, 128};
    int numTrials = 5;

    ofstream file("matrix_multiplication.csv");
    file << "Dimension, Algorithm, Average Time (microseconds)\n" << endl;

    for (int n : dimensions) {
        long long timeSquareMatrixMultiply = 0;
        long long timeSquareMatrixMultiplyRecursive = 0;
        long long timeStrassensAlgorithm = 0;

        for (int trial = 0; trial < numTrials; trial++){
            vector<vector<int>> A = generateRandomMatrix(n);
            vector<vector<int>> B = generateRandomMatrix(n);

            timeSquareMatrixMultiply += measureTime([&](){
                squareMatrixMultiply(A, B);
            });

            timeSquareMatrixMultiplyRecursive += measureTime([&](){
                squareMatrixMultiplyRecursive(A, B);
            });

            timeStrassensAlgorithm += measureTime([&](){
                strassensAlgorithm(A, B);
            });
        }

        file << n << ", Square Matrix Multiply, " << timeSquareMatrixMultiply / numTrials << endl;
        file << n << ", Square Matrix Multiply Recursive, " << timeSquareMatrixMultiplyRecursive / numTrials << endl;
        file << n << ", Strassen's Algorithm, " << timeStrassensAlgorithm / numTrials << endl;
    }

    file.close();
    std::cout << "Data written to matrix_multiplication.csv" << endl;

    return 0;
}