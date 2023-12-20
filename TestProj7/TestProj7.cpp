// asdlab7.cpp

#include <iostream>
using namespace std;

struct HashElement {
	int key;
	string value;
	bool occupied;

	HashElement() {
		key = -1;
		value = "Not set";
		occupied = true;
	}

	HashElement(int _key, string _value) {
		key = _key;
		value = _value;
		occupied = false;
	}
};

class HashTable {
private:
	HashElement** table;
	int size;
	int freeSpace;



	int hashFunc(int key) {
		return key % size;
	}

public:
	HashTable(int m) {
		size = m;
		freeSpace = m;
		table = new HashElement * [size];

		for (int i = 0; i < size; i++) {
			table[i] = new HashElement();
		}
	}

	~HashTable() {
		for (int i = 0; i < size; i++) {
			if (table[i]) {
				delete table[i];
			}
		}
		delete[] table;
	}

	void resize() {
		int newSize = size * 2;

		HashElement** newTable = new HashElement * [newSize];

		for (int i = 0; i < newSize; i++) {
			newTable[i] = new HashElement();
		}

		for (int i = 0; i < size; i++) {
			if (table[i]) {
				int hash = table[i]->key % newSize;
				while (!newTable[hash]->occupied) {
					hash = hash + 1% newSize;
				}
				newTable[hash] = table[i];
			}
		}

		size = newSize;
		freeSpace = size / 2;
		delete[] table;
		table = newTable;
	}

	void addElement(int key, string value) {
		if (freeSpace == 0) {
			resize();
		}

		int hash = hashFunc(key);
		while (!table[hash]->occupied) {
			hash = hashFunc(hash + 1);
		}

		delete table[hash];
		table[hash] = new HashElement(key, value);
		freeSpace--;
	}

	string findobj(int key) {
		int hash = hashFunc(key);
		int originalHash = hash;

		do {
			if (!table[hash]->occupied && table[hash]->key == key) {
				return table[hash]->value;
			}
			hash = hashFunc(hash + 1);
		} while (hash != originalHash);
		return "Not found";
	}

	void removeElement(int key) {
		int hash = hashFunc(key);
		int originalHash = hash;

		do {
			if (table[hash]->key == key) {
				table[hash]->occupied = true;
				freeSpace++;
				break;
			}
			hash = hashFunc(hash + 1);
		} while (hash != originalHash);
	}

	void showElement() {
		for (int i = 0; i < size; i++) {
			if (!table[i]->occupied) {
				cout << "[" << table[i]->key << "]" << table[i]->value << endl;
			}
			else {
				cout << "Empty " << endl;
			}

		}
		cout << endl;
	}

	
};

int main()
{
	HashTable table(5);
	int option;
	int key;
	string value;

	do {
		cout << "\tMenu" << endl;
		cout << "1. Add" << endl;
		cout << "2. Remove" << endl;
		cout << "3. GetElem" << endl;
		cout << "4. Show" << endl;
		cout << "5. Exit" << endl;
		cout << "Input your choise: ";
		cin >> option;

		switch (option) {
		case 1:
			cout << "Enter key ";
			cin >> key;
			cout << "Enter value ";
			cin >> value;
			table.addElement(key, value);
			break;
		case 2:
			cout << "Enter key ";
			cin >> key;
			table.removeElement(key);
			break;
		case 3:
			cout << "Enter key ";
			cin >> key;
			cout << table.findobj(key) << endl;
			break;
		case 4:
			table.showElement();
			break;
		}

	} while (option != 5);

}
