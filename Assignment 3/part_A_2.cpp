#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>  // For assertions
#include <cstdlib>  // For rand()
#include <random>   // For different distributions
#include <map>
#include <tuple>
#include <algorithm> // For std::max

using namespace std;

class Element {
public:
    int p;     
    int rank;  

    Element() : p(0), rank(0) {}
};

class DisjointSet {
private:
    vector<Element> elements;
    vector<int> depth;

public:
    DisjointSet(int n) {
        elements.resize(n);
        depth.resize(n, 1);
        for (int i = 0; i < n; i++) {
            elements[i].p = i; // Initialize each element to be its own parent
            elements[i].rank = 0; // Initialize rank
        }
    }

    // Make-Set Operation: Initializes a single set for element x.
    void MAKE_SET(int x) {
        elements[x].p = x;
        elements[x].rank = 0; // Initialize rank
        depth[x] = 1; // Initialize depth
    }

    // Find-Set Operation with path compression: Returns the representative of the set that contains x.
    int FIND_SET(int x) {
        if (elements[x].p != x) {
            elements[x].p = FIND_SET(elements[x].p); // Path compression
        }
        return elements[x].p;
    }

    // Link function: Links the trees rooted at x and y.
    void LINK(int x, int y) {
        if (elements[x].rank > elements[y].rank) {
            elements[y].p = x;
        } else {
            elements[x].p = y;
            if (elements[x].rank == elements[y].rank) {
                elements[y].rank += 1; // Increase rank if they are the same
            }
        }
    }

    // Union Operation: Combines the two sets that contain x and y.
    void UNION(int x, int y) {
        LINK(FIND_SET(x), FIND_SET(y));
    }

    // Check consistency of the Disjoint Set structure
    bool check_consistency(int n) {
        for (int i = 0; i < n; ++i) {
            if (FIND_SET(i) != FIND_SET(FIND_SET(i))) {
                return false; // Inconsistent structure
            }
        }
        return true; // Consistent structure
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

    ofstream file("part_A_2.csv");
    file << "Number of elements,Number of operations,Union ratio,Execution time,Union count,Find-Set count,Max Depth,Consistency Check" << endl;

    ofstream avg_file("part_A_2_averaged.csv");
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
    cout << "Extended experiment completed. Results saved to part_A_2_extended.csv and part_A_2_averaged.csv" << endl;
    return 0;
}