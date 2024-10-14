#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Set;
struct Element;

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
public:
    vector<Set*> sets;

    DisjointSet(int n) {
        sets.reserve(n);
    }

    void MAKE_SET(int x) {
        Element* elem = new Element(x);
        Set* newSet = new Set(elem);
        sets.push_back(newSet);
    }

    Set* FIND_SET(Element* elem) {
        return elem->owner;
    }

    void UNION(int x, int y) {
        Set* setX = FIND_SET(sets[x]->head);
        Set* setY = FIND_SET(sets[y]->head);

        if (setX != setY) {
            // Weighted union heuristic
            if (setX->size < setY->size) {
                swap(setX, setY);
            }
            // Attach setY to setX
            setX->tail->next = setY->head;
            setX->tail = setY->tail;
            Element* current = setY->head;
            while (current) {
                current->owner = setX;
                current = current->next;
            }
            setX->size += setY->size;
            delete setY;
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
