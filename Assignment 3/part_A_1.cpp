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
#include <map>
#include <tuple>
#include <algorithm> // For std::max

using namespace std;

class DisjointSet {
private:
    vector<int> parent;  
    vector<int> size;
    int make_set_count;
    int find_set_count;
    int union_count;

public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        make_set_count = 0;
        find_set_count = 0;
        union_count = 0;
    }

    void MAKE_SET(int x) {
        parent[x] = x;
        size[x] = 1;
        make_set_count++;
    }

    int FIND_SET(int x) {
        find_set_count++;
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    void UNION(int x, int y) {
        union_count++;
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

    bool check_consistency(int n) {
        for (int i = 0; i < n; ++i) {
            if (FIND_SET(i) != FIND_SET(FIND_SET(i))) {
                return false;
            }
        }
        return true;
    }

    int get_make_set_count() const { return make_set_count; }
    int get_find_set_count() const { return find_set_count; }
    int get_union_count() const { return union_count; }
};

void run_experiment(int n, ofstream &file, map<int, tuple<double, int, int, int, int>> &results) {
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
        file << n << "," << elapsed_time.count() << ",Consistent," << ds.get_make_set_count() << "," << ds.get_find_set_count() << "," << ds.get_union_count() << endl;
    } else {
        file << n << "," << elapsed_time.count() << ",Inconsistent," << ds.get_make_set_count() << "," << ds.get_find_set_count() << "," << ds.get_union_count() << endl;
    }

    if (results.find(n) == results.end()) {
        results[n] = make_tuple(elapsed_time.count(), 1, ds.get_make_set_count(), ds.get_find_set_count(), ds.get_union_count());
    } else {
        auto &val = results[n];
        get<0>(val) += elapsed_time.count();
        get<1>(val) += 1;
        get<2>(val) += ds.get_make_set_count();
        get<3>(val) += ds.get_find_set_count();
        get<4>(val) += ds.get_union_count();
    }
}

int main() {
    int num_elements[] = {100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};
    int num_runs = 10;

    ofstream file("part_A_1.csv");
    file << "Number of elements,Execution time,Consistency Check,MAKE_SET Count,FIND_SET Count,UNION Count" << endl;

    ofstream avg_file("part_A_1_averaged.csv");
    avg_file << "Number of elements,Average Execution time,Average MAKE_SET Count,Average FIND_SET Count,Average UNION Count" << endl;

    map<int, tuple<double, int, int, int, int>> results;

    for (int n : num_elements) {
        for (int run = 0; run < num_runs; run++) {
            run_experiment(n, file, results);
        }
    }

    for (const auto &entry : results) {
        int n = entry.first;
        auto val = entry.second;
        double avg_time = get<0>(val) / get<1>(val);
        double avg_make_set = static_cast<double>(get<2>(val)) / get<1>(val);
        double avg_find_set = static_cast<double>(get<3>(val)) / get<1>(val);
        double avg_union = static_cast<double>(get<4>(val)) / get<1>(val);
        avg_file << n << "," << avg_time << "," << avg_make_set << "," << avg_find_set << "," << avg_union << endl;
    }

    file.close();
    avg_file.close();
    cout << "Experiment completed. Results saved to part_A_1.csv and part_A_1_averaged.csv" << endl;
    return 0;
}