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
    int size; // Size of the subtree rooted at this node
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int value) : key(value), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct BinarySearchTree {
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

    void TreeInsert(int key) {
        TreeNode* new_node = new TreeNode(key);
        TreeNode* y = nullptr;
        TreeNode* x = root;

        while (x != nullptr) {
            y = x;
            x->size++; // Increment size of the subtree
            if (new_node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        new_node->parent = y;
        if (y == nullptr) {
            root = new_node;
        } else if (new_node->key < y->key) {
            y->left = new_node;
        } else {
            y->right = new_node;
        }
    }

    void Transplant(TreeNode* u, TreeNode* v) {
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

    void TreeDelete(TreeNode* node, int key) {
        TreeNode* y = node;
        while (y != nullptr) {
            y->size--; // Decrement size of the subtree
            y = y->parent;
        }

        if (node->left == nullptr) {
            Transplant(node, node->right);
        } else if (node->right == nullptr) {
            Transplant(node, node->left);
        } else {
            TreeNode* temp = TreeMinimum(node->right);
            if (temp->parent != node) {
                Transplant(temp, temp->right);
                temp->right = node->right;
                temp->right->parent = temp;
            }
            Transplant(node, temp);
            temp->left = node->left;
            temp->left->parent = temp;
        }
    }

    TreeNode* TreeMinimum(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* OS_Search(TreeNode* node, int i) {
        if (node == nullptr) {
        return nullptr;
        }

        int r = (node->left ? node->left->size : 0) + 1;
        if (i == r) {
            return node;
        } else if (i < r) {
            return OS_Search(node->left, i);
        } else {
            return OS_Search(node->right, i - r);
        }
    }

    int OS_Rank(TreeNode* node) {
        int r = (node->left ? node->left->size : 0) + 1;
        TreeNode* y = node;
        while (y != root) {
            if (y == y->parent->right) {
                r += (y->parent->left ? y->parent->left->size : 0) + 1;
            }
            y = y->parent;
        }
        return r;
    }

    void InorderTreeWalk(TreeNode* node) {
        if (node != nullptr) {
            InorderTreeWalk(node->left);
            cout << "Key: " << node->key << ", Size: " << node->size << " | ";
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