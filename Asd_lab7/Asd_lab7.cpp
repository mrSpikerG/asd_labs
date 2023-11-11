#include <iostream>
#include <string>

class HashTable {
private:
    static const int tableSize = 10;
    std::string keys[tableSize];
    std::string values[tableSize];
    bool occupied[tableSize];

public:
    HashTable() {
        for (int i = 0; i < tableSize; ++i) {
            keys[i] = "";
            values[i] = "";
            occupied[i] = false;
        }
    }

    size_t hashFunction(const std::string& key) {
        std::hash<std::string> hashFunc;
        return hashFunc(key) % tableSize;
    }

    void addEntry(const std::string& key, const std::string& value) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            index = (index + 1) % tableSize; 
 
        }

        keys[index] = key;
        values[index] = value;
        occupied[index] = true;

        std::cout << "Element added successfully." << std::endl;
    }

    void removeEntry(const std::string& key) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            if (keys[index] == key) {
                keys[index] = "";
                values[index] = "";
                occupied[index] = false;
                std::cout << "Element removed successfully." << std::endl;
                return;
            }
            index = (index + 1) % tableSize; 
        
        }

        std::cout << "Element not found." << std::endl;
    }

    std::string getValue(const std::string& key) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            if (keys[index] == key) {
                return values[index];
            }
            index = (index + 1) % tableSize;
         
        }

        return "Not found";
    }
};


int main() {
    HashTable hashTable;

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