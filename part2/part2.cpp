#include <iostream>
#include <string>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    CircularLinkedList() : head(nullptr) {}

    void insert(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    void remove(Node<T>* prev, Node<T>* current) {
        if (current == head) {
            Node<T>* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next;
            last->next = head;
            delete current;
        }
        else {
            prev->next = current->next;
            delete current;
        }
    }

    void drawWinners(int t, int n) {
        if (!head || n <= 0) {
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        int count = 0;
        int printed = 0;

        while (printed < n) {
            for (int i = 0; i < t - 1; ++i) {
                prev = current;
                current = current->next;
            }

            Node<T>* winner = current;
            current = current->next;

            if (prev) {
                prev->next = current;
            }
            else {
                head = current;
            }

            ++printed;

            std::cout << winner->data << std::endl;
        }
    }
};

int main() {
    CircularLinkedList<std::string> participants;
    participants.insert("Alice");
    participants.insert("Bob");
    participants.insert("Charlie");
    participants.insert("David");
    participants.insert("Eve");
    participants.insert("Frank");
    participants.insert("Grace");
    participants.insert("Helen");

    CircularLinkedList<std::string> bilet;
    bilet.insert("1");
    bilet.insert("2");
    bilet.insert("3");
    bilet.insert("4");
    bilet.insert("5");
    bilet.insert("6");
    bilet.insert("7");
    bilet.insert("8");



    int n = 5;  
    
    std::cout << "\nUsers\n";
    participants.drawWinners(3, n);
    std::cout << "\nBilets\n";
    bilet.drawWinners(5, n);

    //
    return 0;
}
