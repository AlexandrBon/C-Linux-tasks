#include <vector>
#include <cassert>
#include "treeImpl.h"

using namespace std;

void inorder(vector<int> &vectorToFill, node* tree) {
	if (tree) {
		inorder(vectorToFill, tree->left);
		vectorToFill.push_back(tree->data);
		inorder(vectorToFill, tree->right);
	}
}

node* root;

int main() {
	vector<int> vec;

	insert(&root, 5);
	insert(&root, 7);
	insert(&root, 8);
	insert(&root, 6);
	insert(&root, 2);
	insert(&root, 3);
	insert(&root, 1);
	insert(&root, 4);

	remove(&root, 3);
	remove(&root, 1);
	inorder(vec, root);
	assert((vec == vector<int>{ 2, 4, 5, 6, 7, 8 })); vec.clear();

	remove(&root, 8);
	remove(&root, 4);
	inorder(vec, root);
	assert((vec == vector<int>{ 2, 5, 6, 7 })); vec.clear();

	remove(&root, 7);
	remove(&root, 6);
	inorder(vec, root);
	assert((vec == vector<int>{ 2, 5 })); vec.clear();

	remove(&root, 5);
	remove(&root, 2);
	inorder(vec, root);
	assert(vec.empty()); vec.clear();
	return 0;
}