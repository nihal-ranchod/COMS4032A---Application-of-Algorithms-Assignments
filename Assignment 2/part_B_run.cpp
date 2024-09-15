#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream> 
#include "part_B_algorithms.cpp"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));

    vector<int> keys;
    vector<double> heights;
    vector<double> buildTimes;
    vector<double> destroyTimes;

    int nValues[] = {10, 50, 100, 500, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    ofstream file("ost_results.csv");
    file << "n,avg_height,avg_build_time,avg_destroy_time" << endl;

    for (int n : nValues) {
        double totalHeight = 0;
        double totalBuildTime = 0;
        double totalDestroyTime = 0;

        int trials = 50;

        for (int i = 0; i < trials; i++) {
            keys.clear();
            for (int t = 0; t < n; t++) {
                keys.push_back(t + 1);
            }
            random_shuffle(keys.begin(), keys.end());

            OrderStatisticTree ost;
            auto startBuild = high_resolution_clock::now();
            for (int key : keys) {
                ost.treeInsert(key);
            }
            auto stopBuild = high_resolution_clock::now();

            auto durationBuild = duration_cast<microseconds>(stopBuild - startBuild);
            totalBuildTime += durationBuild.count();

            totalHeight += ost.calculateHeight(ost.root);

            auto startDestroy = high_resolution_clock::now();
            for (int key : keys) {
                ost.treeDelete(ost.root);
            }
            auto stopDestroy = high_resolution_clock::now();

            auto durationDestroy = duration_cast<microseconds>(stopDestroy - startDestroy);
            totalDestroyTime += durationDestroy.count();
        }

        double avgHeight = totalHeight / trials;
        double avgBuildTime = totalBuildTime / trials;
        double avgDestroyTime = totalDestroyTime / trials;

        file << n << "," << avgHeight << "," << avgBuildTime << "," << avgDestroyTime << endl;
    }
    
    file.close();

    cout << "Results have been saved to ost_results.csv" << endl;

    return 0;
}