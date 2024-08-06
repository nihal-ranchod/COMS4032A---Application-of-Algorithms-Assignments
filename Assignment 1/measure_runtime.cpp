#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip> 
#include <fstream>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Matrix;

int main() {
    vector<int> dimensions = {64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512};
    ofstream csvFile("Runtimes_and_Graphs/matrix_multiplication_runtimes.csv");

    csvFile << "Dimension,Standard,Recursive,Strassen\n";

    for (int n : dimensions) {
        auto times = measureTime(n);
        csvFile << n << "," << get<0>(times) << "," << get<1>(times) << "," << get<2>(times) << "\n";
    }

    csvFile.close();
    return 0;
}