#include <iostream>
#include <string>


class HashTableEntry {
public:
    std::string key;
    std::string value;
    HashTableEntry* next;

    HashTableEntry(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
};


class HashTable {
private:
    int size;
    HashTableEntry** table;

public:
    HashTable(int s) : size(s), table(new HashTableEntry* [size]()) {}

    size_t hashFunction(const std::string& key) {
        std::hash<std::string> hashFunc;
        return hashFunc(key) % size;
    }

    void addEntry(const std::string& key, const std::string& value) {
        size_t index = hashFunction(key);
        HashTableEntry* newEntry = new HashTableEntry(key, value);
        newEntry->next = table[index];
        table[index] = newEntry;
    }

    void removeEntry(const std::string& key) {
        size_t index = hashFunction(key);
        HashTableEntry* current = table[index];
        HashTableEntry* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return; 
        }

        if (prev == nullptr) {
            table[index] = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
    }

    std::string getValue(const std::string& key) {
        size_t index = hashFunction(key);
        HashTableEntry* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return "Not found";
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            HashTableEntry* current = table[i];
            while (current != nullptr) {
                HashTableEntry* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }
};

int main() {
    // Створення хеш-таблиці розміром 10
    HashTable hashTable(10);

    int choice;
    std::string key, value;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Entry\n";
        std::cout << "2. Remove Entry\n";
        std::cout << "3. Get Value\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin >> value;
            hashTable.addEntry(key, value);
            break;

        case 2:
            std::cout << "Enter key to remove: ";
            std::cin >> key;
            hashTable.removeEntry(key);
            break;

        case 3:
            std::cout << "Enter key to get value: ";
            std::cin >> key;
            std::cout << "Value: " << hashTable.getValue(key) << std::endl;
            break;

        case 4:
            std::cout << "Exiting program.\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}