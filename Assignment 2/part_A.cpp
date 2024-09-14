#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream> 

using namespace std;
using namespace std::chrono;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int value) : key(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct BinarySearchTree {
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

    void TreeInsert(int key) {
        TreeNode* new_node = new TreeNode(key); // Create a new node with the given key value
        TreeNode* y = nullptr; // Hold the parent node of the new node
        TreeNode* x = root; // Start from the root node

        while (x != nullptr) {
            y = x;
            if (new_node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        new_node->parent = y; // Set the parent of the new node to y
        if (y == nullptr) {
            root = new_node; // Tree is empty, so the new node is the root
        } else if (new_node->key < y->key) {
            y->left = new_node; // Insert new node as the left child
        } else {
            y->right = new_node; // Insert new node as the right child
        }
    }

    void InorderTreeWalk(TreeNode* node) {
        if (node != nullptr) {
            InorderTreeWalk(node->left);
            cout << node->key << " ";
            InorderTreeWalk(node->right);
        }
    }

    void DisplayTree() {
        cout << "Inorder Traversal of the Tree: ";
        InorderTreeWalk(root);
        cout << endl;
    }

    int CalculateHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int left_height = CalculateHeight(node->left);
            int right_height = CalculateHeight(node->right);

            if (left_height > right_height) {
                return left_height + 1;
            } else {
                return right_height + 1;
            }
        }
    }
};

int main() {
    srand(time(0));

    vector<int> keys;
    vector<double> heights;
    vector<double> buildTimes;

    int nValues[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

    ofstream file("bst_results.csv");
    file << "n,avg_height,avg_build_time" << endl;

    for (int n : nValues) {
        double totalHeight = 0;
        double totalBuildTime = 0;

        int trials = 10;

        for (int i = 0; i < trials; i++) {
            keys.clear();
            for (int t = 0; t < n; t++) {
                keys.push_back(t + 1);
            }
            random_shuffle(keys.begin(), keys.end());

            BinarySearchTree bst;
            auto start = high_resolution_clock::now();
            for (int key : keys) {
                bst.TreeInsert(key);
            }
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            totalBuildTime += duration.count();

            totalHeight += bst.CalculateHeight(bst.root);
        }

        double avgHeight = totalHeight / trials;
        double avgBuildTime = totalBuildTime / trials;

        file << n << "," << avgHeight << "," << avgBuildTime << endl;
    }
    
    file.close();

    cout << "Results have been saved to bst_results.csv" << endl;

    return 0;
}