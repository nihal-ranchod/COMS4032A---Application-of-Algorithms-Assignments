#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <tuple>

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
    int rank;

    Set(Element* elem) : head(elem), tail(elem), rank(0) {
        elem->owner = this;
    }
};

class DisjointSet {
private:
    vector<Element*> elements;
    vector<Set*> sets;

public:
    DisjointSet(int n) {
        elements.resize(n, nullptr);
        sets.reserve(n); // Reserve memory for sets
    }

    void MAKE_SET(int x) {
        Element* elem = new Element(x);
        elements[x] = elem;
        Set* newSet = new Set(elem);
        sets.push_back(newSet); // Store reference to manage memory
    }

    Element* FIND_SET(int x) {
        Element* elem = elements[x];
        if (elem->owner->head != elem) {
            elem->owner->head = FIND_SET(elem->owner->head->value); // Path compression heuristic
        }
        return elem->owner->head;
    }

    void LINK(Set* setX, Set* setY) {
        if (setX->rank > setY->rank) {
            setY->head->owner = setX;
            setX->tail->next = setY->head;
            setX->tail = setY->tail;
        } else {
            setX->head->owner = setY;
            setY->tail->next = setX->head;
            setY->tail = setX->tail;
            if (setX->rank == setY->rank) {
                setY->rank++;
            }
        }
    }

    void UNION(int x, int y) {
        Element* repX = FIND_SET(x);
        Element* repY = FIND_SET(y);

        if (repX != repY) {
            LINK(repX->owner, repY->owner);
        }
    }

    void printSet(int x) {
        Set* set = elements[x]->owner;
        Element* current = set->head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor to free allocated memory
    ~DisjointSet() {
        for (Element* elem : elements) {
            delete elem;
        }
        for (Set* set : sets) {
            delete set;
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
