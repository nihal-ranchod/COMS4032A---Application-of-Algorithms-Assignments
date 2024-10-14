#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Set;

struct Element {
    int value;
    Element* next;
    Set* owner;

    Element(int val) : value(val), next(nullptr), owner(nullptr) {}
};

struct Set {
    Element* head;
    Element* tail;
    int size;

    Set(Element* elem) : head(elem), tail(elem), size(1) {
        elem->owner = this;
    }
};

class DisjointSet {
private:
    vector<Element*> elements;

public:
    DisjointSet(int n) {
        elements.resize(n, nullptr);
    }

    void MAKE_SET(int x) {
        Element* elem = new Element(x);
        elements[x] = elem;
        new Set(elem);
    }

    Set* FIND_SET(int x) {
        return elements[x]->owner;
    }

    void UNION(int x, int y) {
        Set* setX = FIND_SET(x);
        Set* setY = FIND_SET(y);

        if (setX != setY) {
            Set* extended_set;
            Set* discarded_set;

            // Choose the larger set to be the extended set
            if (setX->size >= setY->size) {
                extended_set = setX;
                discarded_set = setY;
            } else {
                extended_set = setY;
                discarded_set = setX;
            }

            // Link the tail of the extended set to the head of the discarded set
            extended_set->tail->next = discarded_set->head;
            extended_set->tail = discarded_set->tail;
            extended_set->size += discarded_set->size;

            // Update the owner of all elements in the discarded set
            Element* current = discarded_set->head;
            while (current != nullptr) {
                current->owner = extended_set;
                current = current->next;
            }

            // Free memory of discarded set
            delete discarded_set;
        }
    }

    void printSet(int x) {
        Set* set = FIND_SET(x);
        Element* current = set->head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor to free all allocated memory
    ~DisjointSet() {
        for (Element* elem : elements) {
            if (elem) {
                delete elem;
            }
        }
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

    ofstream file("part_A_1.csv");
    file << "Number of elements,Execution time" << endl;

    ofstream avg_file("part_A_1_averaged.csv");
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
    cout << "Experiment completed. Results saved to part_A_1.csv and part_A_1_averaged.csv" << endl;
    return 0;
}
