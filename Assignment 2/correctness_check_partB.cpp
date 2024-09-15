#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "part_B_algorithms.cpp"

using namespace std;

int main() {
    BinarySearchTree bst;

    // Insert values into the tree
    vector<int> values = {5, 3, 7, 2, 4, 6, 8};
    for (int value : values) {
        bst.TreeInsert(value);
    }

    // Display the tree
    bst.DisplayTree();

    // Search for the 3rd smallest element
    TreeNode* node = bst.OS_Search(bst.root, 3);
    if (node != nullptr) {
        cout << "3rd smallest element: " << node->key << endl;
    } else {
        cout << "Element not found" << endl;
    }

    // Get the rank of a node
    int rank = bst.OS_Rank(node);
    cout << "Rank of node with key " << node->key << ": " << rank << endl;

    // Delete a node
    bst.TreeDelete(node);
    bst.DisplayTree();

    // Insert another key after delete
    int newKey = 10;
    bst.TreeInsert(newKey);
    cout << "Inserted key " << newKey << " after deletion." << endl;
    bst.DisplayTree();

    return 0;
}