#include <iostream>
#include <string>

using namespace std;
class HashTableEntry {
public:
	int key;
	std::string value;
	HashTableEntry* next;

	HashTableEntry(int& k, std::string& v) : key(k), value(v), next(nullptr) {}
};


class HashTable {
private:
	int size;
	HashTableEntry** table;

public:
	HashTable(int s) : size(s), table(new HashTableEntry* [size]()) {}

	size_t hashFunction(int& key) {
		std::hash<int> hashFunc;
		return hashFunc(key) % size;
	}

	void addEntry(int& key, std::string& value) {
		size_t index = hashFunction(key);
		if (table[index] == nullptr) {
			table[index] = new HashTableEntry(key, value);
		}
		else {
			HashTableEntry* current = table[index];
			while (current->key != key && current->value != value && current->next != nullptr) {
				current = current->next;
			}
			current->next = new HashTableEntry(key, value);
		}

		
	}

	void removeEntry(int& key) {
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

	std::string getValue(int& key) {
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


	void showElement() {
		for (int i = 0; i < size; i++) {
			if (table[i]!=nullptr) {
				cout << "[" << table[i]->key << "]" << table[i]->value << endl;
			}
			else {
				cout << "Empty " << endl;
			}

		}
		cout << endl;
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

	HashTable hashTable(3);

	int choice;
	std::string value;
	int key;

	do {
		std::cout << "\nMenu:\n";
		std::cout << "1. Add\n";
		std::cout << "2. Remove \n";
		std::cout << "3. Get \n";
		std::cout << "4. Show Elements\n";
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
			std::cout << "\nAll Elements:\n";
			hashTable.showElement();
			break;
		case 5:
			std::cout << "Exiting program.\n";
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 5);

	return 0;
}

//collision додавання в ланцюжок