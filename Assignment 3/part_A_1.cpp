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

// Function to run & measure the execution time for a sequence of n MAKE-SET, UNION, and FIND-SET operations
void run_experiment(int n, int m, ofstream &file) {
    DisjointSet ds(n);
    auto start = chrono::high_resolution_clock::now();

    // Perform n MAKE-SET operations
    for (int i = 0; i < n; i++) {
        ds.MAKE_SET(i);
    }

    // Execute remaining (m - n) operations
    for (int i = n; i < m; i++) {
        int op_type = rand() % 2; // Randomly choose between UNION (0) and FIND_SET (1)
        int x = rand() % n; // Random element for UNION or FIND_SET
        int y = rand() % n; // Random element for UNION

        if (op_type == 0) { // UNION
            ds.UNION(x, y);
        } else { // FIND_SET
            ds.FIND_SET(x);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;

    // Check consistency after operations
    bool is_consistent = ds.check_consistency(n);

    // Save results to file
    if (is_consistent) {
        file << n << "," << m << "," << elapsed_time.count() << ",Consistent" << endl;
    } else {
        file << n << "," << m << "," << elapsed_time.count() << ",Inconsistent" << endl;
    }
}

int main() {
    // int num_elements[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int num_elements[] = {1000};
    int num_operations[] = {1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000};

    ofstream file("part_A_1.csv");
    file << "Number of elements,Number of operations,Execution time,Consistency Check" << endl;

    // Run the experiment for all combinations of num_elements and num_operations
    for (int n : num_elements) {
        for (int m : num_operations) {
            if (n <= m) { // Ensure n is less than or equal to m
                run_experiment(n, m, file);
            }
        }
    }

    file.close();
    cout << "Experiment completed. Results saved to disjoint_set_experiment_results.csv" << endl;
    return 0;
}
