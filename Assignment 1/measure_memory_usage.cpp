#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <psapi.h>

using namespace std;

typedef vector<vector<int>> Matrix;

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    return memCounter.WorkingSetSize;
}

tuple<size_t, size_t, size_t> measureMemory(int n) {
    Matrix A = generateRandomMatrix(n);
    Matrix B = generateRandomMatrix(n);

    size_t mem_before = getMemoryUsage();
    squareMatrixMultiply(A, B);
    size_t mem_after = getMemoryUsage();
    size_t standard_memory = mem_after - mem_before;

    int newSize = pow(2, ceil(log2(n)));
    Matrix paddedA = (newSize != n) ? padMatrix(A, newSize) : A;
    Matrix paddedB = (newSize != n) ? padMatrix(B, newSize) : B;

    mem_before = getMemoryUsage();
    squareMatrixMultiplyRecursive(paddedA, paddedB);
    mem_after = getMemoryUsage();
    size_t recursive_memory = mem_after - mem_before;

    mem_before = getMemoryUsage();
    strassen(paddedA, paddedB);
    mem_after = getMemoryUsage();
    size_t strassen_memory = mem_after - mem_before;

    return make_tuple(standard_memory, recursive_memory, strassen_memory);
}

int main() {
    vector<int> dimensions = {64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512};
    ofstream csvFile("matrix_multiplication_memory.csv");

    csvFile << "Dimension,Standard,Recursive,Strassen\n";

    for (int n : dimensions) {
        auto memory = measureMemory(n);
        csvFile << n << "," << get<0>(memory) << "," << get<1>(memory) << "," << get<2>(memory) << "\n";
    }

    csvFile.close();
    return 0;
}