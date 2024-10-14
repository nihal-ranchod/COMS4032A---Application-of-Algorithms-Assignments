#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Element {
    int value;
    Element* parent;
    int rank;

    Element(int val) : value(val), parent(this), rank(0) {}  // Initially, an element is its own parent.
};

struct Set {
    Element* head;  // Points to an element in the set
    int size;

    Set(Element* elem) : head(elem), size(1) {}
};

class DisjointSet {
public:
    vector<Set*> sets;  // Stores all sets

    DisjointSet(int n) {
        sets.reserve(n);
    }

    void MAKE_SET(int x) {
        Element* elem = new Element(x);
        Set* newSet = new Set(elem);
        sets.push_back(newSet);  // Create a new set for the element.
    }

    // Path compression heuristic
    Element* FIND_SET(Element* elem) {
        if (elem->parent != elem) {
            elem->parent = FIND_SET(elem->parent);  // Recursively find the root and compress the path.
        }
        return elem->parent;
    }

    void UNION(int x, int y) {
        Element* rootX = FIND_SET(sets[x]->head);
        Element* rootY = FIND_SET(sets[y]->head);

        if (rootX != rootY) {
            // Union by rank heuristic
            if (rootX->rank < rootY->rank) {
                rootX->parent = rootY;  // Attach smaller rank tree under larger rank tree.
            } else if (rootX->rank > rootY->rank) {
                rootY->parent = rootX;  // Attach smaller rank tree under larger rank tree.
            } else {
                rootY->parent = rootX;  // Attach one tree under the other.
                rootX->rank++;  // Increase the rank of the new root.
            }
            // Optionally, you can update the size of the new root set if needed
            // sets[x]->size += sets[y]->size; // Update size here if needed
        }
    }

    ~DisjointSet() {
        // Clean up allocated memory for elements and sets.
        for (auto elem : sets) {
            delete elem->head;  // Deleting the head element.
            delete elem;        // Deleting the set.
        }
    }
};

void run_experiment(int n, ofstream &file, map<int, tuple<double, int>> &results) {
    DisjointSet ds(n);
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        ds.MAKE_SET(i);  // Create individual sets for each element.
    }

    for (int i = 1; i < n; i++) {
        ds.UNION(0, i);  // Union all elements with the first element.
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;

    file << n << "," << elapsed_time.count() << endl;

    if (results.find(n) == results.end()) {
        results[n] = make_tuple(elapsed_time.count(), 1);
    } else {
        auto &val = results[n];
        get<0>(val) += elapsed_time.count();
        get<1>(val) += 1;
    }
}

int main() {
    int num_elements[] = {100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 250000};
    int num_runs = 5;

    ofstream file("part_A_2.csv");
    file << "Number of elements,Execution time" << endl;

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
