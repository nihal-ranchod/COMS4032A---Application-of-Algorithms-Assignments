#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "part_B_algorithms.cpp"

using namespace std;

int main() {
    OrderStatisticTree ost;

    // Insert values into the tree
    vector<int> values = {5, 3, 7, 2, 4, 6, 8};
    for (int value : values) {
        ost.TreeInsert(value);
    }

    // Display the tree
    ost.DisplayTree();

    // Search for the 3rd smallest element
    TreeNode* node = ost.OS_Search(ost.root, 3);
    if (node != nullptr) {
        cout << "3rd smallest element: " << node->key << endl;
    } else {
        cout << "Element not found" << endl;
    }

    // Get the rank of a node
    int rank = ost.OS_Rank(node);
    cout << "Rank of node with key " << node->key << ": " << rank << endl;

    // Delete a node
    cout << "Delete node with key " << node->key << ": " << endl;
    ost.TreeDelete(node);
    ost.DisplayTree();

    // Insert another key after delete
    int newKey = 10;
    ost.TreeInsert(newKey);
    cout << "Inserted key " << newKey << " after deletion." << endl;
    ost.DisplayTree();

    return 0;
}