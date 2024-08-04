#include "matrix_multiplication.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(const Matrix &matrix) {
    for (const auto &row : matrix) {
        for (const auto &elem : row) {
            cout << setw(5) << elem << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    // Change dimensions to test different matrix sizes
    vector<int> dimensions = {3, 4, 5};

    for (int n : dimensions) {
        cout << "Matrix dimension: " << n << "x" << n << endl;

        Matrix A = generateRandomMatrix(n);
        Matrix B = generateRandomMatrix(n);

        cout << "Matrix A (" << n << "x" << n << "):\n";
        printMatrix(A);
        cout << "Matrix B (" << n << "x" << n << "):\n";
        printMatrix(B);

        // Standard Multiplication
        Matrix C1 = squareMatrixMultiply(A, B);
        cout << "Standard Multiplication Result:\n";
        printMatrix(C1);

        // Recursive Multiplicationclear
        int newSize = pow(2, ceil(log2(n)));
        Matrix paddedA = (newSize == n) ? A : padMatrix(A, newSize);
        Matrix paddedB = (newSize == n) ? B : padMatrix(B, newSize);
        Matrix C2 = squareMatrixMultiplyRecursive(paddedA, paddedB);
        Matrix C2_unpadded = (newSize == n) ? C2 : unpadMatrix(C2, n);
        cout << "Recursive Multiplication Result:\n";
        printMatrix(C2_unpadded);

        // Strassen Multiplication
        Matrix C3 = strassen(paddedA, paddedB);
        Matrix C3_unpadded = (newSize == n) ? C3 : unpadMatrix(C3, n);
        cout << "Strassen Multiplication Result:\n";
        printMatrix(C3_unpadded);
    }

    return 0;
}