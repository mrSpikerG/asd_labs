#include <iostream>

class TreeNode {
public:
    int data;
    TreeNode* next;

    TreeNode(int item) : data(item), next(nullptr) {}
};

class CustomQueue {
private:
    TreeNode* front;
    TreeNode* back;

public:
    CustomQueue() : front(nullptr), back(nullptr) {}

    void enqueue(int item) {
        TreeNode* newNode = new TreeNode(item);
        if (isEmpty()) {
            front = newNode;
            back = newNode;
        }
        else {
            back->next = newNode;
            back = newNode;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            int frontData = front->data;
            TreeNode* temp = front;
            front = front->next;
            delete temp;
            return frontData;
        }
        return -1; 
    }

    void swapFirstLast() {
        
        if (!front || !front->next)
        {
            return;
        }


        TreeNode* prev = nullptr;
        TreeNode* current = front;

        while (current->next)
        {
            prev = current;
            current = current->next;
        }

        int tmp = front->data;
        front->data = current->data;
        current->data = tmp;
    }

    void reverse() {
        TreeNode* prev = nullptr;
        TreeNode* current = front;
        TreeNode* next = nullptr;
        back = front;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        front = prev;
    }

    bool contains(int element) {
        TreeNode* temp = front;
        while (temp != nullptr) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void display() {
        TreeNode* temp = front;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    CustomQueue queue;
    int choice;
    int item;

    do {
        std::cout << "1. Add an item to the queue" << std::endl;
        std::cout << "2. Remove an item from the queue" << std::endl;
        std::cout << "3. Swap the first and last elements of the queue" << std::endl;
        std::cout << "4. Reverse the queue" << std::endl;
        std::cout << "5. Check if a specified element belongs to the queue" << std::endl;
        std::cout << "6. Remove all items from the queue" << std::endl;
        std::cout << "7. Display the queue" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter an item to add: ";
            std::cin >> item;
            queue.enqueue(item);
            break;
        case 2:
            item = queue.dequeue();
            if (item != -1) {
                std::cout << "Removed item: " << item << std::endl;
            }
            else {
                std::cout << "The queue is empty" << std::endl;
            }
            break;
        case 3:
            queue.swapFirstLast();
            break;
        case 4:
            queue.reverse();
            break;
        case 5:
            std::cout << "Enter an item to check: ";
            std::cin >> item;
            if (queue.contains(item)) {
                std::cout << "The item belongs to the queue" << std::endl;
            }
            else {
                std::cout << "The item does not belong to the queue" << std::endl;
            }
            break;
        case 6:
            queue.clear();
            std::cout << "The queue has been cleared" << std::endl;
            break;
        case 7:
            std::cout << "Queue: ";
            queue.display();
            break;
        }

    } while (choice != 0);
    return 0;
}