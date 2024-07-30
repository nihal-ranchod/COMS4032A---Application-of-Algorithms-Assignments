#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip> 
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix;

Matrix squareMatrixMultiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix subtract(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

Matrix squareMatrixMultiplyRecursive(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        Matrix A11(newSize, vector<int>(newSize, 0));
        Matrix A12(newSize, vector<int>(newSize, 0));
        Matrix A21(newSize, vector<int>(newSize, 0));
        Matrix A22(newSize, vector<int>(newSize, 0));
        Matrix B11(newSize, vector<int>(newSize, 0));
        Matrix B12(newSize, vector<int>(newSize, 0));
        Matrix B21(newSize, vector<int>(newSize, 0));
        Matrix B22(newSize, vector<int>(newSize, 0));

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

        Matrix C11 = add(squareMatrixMultiplyRecursive(A11, B11), squareMatrixMultiplyRecursive(A12, B21));
        Matrix C12 = add(squareMatrixMultiplyRecursive(A11, B12), squareMatrixMultiplyRecursive(A12, B22));
        Matrix C21 = add(squareMatrixMultiplyRecursive(A21, B11), squareMatrixMultiplyRecursive(A22, B21));
        Matrix C22 = add(squareMatrixMultiplyRecursive(A21, B12), squareMatrixMultiplyRecursive(A22, B22));

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

Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        Matrix A11(newSize, vector<int>(newSize, 0));
        Matrix A12(newSize, vector<int>(newSize, 0));
        Matrix A21(newSize, vector<int>(newSize, 0));
        Matrix A22(newSize, vector<int>(newSize, 0));
        Matrix B11(newSize, vector<int>(newSize, 0));
        Matrix B12(newSize, vector<int>(newSize, 0));
        Matrix B21(newSize, vector<int>(newSize, 0));
        Matrix B22(newSize, vector<int>(newSize, 0));

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

        Matrix M1 = strassen(add(A11, A22), add(B11, B22));
        Matrix M2 = strassen(add(A21, A22), B11);
        Matrix M3 = strassen(A11, subtract(B12, B22));
        Matrix M4 = strassen(A22, subtract(B21, B11));
        Matrix M5 = strassen(add(A11, A12), B22);
        Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
        Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

        Matrix C11 = add(subtract(add(M1, M4), M5), M7);
        Matrix C12 = add(M3, M5);
        Matrix C21 = add(M2, M4);
        Matrix C22 = add(subtract(add(M1, M3), M2), M6);

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

Matrix generateRandomMatrix(int n) {
    Matrix matrix(n, vector<int>(n));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

tuple<double, double, double> measureTime(int n) {
    double standardTime = 0.0;
    double recursiveTime = 0.0;
    double strassenTime = 0.0;

    for (int i = 0; i < 3; ++i) {
        Matrix A = generateRandomMatrix(n);
        Matrix B = generateRandomMatrix(n);

        auto start = chrono::high_resolution_clock::now();
        Matrix C1 = squareMatrixMultiply(A, B);
        auto end = chrono::high_resolution_clock::now();
        standardTime += chrono::duration<double>(end - start).count();

        start = chrono::high_resolution_clock::now();
        Matrix C2 = squareMatrixMultiplyRecursive(A, B);
        end = chrono::high_resolution_clock::now();
        recursiveTime += chrono::duration<double>(end - start).count();

        start = chrono::high_resolution_clock::now();
        Matrix C3 = strassen(A, B);
        end = chrono::high_resolution_clock::now();
        strassenTime += chrono::duration<double>(end - start).count();
    }

    return {standardTime / 3, recursiveTime / 3, strassenTime / 3};
}

int main() {
    vector<int> dimensions = {64, 128, 256, 512};
    ofstream csvFile("matrix_multiplication_times.csv");

    csvFile << "Dimension,Standard,Recursive,Strassen\n";

    for (int n : dimensions) {
        auto times = measureTime(n);
        csvFile << n << "," << get<0>(times) << "," << get<1>(times) << "," << get<2>(times) << "\n";
    }

    csvFile.close();
    return 0;
}