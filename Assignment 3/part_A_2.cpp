#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
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

void run_experiment(int n, ofstream &file, map<int, tuple<double, int>> &results) {
    DisjointSet ds(n);
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        ds.MAKE_SET(i);
    }

    for (int i = 1; i < n; i++) {
        ds.UNION(0, i);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;

    bool is_consistent = ds.check_consistency(n);

    if (is_consistent) {
        file << n << "," << elapsed_time.count() << ",Consistent" << endl;
    } else {
        file << n << "," << elapsed_time.count() << ",Inconsistent" << endl;
    }

    if (results.find(n) == results.end()) {
        results[n] = make_tuple(elapsed_time.count(), 1);
    } else {
        auto &val = results[n];
        get<0>(val) += elapsed_time.count();
        get<1>(val) += 1;
    }
}

int main() {
    int num_elements[] = {1000, 5000, 10000, 50000, 100000, 250000, 500000, 750000, 1000000};
    int num_runs = 10;

    ofstream file("part_A_2.csv");
    file << "Number of elements,Execution time,Consistency Check" << endl;

    ofstream avg_file("part_A_2_averaged.csv");
    avg_file << "Number of elements,Average Execution time" << endl;

    map<int, tuple<double, int>> results;

    for (int n : num_elements) {
        for (int run = 0; run < num_runs; run++) {
            run_experiment(n, file, results);
        }
    }

    for (const auto &entry : results) {
        int n = entry.first;
        auto val = entry.second;
        double avg_time = get<0>(val) / get<1>(val);
        avg_file << n << "," << avg_time << endl;
    }

    file.close();
    avg_file.close();
    cout << "Experiment completed. Results saved to part_A_2.csv and part_A_2_averaged.csv" << endl;
    return 0;
}