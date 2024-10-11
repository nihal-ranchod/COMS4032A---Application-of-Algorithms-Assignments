/*
The experiment is designed to provide empirical evidence for Theorem 21.2, which states that:
a sequence of 𝑚 MAKE-SET, UNION, and FIND-SET operations takes 𝑂(𝑚 + 𝑛log 𝑛) time 
when using the weighted-union heuristic. By measuring the execution time for union operations
across different numbers of elements, we can observe the expected time complexity behaviour.
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>  // For assertions
#include <cstdlib>  // For rand()

using namespace std;

class DisjointSet {
    private:
        vector<int> parent;
        vector<int> size;

    public:
        DisjointSet(int n) {
            parent.resize(n);
            size.resize(n, 1);
        }

        // Make-Set Operation: Initializes a single set for element x.
        void MAKE_SET(int x) {
            parent[x] = x;
            size[x] = 1;
        }

        // Find-Set Operation: Returns the representative of the set that contains x.
        int FIND_SET(int x) {
            while (parent[x] != x) {
                x = parent[x];
            }
            return x;
        }

        // Union Operation with weighted-union heuristic: Combines the two sets that contain x and y into a new set that is the union of these two sets.
        void UNION(int x, int y) {
            int root_x = FIND_SET(x);
            int root_y = FIND_SET(y);
            if (root_x != root_y) {
                if (size[root_x] < size[root_y]) {
                    parent[root_x] = root_y;
                    size[root_y] += size[root_x];
                } else {
                    parent[root_y] = root_x;
                    size[root_x] += size[root_y];
                }
            }
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
};

// Function to run & measure the execution time for a sequence of n MAKE-SET and m UNION operations
void run_experiment(int n, int m, ofstream &file) {
    DisjointSet ds(n);

    // Measure the execution time for n MAKE-SET operations
    auto start_make_set = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        ds.MAKE_SET(i);
    }
    auto end_make_set = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time_make_set = end_make_set - start_make_set;

    // Measure the execution time for m UNION operations
    auto start_union = chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        ds.UNION(rand() % n, rand() % n);
    }
    auto end_union = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time_union = end_union - start_union;

    // Combine the elapsed times for Make-Set and Union operations
    double total_elapsed_time = elapsed_time_make_set.count() + elapsed_time_union.count();

    // Check consistency after operations
    bool is_consistent = ds.check_consistency(n);

    // Save results to file
    if (is_consistent) {
        file << "Union," << n << "," << m << "," << total_elapsed_time << ",Consistent" << endl;
    } else {
        file << "Union," << n << "," << m << "," << total_elapsed_time << ",Inconsistent" << endl;
    }
}

int main() {
    int num_elements[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
    int num_operations[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};

    // Open file and write header
    ofstream file("part_A_1_expanded.csv");
    file << "Operation,Number of elements,Number of operations,Execution time,Consistency Check" << endl;

    // Run the experiment for all combinations of num_elements and num_operations
    for (int n : num_elements) {
        for (int m : num_operations) {
            run_experiment(n, m, file);
        }
    }

    file.close();
    cout << "Experiment completed. Results saved to part_A_1_expanded.csv" << endl;
    return 0;
}
