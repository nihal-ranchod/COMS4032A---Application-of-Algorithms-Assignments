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
    Element* parent;
    int rank;

    Element(int val) : value(val), next(nullptr), owner(nullptr), parent(this), rank(0) {}
};

struct Set {
    Element* head;
    Element* tail;
    int size;

    Set(Element* elem) : head(elem), tail(elem), size(1) {
        elem->owner = this;
    }
};

// Make-Set operation
Set* MakeSet(int value) {
    Element* elem = new Element(value);
    Set* newSet = new Set(elem);
    elem->owner = newSet;
    return newSet;
}

// Find-Set operation
Element* FindSet(Element* elem) {
    while (elem->parent != elem) {
        elem = elem->parent;
    }
    return elem;
}

// Brute-force Basic Union operation
void BasicUnion(Element* elem1, Element* elem2) {
    Element* root1 = FindSet(elem1);
    Element* root2 = FindSet(elem2);

    // If they are already in the same set, still go through the brute-force process
    Set* set1 = root1->owner;
    Set* set2 = root2->owner;

    Element* current1 = set1->head;
    while (current1 != nullptr) {
        current1->parent = root1;  // Re-assign parent pointers in set1 to root1 (even if already correct)
        current1 = current1->next;
    }

    Element* current2 = set2->head;
    while (current2 != nullptr) {
        current2->parent = root1;  // Re-assign parent pointers in set2 to root1
        current2 = current2->next;
    }

    // Optionally merge set1 and set2 (can be done inefficiently by iterating again)
    current1 = set1->head;
    if (current1 != nullptr) {
        while (current1->next != nullptr) {
            current1 = current1->next;  // Move to the end of set1
        }
        current1->next = set2->head;  // Merge set2 at the end of set1
    }
}


// Weighted Union operation with tail pointer
void WeightedUnion(Element* elem1, Element* elem2) {
    Element* root1 = FindSet(elem1);
    Element* root2 = FindSet(elem2);

    if (root1 == root2) return;

    Set* set1 = root1->owner;
    Set* set2 = root2->owner;

    if (set1->size >= set2->size) {
        set1->tail->next = set2->head;
        set1->tail = set2->tail;
        Element* current = set2->head;
        while (current != nullptr) {
            current->owner = set1;
            current->parent = root1;  // Update parent to root1
            current = current->next;
        }
        set1->size += set2->size;
    } else {
        set2->tail->next = set1->head;
        set2->tail = set1->tail;
        Element* current = set1->head;
        while (current != nullptr) {
            current->owner = set2;
            current->parent = root2;  // Update parent to root2
            current = current->next;
        }
        set2->size += set1->size;
    }
}

// Find-Set with path compression
Element* FindSetPathCompression(Element* elem) {
    if (elem->parent != elem) {
        elem->parent = FindSetPathCompression(elem->parent);
    }
    return elem->parent;
}

// Union-by-Rank operation
void UnionByRank(Element* elem1, Element* elem2) {
    Element* root1 = FindSetPathCompression(elem1);
    Element* root2 = FindSetPathCompression(elem2);

    if (root1 == root2) return;

    if (root1->rank < root2->rank) {
        root1->parent = root2;
    } else if (root1->rank > root2->rank) {
        root2->parent = root1;
    } else {
        root2->parent = root1;
        root1->rank++;
    }
}

// Validation check to ensure all elements are in the same set
bool validate_union(const vector<Element*>& elements) {
    Element* representative = FindSet(elements[0]);
    for (auto elem : elements) {
        if (FindSet(elem) != representative) {
            return false;
        }
    }
    return true;
}

// Run experiment function
void run_experiment(int n, ofstream &file, map<int, tuple<double, double, double>> &results) {
    vector<Element*> elements;
    for (int i = 0; i < n; i++) {
        elements.push_back(MakeSet(i)->head);
    }

    auto startUnion = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        BasicUnion(elements[0], elements[i]);
    }
    auto endUnion = chrono::high_resolution_clock::now();
    chrono::duration<double> union_elapsed_time = endUnion - startUnion;

    // Validate the union operation
    if (!validate_union(elements)) {
        cerr << "Error: BasicUnion failed for " << n << " elements." << endl;
    }

    elements.clear();
    for (int i = 0; i < n; i++) {
        elements.push_back(MakeSet(i)->head);
    }

    auto startWeightedUnion = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        WeightedUnion(elements[0], elements[i]);
    }
    auto endWeightedUnion = chrono::high_resolution_clock::now();
    chrono::duration<double> weighted_union_elapsed_time = endWeightedUnion - startWeightedUnion;

    // Validate the union operation
    if (!validate_union(elements)) {
        cerr << "Error: WeightedUnion failed for " << n << " elements." << endl;
    }

    elements.clear();
    for (int i = 0; i < n; i++) {
        elements.push_back(MakeSet(i)->head);
    }

    auto startUnionByRank = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        UnionByRank(elements[0], elements[i]);
    }
    auto endUnionByRank = chrono::high_resolution_clock::now();
    chrono::duration<double> union_by_rank_elapsed_time = endUnionByRank - startUnionByRank;

    // Validate the union operation
    if (!validate_union(elements)) {
        cerr << "Error: UnionByRank failed for " << n << " elements." << endl;
    }

    file << n << "," << union_elapsed_time.count() <<  "," << weighted_union_elapsed_time.count() << "," << union_by_rank_elapsed_time.count() << endl;
    results[n] = make_tuple(union_elapsed_time.count(), weighted_union_elapsed_time.count(), union_by_rank_elapsed_time.count());

    for (auto elem : elements) {
        delete elem;
    }
}

// Main function with averaging and output to a separate CSV file
int main() {
    int num_elements[] = {100, 500, 1000, 5000, 10000, 25000, 50000, 100000};
    int num_runs = 5;

    ofstream file("disjoint_set_experiment.csv");
    ofstream avg_file("disjoint_set_average_results.csv");

    file << "Number of elements,Union Execution time,Weighted Union Execution time,Union-by-Rank Execution time" << endl;
    avg_file << "Number of elements,Average Union Execution time,Average Weighted Union Execution time,Average Union-by-Rank Execution time" << endl;

    map<int, tuple<double, double, double>> results;

    for (int n : num_elements) {
        double union_time_sum = 0, weighted_union_time_sum = 0, union_by_rank_time_sum = 0;

        for (int run = 0; run < num_runs; run++) {
            run_experiment(n, file, results);
            auto [union_time, weighted_union_time, union_by_rank_time] = results[n];
            union_time_sum += union_time;
            weighted_union_time_sum += weighted_union_time;
            union_by_rank_time_sum += union_by_rank_time;
        }

        double avg_union_time = union_time_sum / num_runs;
        double avg_weighted_union_time = weighted_union_time_sum / num_runs;
        double avg_union_by_rank_time = union_by_rank_time_sum / num_runs;

        avg_file << n << "," << avg_union_time << "," << avg_weighted_union_time << "," << avg_union_by_rank_time << endl;
    }

    file.close();
    avg_file.close();

    return 0;
}
