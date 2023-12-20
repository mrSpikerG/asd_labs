
#include <iostream>
using namespace std;


struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : key(x), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, int key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key);
        }
        else {
            node->right = insertNode(node->right, key);
        }

        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node == nullptr) return node;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* searchNode(TreeNode* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (node->key < key) {
            return searchNode(node->right, key);
        }

        return searchNode(node->left, key);
    }

    void printTree(TreeNode* node, int space) {
        if (node == nullptr) return;

        space += 4;

        printTree(node->right, space);

        cout << endl;
        for (int i = 0; i < space; i++) {
            cout << " ";
        }
        cout << node->key << endl;

        printTree(node->left, space);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        return searchNode(root, key) != nullptr;
    }

    void display() {
        cout << "======================" << endl;
        printTree(root, 0);
        cout << endl << "======================" << endl;
    }
};



int main()
{
    BinarySearchTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);

    int option;
    int key;

    while (true) {
        tree.display();

        cout << "=======Choose option=========" << endl;
        cout << "1. Add" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Find" << endl;
            
        cin >> option;

        if (option == 1) {
            cout << "Enter key: ";
            cin >> key;
            tree.insert(key);
        }
        if (option == 2) {
            cout << "Enter key: ";
            cin >> key;
            tree.remove(key);
        }
        if (option == 3) {
            cout << "Enter key: ";
            cin >> key;
            cout << "Result = " << tree.search(key) << endl;
        }
    }
}