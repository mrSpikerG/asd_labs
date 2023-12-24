#include <iostream>
using namespace std;


enum Color {
	RED,
	BLACK
};

class Node {
public:
	int value;
	Node* left;
	Node* right;
	Node* parent;
	Color color = BLACK;

	Node(int _value) : left(nullptr), right(nullptr), parent(nullptr) {
		value = _value;
	}
};


class RedBlackTree {
private:
	Node* EMPTYNODE = new Node(0);
	Node* root = EMPTYNODE;

	void rotateLeft(RedBlackTree* tree, Node* x) {
		Node* newRoot = x->right;
		x->right = newRoot->left;
		if (newRoot->left != EMPTYNODE) {
			newRoot->left->parent = x;
		}
		newRoot->parent = x->parent;
		if (x->parent == EMPTYNODE) {
			tree->root = newRoot;
		}
		else if (x == x->parent->left) {
			x->parent->left = newRoot;
		}
		else {
			x->parent->right = newRoot;
		}
		newRoot->left = x;
		x->parent = newRoot;
	}

	void rotateRight(RedBlackTree* tree, Node* y) {
		Node* newRoot = y->left;
		y->left = newRoot->right;
		if (newRoot->right != EMPTYNODE) {
			newRoot->right->parent = y;
		}
		newRoot->parent = y->parent;
		if (y->parent == EMPTYNODE) {
			tree->root = newRoot;
		}
		else if (y == y->parent->left) {
			y->parent->left = newRoot;
		}
		else {
			y->parent->right = newRoot;
		}
		newRoot->right = y;
		y->parent = newRoot;
	}

	void balanceTree(RedBlackTree* tree, Node* newNode) {
		Node* uncle;

		while (newNode->parent->color == RED) {
			if (newNode->parent == newNode->parent->parent->left) {
				uncle = newNode->parent->parent->right;

				if (uncle->color == RED) {
					newNode->parent->color = BLACK;
					uncle->color = BLACK;
					newNode->parent->parent->color = RED;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->right) {
						newNode = newNode->parent;
						rotateLeft(tree, newNode);
					}
					newNode->parent->color = BLACK;
					newNode->parent->parent->color = RED;
					rotateRight(tree, newNode->parent->parent);
				}
			}
			else {
				uncle = newNode->parent->parent->left;

				if (uncle->color == RED) {
					newNode->parent->color = BLACK;
					uncle->color = BLACK;
					newNode->parent->parent->color = RED;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->left) {
						newNode = newNode->parent;
						rotateRight(tree, newNode);
					}
					newNode->parent->color = BLACK;
					newNode->parent->parent->color = RED;
					rotateLeft(tree, newNode->parent->parent);
				}
			}
		}

		tree->root->color = BLACK;
	}

	Node* find(Node* node, int data) {
		if (node == nullptr || node->value == data) {
			return node;
		}

		if (data < node->value) {
			return find(node->left, data);
		}

		return find(node->right, data);
	}

	Node* min(Node* node) {
		if (node == EMPTYNODE) {
			return EMPTYNODE;
		}

		if (node->left == EMPTYNODE) {
			return node;
		}

		return min(node->left);
	}

	int getChildrenCount(Node* node) {
		int count = 0;

		if (node->left != EMPTYNODE) {
			count += 1;
		}

		if (node->right != EMPTYNODE) {
			count += 1;
		}

		return count;
	}

	Node* getChild(Node* node) {
		return (node->left != EMPTYNODE) ? node->left : node->right;
	}

	void transplantNode(Node* toNode, Node* fromNode) {
		if (fromNode == EMPTYNODE) {
			if (toNode == root) {
				root = EMPTYNODE;
			}
			else if (toNode == toNode->parent->left) {
				toNode->parent->left = EMPTYNODE;
			}
			else {
				toNode->parent->right = EMPTYNODE;
			}
		}
		else {
			if (toNode == root) {
				root = fromNode;
			}
			else if (toNode == toNode->parent->left) {
				toNode->parent->left = fromNode;
			}
			else {
				toNode->parent->right = fromNode;
			}

			fromNode->parent = toNode->parent;
		}
	}

	void removeBalance(RedBlackTree* tree, Node* node) {
		while (node != tree->root && node->color == BLACK) {
			Node* sibling;

			if (node == node->parent->left) {
				sibling = node->parent->right;

				if (sibling->color == RED) {
					sibling->color = BLACK;
					node->parent->color = RED;
					rotateLeft(tree, node->parent);
					sibling = node->parent->right;
				}

				if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
					sibling->color = RED;
					node = node->parent;
				}
				else {
					if (sibling->right->color == BLACK) {
						sibling->left->color = RED;
						node->parent->color = RED;
						rotateRight(tree, sibling);
						sibling = node->parent->right;
					}
					else {
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->right->color = BLACK;
						rotateLeft(tree, node->parent);
						node = tree->root;
					}
				}
			}
			else {
				sibling = node->parent->left;

				if (sibling->color == RED) {
					sibling->color = BLACK;
					node->parent->color = RED;
					rotateRight(tree, node->parent);
					sibling = node->parent->left;
				}

				if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
					rotateRight(tree, node->parent);
					sibling = node->parent->left;
				}
				else {
					if (sibling->left->color == BLACK) {
						sibling->right->color = BLACK;
						sibling->color = RED;
						rotateLeft(tree, sibling);
						sibling = node->parent->left;
					}
					else {
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->left->color = BLACK;
						rotateRight(tree, node->parent);
						node = tree->root;
					}
				}
			}
		}
		node->color = BLACK;
	}

	void printTree(Node* root, int depth = 0) {
		if (root != EMPTYNODE) {
			printTree(root->right, depth + 1);
			for (int i = 0; i < depth; i++) {
				cout << "    ";
			}
			cout << root->value << " " << (root->color == RED ? "R" : "B") << endl;
			printTree(root->left, depth + 1);
		}
		else {
			for (int i = 0; i < depth; i++) {
				cout << "    ";
			}
			cout << "   " << endl;
		}
	}

