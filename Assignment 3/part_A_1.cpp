/*
Theorem 21.2:
Using the linked-list representation of disjoint sets and the weighted-union heuristic, a 
sequence of 𝑚 MAKE-SET, UNION, and FIND-SET operations, n of which are MAKE-SET operations, 
takes 𝑂(𝑚 + 𝑛log 𝑛) time.
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>  // For rand()
#include <random>   // For different distributions
#include <map>
#include <tuple>
#include <algorithm> // For std::max

using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> size;
    vector<int> depth;

public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        depth.resize(n, 1);
    }

    void MAKE_SET(int x) {
        parent[x] = x;
        size[x] = 1;
        depth[x] = 1;
    }

    int FIND_SET(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    void UNION(int x, int y) {
        int root_x = FIND_SET(x);
        int root_y = FIND_SET(y);
        if (root_x != root_y) {
            if (size[root_x] < size[root_y]) {
                parent[root_x] = root_y;
                size[root_y] += size[root_x];
                depth[root_y] = max(depth[root_y], depth[root_x] + 1);
            } else {
                parent[root_y] = root_x;
                size[root_x] += size[root_y];
                depth[root_x] = max(depth[root_x], depth[root_y] + 1);
            }
        }
    }

    bool check_consistency(int n) {
        for (int i = 0; i < n; ++i) {
            if (FIND_SET(i) != FIND_SET(FIND_SET(i))) {
                return false;
            }
        }
        return true;
    }

    int get_max_depth() {
        return *max_element(depth.begin(), depth.end());
    }
};

void run_experiment(int n, int m, double union_ratio, ofstream &file, mt19937 &gen, map<tuple<int, int, double>, tuple<double, int, int, int, int>> &results) {
    DisjointSet ds(n);
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        ds.MAKE_SET(i);
    }

    uniform_int_distribution<> dist(0, n - 1);
    bernoulli_distribution op_dist(union_ratio);

    int union_count = 0;
    int find_set_count = 0;

    for (int i = n; i < m; i++) {
        int x = dist(gen);
        int y = dist(gen);

        if (op_dist(gen)) {
            ds.UNION(x, y);
            union_count++;
        } else {
            ds.FIND_SET(x);
            find_set_count++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;

    bool is_consistent = ds.check_consistency(n);
    int max_depth = ds.get_max_depth();

    if (is_consistent) {
        file << n << "," << m << "," << union_ratio << "," << elapsed_time.count() << "," << union_count << "," << find_set_count << "," << max_depth << ",Consistent" << endl;
    } else {
        file << n << "," << m << "," << union_ratio << "," << elapsed_time.count() << "," << union_count << "," << find_set_count << "," << max_depth << ",Inconsistent" << endl;
    }

    auto key = make_tuple(n, m, union_ratio);
    if (results.find(key) == results.end()) {
        results[key] = make_tuple(elapsed_time.count(), union_count, find_set_count, max_depth, 1);
    } else {
        auto &val = results[key];
        get<0>(val) += elapsed_time.count();
        get<1>(val) += union_count;
        get<2>(val) += find_set_count;
        get<3>(val) += max_depth;
        get<4>(val) += 1;
    }
}

int main() {
    int num_elements[] = {1000, 5000, 10000};
    int num_operations[] = {1000, 5000, 10000, 25000, 50000};
    double union_ratios[] = {0.25, 0.5, 0.75};
    int num_runs = 5;

    ofstream file("part_A_1.csv");
    file << "Number of elements,Number of operations,Union ratio,Execution time,Union count,Find-Set count,Max Depth,Consistency Check" << endl;

    ofstream avg_file("part_A_1_averaged.csv");
    avg_file << "Number of elements,Number of operations,Union ratio,Average Execution time,Average Union count,Average Find-Set count,Average Max Depth" << endl;

    random_device rd;
    mt19937 gen(rd());

    map<tuple<int, int, double>, tuple<double, int, int, int, int>> results;

    for (int n : num_elements) {
        for (int m : num_operations) {
            if (n <= m) {
                for (double ratio : union_ratios) {
                    for (int run = 0; run < num_runs; run++) {
                        run_experiment(n, m, ratio, file, gen, results);
                    }
                }
            }
        }
    }

    for (const auto &entry : results) {
        auto key = entry.first;
        auto val = entry.second;
        int n = get<0>(key);
        int m = get<1>(key);
        double ratio = get<2>(key);
        double avg_time = get<0>(val) / get<4>(val);
        int avg_union_count = get<1>(val) / get<4>(val);
        int avg_find_set_count = get<2>(val) / get<4>(val);
        int avg_max_depth = get<3>(val) / get<4>(val);
        avg_file << n << "," << m << "," << ratio << "," << avg_time << "," << avg_union_count << "," << avg_find_set_count << "," << avg_max_depth << endl;
    }

    file.close();
    avg_file.close();
    cout << "Extended experiment completed. Results saved to part_A_1_extended.csv and part_A_1_averaged.csv" << endl;
    return 0;
}