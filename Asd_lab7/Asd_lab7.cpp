#include <iostream>
#include <string>

class HashTable {
private:
    static const int tableSize = 10;
    int keys[tableSize];
    std::string values[tableSize];
    bool occupied[tableSize];

public:
    HashTable() {
        for (int i = 0; i < tableSize; ++i) {
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    size_t hashFunction(int& key) {
        std::hash<int> hashFunc;
        return hashFunc(key) % tableSize;
    }

    bool keyExists(int& key) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            if (keys[index] == key) {
                return true;
            }
            index = (index + 1) % tableSize;
        }

        return false;
    }

    void addEntry(int& key,  std::string& value) {
        size_t index = hashFunction(key);
        if (keyExists(key)) {
            std::cout << "Key already exists. Cannot add duplicate key.\n";
            while (occupied[index]) {
                index = (index + 1) % tableSize; // Ищем следующую свободную ячейку
            }
        }


        while (occupied[index]) {
            index = (index + 1) % tableSize;
        }

        keys[index] = index;
        values[index] = value;
        occupied[index] = true;

        std::cout << "Element added successfully.\n";
    }
    void resize() {
        int newSize = size * 2;

        Pair** newTable = new Pair * [newSize];

        for (int i = 0; i < newSize; i++) {
            newTable[i] = new Pair();
        }

        for (int i = 0; i < size; i++) {
            if (table[i]) {
                int hash = divisionHash(table[i]->key, newSize);
                while (!newTable[hash]->isDeleted) {
                    hash = divisionHash(hash + 1, newSize);
                }
                newTable[hash] = table[i];
            }
        }

        size = newSize;
        freeSpace = size / 2;
        delete[] table;
        table = newTable;
    }


    void removeEntry( int& key) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            if (keys[index] == key) {
                keys[index] = 0;
                values[index] = "";
                occupied[index] = false;
                std::cout << "Element removed successfully." << std::endl;
                return;
            }
            index = (index + 1) % tableSize; 
        
        }

        std::cout << "Element not found." << std::endl;
    }

    std::string getValue( int& key) {
        size_t index = hashFunction(key);

        while (occupied[index]) {
            if (keys[index] == key) {
                return values[index];
            }
            index = (index + 1) % tableSize;
         
        }

        return "Not found";
    }
    void displayAllEntries() {
        std::cout << "\nAll Entries:\n";
        for (int i = 0; i < tableSize; ++i) {
            if (occupied[i]) {
                std::cout << "Key: " << keys[i] << ", Value: " << values[i] << std::endl;
            }
        }
        std::cout << "End of Entries\n";
    }
};


int main() {
    HashTable hashTable;

    int choice;
    std::string value;
    int key;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Entry\n";
        std::cout << "2. Remove Entry\n";
        std::cout << "3. Get Value\n";
        std::cout << "4. Show\n";
        std::cout << "5. Exit\n";
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
            hashTable.displayAllEntries();
            break;

        case 5:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice !=5);

    return 0;
}