#include <iostream>
#include <stack>

using namespace std;
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class CustomStack {
private:
    Node<T>* topNode;

public:
    CustomStack() : topNode(nullptr) {}

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push( T& item) {
        Node<T>* newNode = new Node<T>(item);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() const {
        if (!isEmpty()) {
            return topNode->data;
        }
        throw std::runtime_error("Stack is empty");
    }

    void swapFirstAndLast()
    {
        if (!topNode || !topNode->next)
        {
            return;
        }


        Node<T>* prev = nullptr;
        Node<T>* current = topNode;

        while (current->next)
        {
            prev = current;
            current = current->next;
        }

        // Поміняти дані першого та останнього елементів
        int tmp = topNode->data;
        topNode->data = current->data;
        current->data = tmp;
    }

        //// Swap the first and last elements by adjusting the pointers.
        //if (first->next == last) {
        //    // Special case when there are only two elements.
        //    last->next = first;
        //    first->prev = last;
        //    first->next = nullptr;
        //    last->prev = nullptr;
        //    topNode = last;
        //}
        //else {
        //    first->next->prev = last;
        //    last->prev->next = first;
        //    std::swap(first->next, last->next);
        //    std::swap(first->prev, last->prev);
        //    topNode = last;
        //}
    

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = topNode;
        Node<T>* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        topNode = prev;
    }

    bool contains(const T& item) const {
        Node<T>* current = topNode;
        while (current != nullptr) {
            if (current->data == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    void show() const {
        Node<T>* current = topNode;
        std::cout << "Current stack: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // основні операції(додавання та видалення елементу стека); 
    // - змінити місцями перший та останній елемент стеку; 
    // - розвернути стек(зробити «дно» стеку вершиною, а вершину –«дном»); 
    // - операція «чи належить заданий елемент» стеку; 
    // - видалити всі елементи стеку.
    CustomStack<int> myStack;
    int check = 0;
    do {
        cout << "\t\tMenu";
        cout << "\n0 - Exit";
        cout << "\n1 - Add";
        cout << "\n2 - Remove";
        cout << "\n3 - Change first and last";
        cout << "\n4 - Reverse";
        cout << "\n5 - Is exist";
        cout << "\n6 - Clear all";
        cout << "\n7 - Show";
        cout << "\nYour input: ";
        cin >> check;

        if (check == 0) {
            break;
        }

        if (check == 1) {
            int val;
            cout << "\nWrite value: ";
            cin >> val;
            myStack.push(val);
            continue;
        }
        if (check == 2) {
            myStack.pop();
            continue;
        }
        if (check == 3) {
            myStack.swapFirstAndLast();
            continue;
        }
        if (check == 4) {
            myStack.reverse();
            continue;
        }

        if (check == 5) {
            int val;
            cout << "\nWrite value: ";
            cin >> val;
            if (myStack.contains(val)) {
                cout << "\ncontain";
            }
            else {
                cout << "\nnot contain";
            }
            
            continue;
        }
        if (check == 6) {
            myStack.clear();
            continue;
        }

        if (check == 7) {
            myStack.show();
            continue;
        }

    } while (true);
    
    
    
    return 0;
}