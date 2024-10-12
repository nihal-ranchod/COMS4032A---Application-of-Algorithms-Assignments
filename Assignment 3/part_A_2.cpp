#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>  // For assertions
#include <cstdlib>  // For rand()

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

public:
    DisjointSet(int n) {
        elements.resize(n);
        for (int i = 0; i < n; i++) {
            elements[i].p = i; // Initialize each element to be its own parent
            elements[i].rank = 0; // Initialize rank
        }
    }

    // Make-Set Operation: Initializes a single set for element x.
    void MAKE_SET(int x) {
        elements[x].p = x;
        elements[x].rank = 0; // Initialize rank
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
        int y = (op_type == 0) ? (rand() % n) : 0; // Only choose y if operation is UNION

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

    ofstream file("part_A_2.csv");
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
    cout << "Experiment completed. Results saved to part_A_2.csv" << endl;
    return 0;
}
