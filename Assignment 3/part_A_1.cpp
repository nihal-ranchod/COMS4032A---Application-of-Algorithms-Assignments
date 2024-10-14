#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <tuple>
#include <algorithm> // For std::max

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* representative;
    int size; // Size of the set this node belongs to

    Node(int val) : value(val), next(nullptr), representative(this), size(1) {}
};

class DisjointSet {
private:
    vector<Node*> head;  // Points to the head of each linked list

public:
    DisjointSet(int n) {
        head.resize(n, nullptr);
    }

    void MAKE_SET(int x) {
        Node* node = new Node(x);
        head[x] = node;
    }

    Node* FIND_SET(int x) {
        Node* node = head[x];
        return node->representative;
    }

    void UNION(int x, int y) {
        Node* repX = FIND_SET(x);
        Node* repY = FIND_SET(y);

        if (repX != repY) {
            if (repX->size >= repY->size) {
                // Append the list of y to the list of x
                Node* temp = repX;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = repY;

                // Update the representative and size of all nodes in y's list
                Node* current = repY;
                while (current != nullptr) {
                    current->representative = repX;
                    current = current->next;
                }
                repX->size += repY->size;
            } else {
                // Append the list of x to the list of y
                Node* temp = repY;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = repX;

                // Update the representative and size of all nodes in x's list
                Node* current = repX;
                while (current != nullptr) {
                    current->representative = repY;
                    current = current->next;
                }
                repY->size += repX->size;
            }

        }
    }

    void printSet(int x) {
        Node* rep = FIND_SET(x);
        Node* current = head[x];
        while (current != nullptr) {
            if (current->representative == rep) {
                cout << current->value << " ";
            }
            current = current->next;
        }
        cout << endl;
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
