#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "part_B_algorithms.cpp"

using namespace std;

int main() {
    OrderStatisticTree ost;

    // Insert values into the tree
    vector<int> values = {10, 5, 15, 3, 7, 12, 18, 1, 4, 6, 8};
    for (int value : values) {
        ost.treeInsert(value);
    }

    // Display the tree
    ost.displayTree();
    cout << endl;

    // Insert new node: 13
    int key = 13;
    ost.treeInsert(key);
    cout << "Inserted key " << key << endl;
    ost.displayTree();
      cout << endl;

    // Delete root: 10
    ost.treeDelete(ost.root);
    cout << "Deleted root 10" << endl;
    ost.displayTree();
    cout << "New root: " << ost.root->key << endl;
    cout << endl;

    // Delete node: 5
    TreeNode* node5 = ost.root->left; // assuming that node 5 was the left child of root
    cout << "Delete node " << node5->key << ": " << endl;
    ost.treeDelete(node5);
    ost.displayTree();
    cout << "New left child of root: " << ost.root->left->key << endl;

    return 0;
}