#include <iostream>

struct TreeNode {
    int data;
    TreeNode* parent;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    TreeNode(int val, TreeNode* parent = nullptr)
        : data(val), parent(parent), firstChild(nullptr), nextSibling(nullptr) {}
};

class Tree {
private:
    TreeNode* root;

public:
    Tree() : root(nullptr) {}

    // Додавання елемента до дерева
    void addNode(int value, int parentValue = -1) {
        TreeNode* newNode = new TreeNode(value);

        if (!root) {
            root = newNode;
        }
        else {
            TreeNode* parentNode = findNode(parentValue);
            if (parentNode) {
                if (!parentNode->firstChild) {
                    parentNode->firstChild = newNode;
                }
                else {
                    TreeNode* sibling = parentNode->firstChild;
                    while (sibling->nextSibling) {
                        sibling = sibling->nextSibling;
                    }
                    sibling->nextSibling = newNode;
                }
                newNode->parent = parentNode;
            }
            else {
                std::cerr << "Error: Parent node not found.\n";
                delete newNode;
            }
        }
    }

    // Пошук елемента у дереві
    TreeNode* findNode(int value, TreeNode* startNode = nullptr) {
        if (!startNode) {
            startNode = root;
        }

        if (!startNode) {
            return nullptr;
        }

        if (startNode->data == value) {
            return startNode;
        }

        TreeNode* child = startNode->firstChild;
        while (child) {
            TreeNode* result = findNode(value, child);
            if (result) {
                return result;
            }
            child = child->nextSibling;
        }

        return nullptr;
    }

    // Видалення елемента з дерева
    void deleteNode(int value) {
        TreeNode* nodeToDelete = findNode(value);
        if (!nodeToDelete) {
            std::cerr << "Error: Node not found.\n";
            return;
        }

        TreeNode* parentNode = nodeToDelete->parent;

        if (parentNode) {
            if (parentNode->firstChild == nodeToDelete) {
                parentNode->firstChild = nodeToDelete->nextSibling;
            }
            else {
                TreeNode* sibling = parentNode->firstChild;
                while (sibling->nextSibling != nodeToDelete) {
                    sibling = sibling->nextSibling;
                }
                sibling->nextSibling = nodeToDelete->nextSibling;
            }
        }
        else {
            delete root;
            root = nullptr;
        }

        deleteSubtree(nodeToDelete);
    }

    // Показ шляху при знаходженні елемента при прямому обході дерева
    void showPathPreorder(int value) {
        std::cout << "Path for value " << value << " (Preorder): ";
        showPathPreorderHelper(root, value);
        std::cout << "\n";
    }

    // Показ шляху при знаходженні елемента при зворотному обході дерева
    void showPathPostorder(int value) {
        std::cout << "Path for value " << value << " (Postorder): ";
        showPathPostorderHelper(root, value);
        std::cout << "\n";
    }

    // Показ шляху при знаходженні елемента при симетричному обході дерева
    void showPathInorder(int value) {
        std::cout << "Path for value " << value << " (Inorder): ";
        showPathInorderHelper(root, value);
        std::cout << "\n";
    }

private:
    // Допоміжна функція для рекурсивного видалення піддерева
    void deleteSubtree(TreeNode* node) {
        if (!node) {
            return;
        }

        TreeNode* child = node->firstChild;
        while (child) {
            TreeNode* nextChild = child->nextSibling;
            deleteSubtree(child);
            child = nextChild;
        }

        delete node;
    }

    // Допоміжна функція для прямого обходу дерева та показу шляху
    void showPathPreorderHelper(TreeNode* currentNode, int value) {
        if (!currentNode) {
            return;
        }

        std::cout << currentNode->data << " ";

        if (currentNode->data == value) {
            return;
        }

        TreeNode* child = currentNode->firstChild;
        while (child) {
            showPathPreorderHelper(child, value);
            child = child->nextSibling;
        }
    }

    // Допоміжна функція для зворотного обходу дерева та показу шляху
    void showPathPostorderHelper(TreeNode* currentNode, int value) {
        if (!currentNode) {
            return;
        }

        TreeNode* child = currentNode->firstChild;
        while (child) {
            showPathPostorderHelper(child, value);
            child = child->nextSibling;
        }

        std::cout << currentNode->data << " ";

        if (currentNode->data == value) {
            return;
        }
    }

    // Допоміжна функція для симетричного обходу дерева та показу шляху
    void showPathInorderHelper(TreeNode* currentNode, int value) {
        if (!currentNode) {
            return;
        }

        TreeNode* child = currentNode->firstChild;
        while (child) {
            showPathInorderHelper(child, value);
            std::cout << currentNode->data << " ";

            if (currentNode->data == value) {
                return;
            }

            child = child->nextSibling;
        }
    }
};

int main() {
    Tree tree;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Node\n";
        std::cout << "2. Delete Node\n";
        std::cout << "3. Find Node and Show Path (Preorder)\n";
        std::cout << "4. Find Node and Show Path (Postorder)\n";
        std::cout << "5. Find Node and Show Path (Inorder)\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value, parentValue;
            std::cout << "Enter the value to add: ";
            std::cin >> value;
            std::cout << "Enter the parent value (or -1 for root): ";
            std::cin >> parentValue;
            tree.addNode(value, parentValue);
            break;
        }
        case 2: {
            int value;
            std::cout << "Enter the value to delete: ";
            std::cin >> value;
            tree.deleteNode(value);
            break;
        }
        case 3: {
            int value;
            std::cout << "Enter the value to find and show path (Preorder): ";
            std::cin >> value;
            tree.showPathPreorder(value);
            break;
        }
        case 4: {
            int value;
            std::cout << "Enter the value to find and show path (Postorder): ";
            std::cin >> value;
            tree.showPathPostorder(value);
            break;
        }
        case 5: {
            int value;
            std::cout << "Enter the value to find and show path (Inorder): ";
            std::cin >> value;
            tree.showPathInorder(value);
            break;
        }
        case 6:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}