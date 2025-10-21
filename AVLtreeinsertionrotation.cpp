#include <iostream>
#include <algorithm> // For std::max

// AVL tree node structure
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    // Get height of a node
    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Get balance factor of a node
    int getBalance(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Update height of a node
    void updateHeight(AVLNode* node) {
        if (node != nullptr)
            node->height = 1 + std::max(height(node->left), height(node->right));
    }

    // Right rotation
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x; // New root of the subtree
    }

    // Left rotation
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y; // New root of the subtree
    }

    // Insert a key into the AVL tree
    AVLNode* insert(AVLNode* node, int key) {
        // Perform standard BST insertion
        if (node == nullptr)
            return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // Duplicate keys are not allowed in this implementation
            return node;

        // Update height of current node
        updateHeight(node);

        // Get balance factor and rebalance if needed
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the (potentially unchanged) node pointer
    }

    // Public insert function
    void insert(int key) {
        root = insert(root, key);
    }

    // Preorder traversal for verification
    void preOrder(AVLNode* node) {
        if (node != nullptr) {
            std::cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }
};

int main() {
    AVLTree avl;

    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    std::cout << "Preorder traversal of the constructed AVL tree is: ";
    avl.preOrder(avl.root);
    std::cout << std::endl;

    return 0;
}
