#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;
};

class AVLTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int data) {
        if (!node) {
            return new TreeNode{ data, nullptr, nullptr, 0 };
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        }
        else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        return balance(node);
    }

    TreeNode* remove(TreeNode* node, int data) {
        if (!node) {
            return nullptr;
        }
        if (data < node->data) {
            node->left = remove(node->left, data);
        }
        else if (data > node->data) {
            node->right = remove(node->right, data);
        }
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else {
                TreeNode* minRight = min(node->right);
                node->data = minRight->data;
                node->right = remove(node->right, minRight->data);
            }
        }
        return balance(node);
    }

    void print(TreeNode* node, int depth = 0) {
        if (node) {
            print(node->right, depth + 1);
            for (int i = 0; i < depth; i++) {
                cout << "    ";
            }
            cout << node->data << endl;
            print(node->left, depth + 1);
        }
    }

    int height(TreeNode* node) {
        if (node) {
            return node->height;
        }
        return -1;
    }

    int balanceFactor(TreeNode* node) {
        if (node) {
            return height(node->left) - height(node->right);
        }
        return 0;
    }

    void updateHeight(TreeNode* node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    TreeNode* rotateRight(TreeNode* root) {
        TreeNode* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        updateHeight(root);
        updateHeight(newRoot);
        return newRoot;
    }

    TreeNode* rotateLeft(TreeNode* root) {
        TreeNode* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        updateHeight(root);
        updateHeight(newRoot);
        return newRoot;
    }

    TreeNode* balance(TreeNode* node) {
        updateHeight(node);
        int factor = balanceFactor(node);
        if (factor > 1) {
            if (balanceFactor(node->left) >= 0) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        if (factor < -1) {
            if (balanceFactor(node->right) <= 0) {
                return rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    TreeNode* min(TreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

public:
    AVLTree() {
        this->root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    void ShowAll() {
        if (root) {
            cout << "---------------------------" << endl;
            print(root);
        }
    }
};

int main() {
    AVLTree tree;
    int option;
    int value;

    while (true) {
        cout << "\t Menu";
        cout << "\n1. Add";
        cout << "\n2. Remove";
        cout << "\n3. Show";
        cout << "\n4. Default value\n";
        cout << "Your input: ";

        cin >> option;

        if (option == 1) {
            cout << "Input: ";
            cin >> value;
            tree.insert(value);
        }
        if (option == 2) {
            cout << "Input: ";
            cin >> value;
            tree.remove(value);
        }
        if (option == 3) {
            tree.ShowAll();
        }
        if (option == 4) {
            tree.insert(6);
            tree.insert(2);
            tree.ShowAll();
            tree.insert(4);
            tree.ShowAll();
            tree.insert(5);
            tree.ShowAll();
            tree.insert(7);
            tree.ShowAll();
            tree.insert(8);
            tree.ShowAll();
            tree.insert(3);
            tree.ShowAll();
        }
    }


}