public:
	void show() {
		if (root != EMPTYNODE) {
			printTree(root);
			cout << "\n" << endl;
		}
	}

	void append(int data) {
		Node* currNode = root;
		Node* parent = EMPTYNODE;

		while (currNode != EMPTYNODE) {
			parent = currNode;
			if (data < currNode->value) {
				currNode = currNode->left;
			}
			else {
				currNode = currNode->right;
			}
		}
		Node* newNode = new Node(data);
		newNode->parent = parent;
		newNode->left = EMPTYNODE;
		newNode->right = EMPTYNODE;
		newNode->color = RED;
		if (parent == EMPTYNODE) {
			root = newNode;
		}
		else if (data < parent->value) {
			parent->left = newNode;
		}
		else {
			parent->right = newNode;
		}
		balanceTree(this, newNode);
	}

	void remove(int data) {
		Node* toDelete = find(root, data);

		if (toDelete == nullptr) {
			return;
		}

		bool color = toDelete->color;

		Node* child;
		if (getChildrenCount(toDelete) < 2) {
			child = getChild(toDelete);
			if (child == EMPTYNODE) {
				color = RED;
			}
			transplantNode(toDelete, child);
		}

		else {
			Node* minNode = min(toDelete->right);
			toDelete->value = minNode->value;
			child = getChild(minNode);
			if (child != EMPTYNODE) {
				color = minNode->color;
			}
			else if (color == BLACK && minNode->color == RED) {
				color = minNode->color;
			}
			transplantNode(minNode, child);
		}

		if (color == BLACK) {
			removeBalance(this, child);
		}
	}
};


int main()
{
	RedBlackTree tree;

	tree.append(9);
	tree.append(23);
	tree.append(22);
	tree.append(15);
	tree.append(6);
	tree.append(27);
	tree.append(7);
	tree.append(4);

	tree.show();

	int option;
	int value;

	while (true) {
		cout << "\tMenu";
		cout << "\n1 - Add";
		cout << "\n2 - Remove";
		cout << "\n3 - Show";
		cout << "\nInput: ";

		cin >> option;

		if (option == 1) {
			cout << "\nInput: ";
			cin >> value;
			tree.append(value);
		}
		if (option == 2) {
			cout << "\nInput: ";
			cin >> value;
			tree.remove(value);
		}
		if (option == 3) {
			tree.show();
		}
	}

}