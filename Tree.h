#pragma once
#include <queue>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "TreeNode.h"

class Tree {
	
public:
	TreeNode* head;
	Tree();
	Tree(TreeNode* root);
	void searchString(TreeNode* root, string nameToFind);
	TreeNode* searchInt(TreeNode* root, int idToFind);
	TreeNode* remove(TreeNode* root, int idToRemove);
	queue<TreeNode*> inOrderTraversal(TreeNode* root, queue<TreeNode*> nodes);
	queue<TreeNode*> preOrderTraversal(TreeNode* root, queue<TreeNode*> nodes);
	queue<TreeNode*> postOrderTraversal(TreeNode* root, queue<TreeNode*> nodes);
	void printInOrder(TreeNode* node);
	void printPreOrder(TreeNode* root);
	void printPostOrder(TreeNode* root);
	bool removeInOrder(TreeNode* node, int N, int currentN);
	int getBalanceFactor(TreeNode* root);
	int getHeight(TreeNode* root);
	TreeNode* leftRotation(TreeNode* node);
	TreeNode* rightRotation(TreeNode* node);
	TreeNode* insert(TreeNode* root, int ID, string name);
	bool isEmpty();
	TreeNode* readInput(istringstream& in);
	void setHead(TreeNode* root);
	TreeNode* inorderSuccessor(TreeNode* node);
	bool validateStringInput(string name);
	bool validateIdInput(string ID);

};  


	Tree::Tree() {
		head = nullptr;
	}

	Tree::Tree(TreeNode* root) {
		head = root;
		head->height = 1;
	}

	//level order traversal, adds level to queue, prints ID if names match, pops everything after the level
	void Tree::searchString(TreeNode* root, string nameToFind) {
		if (root == nullptr) {
			cout << "unsuccessful" << endl;
		}

		queue<TreeNode*> level;
		level.push(root);

		while (!level.empty()) {
			TreeNode* node = level.front();
			if (node->name == nameToFind) {
				cout << node->ID << endl;
			}

			level.pop();
			if (node->left) {
				level.push(node->left);
			}
			if (node->right) {
				level.push(node->right);
			}
		}

	}

	TreeNode* Tree::searchInt(TreeNode* root, int idToFind) {
		if (root == nullptr) {
			return root;
		}
		//if idToFind > root ID,search right subtree, if right is null, then ID is not in tree (if inserted & balanced properly)
		if (idToFind > root->ID) {
			if (root->right == nullptr) { return root; }
			root = searchInt(root->right, idToFind);
		}
		//else if idToFind < root ID, search left subtree, if left is null, then ID is not in tree (if inserted & balanced properly)
		else if (idToFind < root->ID) {
			if (root->left == nullptr) { return root; }
			root = searchInt(root->left, idToFind);
		}
		//else if id is found
		else if (root->ID == idToFind) { return root; }

		//otherwise
		else { return root; }
	}

	//gets nodes smallest value in left subtree (as this is it's parents in order successor bc node passed in is grandparent->right)
	TreeNode* Tree:: inorderSuccessor(TreeNode* node) {
		TreeNode* smallestNode = node;
		if (!node->left) {
			return node;
		}
		while (smallestNode->left) {
			smallestNode = smallestNode->left;
		}
		return smallestNode;
	}

	TreeNode* Tree::remove(TreeNode* node, int idToRemove) {

		if (node == nullptr) {
			return node;
		}

		//FINDING NODE W/ CORRECT ID

		//go left
		if (idToRemove < node->ID) {
			node->left = remove(node->left, idToRemove);
			return node;
		}
		//go right
		else if (idToRemove > node->ID) {
			node->right  = remove(node->right, idToRemove);
			return node;
		}

		//ID FOUND

		//node->ID == IDTOREMOVE
		else {
			//node has at least left child
			if (node->left != nullptr) {

				//node has left and right child
				if (node->right != nullptr) {
					TreeNode* nextOfKin = inorderSuccessor(node->right);
					node->ID = nextOfKin->ID;
					node->name = nextOfKin->name;
					node->right = remove(node->right, nextOfKin->ID);
					return node;
				}

				//node has only left child
				else {
					TreeNode* leftChild = node->left;
					*node = *leftChild;
					free(leftChild);
					return node;
				}
			}

			//node has only right child
			else if (node->right != NULL || node->right->ID != NULL) {
				TreeNode* rightChild = node->right;
				*node = *rightChild;
				free(rightChild);
				return node;
			}

			//node has no child
			else {
				TreeNode* temp = node;
				node = nullptr;
				free(temp);
				return node;
			}
		}
	}

	queue<TreeNode*> Tree:: inOrderTraversal(TreeNode* root, queue<TreeNode*> nodes) {
		if (root != nullptr) {
			nodes = inOrderTraversal(root->left, nodes);
			nodes.push(root);
			nodes = inOrderTraversal(root->right, nodes);
		}
		return nodes;
	}

	void Tree::printInOrder(TreeNode* node) {
		queue<TreeNode*> nodes;
		nodes = inOrderTraversal(node, nodes);
		while (!nodes.empty()) {
			if (1 == nodes.size()) {
				cout << nodes.front()->name;
			}
			else {
				cout << nodes.front()->name << ", ";
			}
			nodes.pop();
		}
	}

	queue<TreeNode*> Tree::preOrderTraversal(TreeNode* root, queue<TreeNode*> nodes) {
		if (root != nullptr) {
			nodes.push(root);
			nodes = preOrderTraversal(root->left, nodes);
			nodes = preOrderTraversal(root->right, nodes);
		}
		return nodes;
	}

	void Tree::printPreOrder(TreeNode* node) {
		queue<TreeNode*> nodes;
		nodes = preOrderTraversal(node, nodes);
		while (!nodes.empty()) {
			if (1 == nodes.size()) {
				cout << nodes.front()->name;
			}
			else {
				cout << nodes.front()->name << ", ";
			}
			nodes.pop();
		}
	}

	queue<TreeNode*> Tree::postOrderTraversal(TreeNode* root, queue<TreeNode*> nodes) {
		if (root != nullptr) {
			nodes = postOrderTraversal(root->left, nodes);
			nodes = postOrderTraversal(root->right, nodes);
			nodes.push(root);
		}
		return nodes;
	}

	void Tree::printPostOrder(TreeNode* node) {
		queue<TreeNode*> nodes;
		nodes = postOrderTraversal(node, nodes);
		while (!nodes.empty()) {
			if (nodes.size() == 1) {
				cout << nodes.front()->name;
			}
			else {
				cout << nodes.front()->name << ", ";
			}
			nodes.pop();
		}
	}
	

	//not done
	bool Tree::removeInOrder(TreeNode* node, int N, int currentN) {
		if (node) {
			removeInOrder(node->left, N, currentN + 1);
			if (N == currentN) {
				remove(node, node->ID);
				return true;
			}
			removeInOrder(node->right, N, currentN - 1);
		}
	}

	int Tree::getBalanceFactor(TreeNode* root) {
		int balanceFactor = 0;

		//root is in a 1 node tree
		if (!root->left && !root->right) {
			return balanceFactor;
		}

		//root has children
		else {
			//get height of left side
			int leftHeight = getHeight(root->left);
			//get height of right side
			int rightHeight = getHeight(root->right);

			return (balanceFactor = leftHeight - rightHeight);
		}
	}

	int Tree::getHeight(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}

	//right right case, returns newParent (node->right)
	TreeNode* Tree::leftRotation(TreeNode* node) {
		TreeNode* newParent = node->right;
		TreeNode* grandChild = node->right->left;
		newParent->left = node;
		node->right = grandChild;
		//height update
		node->height = 1 + max(getHeight(node->right), getHeight(node->left));
		newParent->height = 1 +max(getHeight(newParent->right), getHeight(newParent->left));
		if (node == head) {
			head = newParent;
		}
		return newParent;
	}

	//left left case, returns newParent (node->left)
	TreeNode* Tree::rightRotation(TreeNode* node) {
		TreeNode* newParent = node->left;
		TreeNode* grandChild = node->left->right;
		newParent->right = node;
		node->left = grandChild;
		//height update
		node->height = 1 + max(getHeight(node->right), getHeight(node->left));
		newParent->height = 1 + max(getHeight(newParent->right), getHeight(newParent->left));
		if (node == head) {
			head = newParent;
		}
		return newParent;
	}

	TreeNode* Tree::insert(TreeNode* node, int ID, string name) {
		
		if (node == nullptr) {
			TreeNode* newNode = new TreeNode(ID, name);
			return newNode;
		}
		//if ID already in tree
		else if (searchInt(node, ID)->ID == ID) {
			return nullptr;
		}
		
		//if ID to be inserted is > current node's ID, go right
		else if (ID > node->ID) {
			node->right = insert(node->right, ID, name);
		}
		//else go left
		else {
			node->left = insert(node->left, ID, name);
		}

		//update height here
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));

		//BALANCE

		//right heavy
		if (getBalanceFactor(node) < -1) {
			//right right => left rotation
			if (getBalanceFactor(node->right) < 0) {
				node = leftRotation(node);
			}
			//right left => right left rotation
			else {
				node->right = rightRotation(node->right);
				node = leftRotation(node);
			}
		}

		//left heavy
		else if (getBalanceFactor(node) > 1) {
			//left left => right rotation
			if (getBalanceFactor(node->left) > 0) {
				node = rightRotation(node);
			}
			//left right => left right rotation 
			else {
				node->left = leftRotation(node->left);
				node = rightRotation(node);
			}
		}
		
		return node;

	}

	bool Tree::isEmpty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	void Tree::setHead(TreeNode* root) {
		this->head = root;
	}

	//validates name, returns TRUE if BAD input
	bool Tree::validateStringInput(string name) {
		for (char b : name) {
			if (!isalpha(b) && b != ' ') {
				return true;
			}
		}
		return false;
	}

	//validates ID, returns TRUE if BAD input
	bool Tree::validateIdInput(string stringID) {
		if (stringID.size() != 8) {
			return true;
		}
		for (char c : stringID) {
			if (!isdigit(c)) {
				return true;
			}
		}
		return false;
	}

	TreeNode* Tree::readInput(istringstream& in) {

		string command;
		in >> command;

		if (command == "insert") {
			string name;
			string stringID;
			getline(in, name, '"');
			getline(in, name, '"');
			in >> ws;
			getline(in, stringID);

			//if invalid ID or name is entered

			if (validateIdInput(stringID) || validateStringInput(name) || ((head != nullptr) && (searchInt(head, stoi(stringID))->ID == stoi(stringID)))) {
				cout << "unsuccessful" << endl;
			}

			else {
				int ID = stoi(stringID);
				if (head == nullptr) {
					head = insert(head, ID, name);
				}
				else {
					insert(this->head, ID, name);
				}
				cout << "successful" << endl;
			}
		}

		else if (command == "remove") {
			string idToFindS;
			in >> ws;
			getline(in, idToFindS);
			bool notDigit = false;

			//checks to see if id string contains non digits
			for (char c : idToFindS) {
				if (!isdigit(c)) {
					notDigit = true;
					break;
				}
			}

			int idToFind;
			idToFind = stoi(idToFindS);

			//if invalid ID is entered
			if (idToFindS.length() > 8 || idToFindS.length() < 8 || notDigit || (searchInt(head, idToFind)->ID != idToFind)) {
				cout << "unsuccessful" << endl;
				
			}
			else {
				head = remove(head, idToFind);
				cout << "successful" << endl;
			}
		}

		else if (command == "search") {
			in >> ws;
			string forWhat;
			getline(in, forWhat);
			bool isName = false;
			bool isID = false;
			bool invalidInput = false;

			//validating input, deciding if its name or ID to search for
			for (char c : forWhat) {
				if (isalpha(c) || c == '"') {
					isName = true;
					break;
				}
				else if (isdigit(c)) {
					isID = true;
					break;
				}
				else {
					invalidInput = true;
					break;
				}
			}
			if (invalidInput || head == nullptr) {
				cout << "unsuccessful" << endl;
			}

			else if (isName) {
				forWhat.erase(std::remove(forWhat.begin(), forWhat.end(), '"'), forWhat.end());
				searchString(head, forWhat);
			}
			else if (isID && forWhat.size() == 8) {
				TreeNode* search = searchInt(head, stoi(forWhat));
				if(search->ID == stoi(forWhat))
					cout << search->name << endl;
				else {
					cout << "unsuccessful" << endl;
				}
			}
			else {
				cout << "unsuccessful" << endl;
			}

		}

		else if (command == "printInorder") {
			printInOrder(head);
			cout << endl;
		}

		else if (command == "printPreorder") {
			printPreOrder(head);
			cout << endl;
		}

		else if (command == "printPostorder") {
			printPostOrder(head);
			cout << endl;
		}

		else if (command == "printLevelCount") {
			cout << head->height << endl;
		}

		else if (command == "removeInorder") {
			string Nstring;
			in >> ws;
			getline(in, Nstring);
			bool notDigit = false;

			//checks to see if id string contains non digits
			for (char c : Nstring) {
				if (!isdigit(c)) {
					notDigit = true;
					break;
				}
			}

			//if invalid ID is entered
			if (notDigit) {
				cout << "unsuccessful" << endl;
			}

			else {
				int N = stoi(Nstring);
				if( removeInOrder(head, N, 0) ) { cout << "successful" << endl; }
				else { cout << "unsuccessful" << endl; }
			}
		}

		else {
			cout << "unsuccessful" << endl;
		}

		return head;
	}
