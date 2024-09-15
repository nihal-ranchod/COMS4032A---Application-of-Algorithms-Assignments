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

struct OrderStatisticTree {
    TreeNode* root;

    OrderStatisticTree() : root(nullptr) {}

    void treeInsert(int key) {
        TreeNode* z = new TreeNode(key);
        TreeNode* y = nullptr;
        TreeNode* x = root;

        while (x != nullptr) {
            y = x;
            x->size++; // Increment size of subtree
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
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

    TreeNode* treeMinimum(TreeNode* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    void updateSize(TreeNode* node) {
        while (node != nullptr) {
            int newSize = 1;  // Initialize with 1 to count the node itself
            if (node->left != nullptr) {
                newSize += node->left->size;
            }
            if (node->right != nullptr) {
                newSize += node->right->size;
            }

            // Only update if the size actually changes
            if (newSize == node->size) {
                break;  // No further updates needed if size hasn't changed
            }

            node->size = newSize;  // Update the size of the current node
            node = node->parent;   // Move up to the parent
        }
    }

    void treeDelete(TreeNode* z) {
        TreeNode* affectedNode = nullptr;

        if (z->left == nullptr) {
            transplant(z, z->right);
            affectedNode = z->parent;  // The parent of the deleted node is affected
        } else if (z->right == nullptr) {
            transplant(z, z->left);
            affectedNode = z->parent;  // The parent of the deleted node is affected
        } else {
            TreeNode* y = treeMinimum(z->right);  // Find the successor (minimum in right subtree)
            affectedNode = y->parent != z ? y->parent : y;  // Find the affected node for size updates

            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }

        delete z;

        // Update the sizes starting from the affected node (successor or parent of z)
        if (affectedNode != nullptr) {
            updateSize(affectedNode);
        }
    }

    TreeNode* OS_Search(TreeNode* node, int i) {
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

    void inorderTreeWalk(TreeNode* node) {
        if (node != nullptr) {
            inorderTreeWalk(node->left);
            cout << "Key: " << node->key << ", Size: " << node->size << " | ";
            inorderTreeWalk(node->right);
        }
    }

    void displayTree() {
        cout << "Inorder Traversal of the Tree: ";
        inorderTreeWalk(root);
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