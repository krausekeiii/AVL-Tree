#pragma once
using namespace std;

class TreeNode {

public:

	int ID;
	string name;
	TreeNode* left, * right;
	int height;

	TreeNode() {
		//this->ID = NULL;
		
		left = nullptr, right = nullptr;
		height = 1;
	}

	TreeNode(int ID, string name) {
		//TreeNode* node = new TreeNode();
		this->ID = ID;
		this->name = name;
		left = nullptr;
		right = nullptr;
		height = 1;
	}

	/*~TreeNode() {
		delete this;
	}*/
};