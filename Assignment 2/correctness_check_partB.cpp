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
        ost.treeInsert(value);
    }

    // Display the tree
    ost.displayTree();

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
    cout << "Delete root " << node->key << ": " << endl;
    ost.treeDelete(node);
    ost.displayTree();
    cout << "New root " << ost.root->key << endl;

    // Insert another key after delete
    int newKey = 10;
    ost.treeInsert(newKey);
    cout << "Inserted key " << newKey << " after deletion." << endl;
    ost.displayTree();

    return 0;
}