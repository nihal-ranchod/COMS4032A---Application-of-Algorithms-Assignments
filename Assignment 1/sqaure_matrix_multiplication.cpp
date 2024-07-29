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
            cout << setw(5) << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Standard SQUARE-MATRIX-MULTIPLY
vector<vector<int>> squareMatrixMultiply(vector<vector<int>> A, vector<vector<int>> B) {
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

// Measure running time algorithm
template <typename Func>
long long measureTime(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main(){
    // Range of dimensions
    vector<int> dimensions = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int numTrials = 5;

    ofstream file("matrix_multiplication.csv");
    file << "Dimension, Algorithm, Average Time (microseconds)\n" << endl;

    for (int n : dimensions) {
        long long timeSquareMatrixMultiply = 0;

        for (int trial = 0; trial < numTrials; trial++){
            vector<vector<int>> A = generateRandomMatrix(n);
            vector<vector<int>> B = generateRandomMatrix(n);

            timeSquareMatrixMultiply += measureTime([&](){
                squareMatrixMultiply(A, B);
            });
        }

        file << n << ", Square Matrix Multiply, " << timeSquareMatrixMultiply / numTrials << endl;
    }

    file.close();
    cout << "Data written to matrix_multiplication.csv" << endl;

    return 0;
}