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

    void treeInsert(int key) {
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

    TreeNode* treeMinimum(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void transplant(TreeNode* u, TreeNode* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void treeDelete(TreeNode* node) {
        if (node->left == nullptr) {
            transplant(node, node->right);
        } else if (node->right == nullptr) {
            transplant(node, node->left);
        } else {
            TreeNode* temp = treeMinimum(node->right); // Successr of the node
            if (temp->parent != node) {
                transplant(temp, temp->right);
                temp->right = node->right;
                temp->right->parent = temp;
            }
            transplant(node, temp);
            temp->left = node->left;
            temp->left->parent = temp;
        }
    }

    void inOrderTreeWalk(TreeNode* node) {
        if (node != nullptr) {
            inOrderTreeWalk(node->left);
            cout << node->key << " ";
            inOrderTreeWalk(node->right);
        }
    }

    void displayTree() {
        cout << "Inorder Traversal of the Tree: ";
        inOrderTreeWalk(root);
        cout << endl;
    }

    int calculateHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int left_height = calculateHeight(node->left);
            int right_height = calculateHeight(node->right);

            if (left_height > right_height) {
                return left_height + 1;
            } else {
                return right_height + 1;
            }
        }
    }
};
