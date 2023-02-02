
#include "Tree.h"


/*TO DO LIST:
	-get remove in order working
	-create tests which needto satisfy:
		trees with 100+ nodes
		tests for all 4 rotation types (for balancing)
			left right node
			right left node
			left left node
			right right node
	-need destructor class
	*/


int main() {
	int numOps;
	int opsCounter = 0;
	cin >> numOps >> ws;
	string command;
	string line;

	//building tree with head set to null, i.e setting tree to empty before any ops are called
	TreeNode* root = nullptr;
	Tree* tree = new Tree();
	tree->head = root;
	

	for (opsCounter; opsCounter < numOps; opsCounter++) {

		getline(cin, line);
		istringstream in(line);
		root = tree->readInput(in);
	}

	return 0;
}