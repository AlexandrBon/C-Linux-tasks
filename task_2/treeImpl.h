#include <algorithm>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct node {
	int data;
	node* left;
	node* right;
};

void insert(node** tree, int val)
{
	node* temp = NULL;
	if (!(*tree)) {
		temp = (node*)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;
		return;
	}
	if (val < (*tree)->data) {
		insert(&(*tree)->left, val);
	}
	else if (val > (*tree)->data) {
		insert(&(*tree)->right, val);
	}
}

node* descendToParent(node* tree, int val) {
	if (!tree) {
		return NULL;
	}
	if ((tree->left && tree->left->data == val)
		|| (tree->right && tree->right->data == val)) {
		return tree;
	}
	else if (tree->data < val) {
		return descendToParent(tree->right, val);
	}
	else if (tree->data > val) {
		return descendToParent(tree->left, val);
	}
	return tree;
}

node* getNodeFromParent(node* parentOfDelNode, int val) {
	if (!parentOfDelNode)
		return NULL;
	node* leftChild = parentOfDelNode->left;
	node* rightChild = parentOfDelNode->right;
	if (leftChild && leftChild->data == val) {
		return leftChild;
	}
	else if (rightChild && rightChild->data == val) {
		return rightChild;
	}
	else if (parentOfDelNode->data == val) {
		return parentOfDelNode;
	}
	return NULL;
}

node* descendToMin(node* tree) {
	node* minNode = tree;

	while (tree) {
		minNode = tree;
		tree = tree->left;
	}
	return minNode;
}

void remove(node** tree, int val) {
	if (!(*tree)) 
		return;
	
	node* delNodeParent = descendToParent(*tree, val);
	node* delNode = getNodeFromParent(delNodeParent, val);
	if (!delNode) 
		return;

	// root without children
	if (delNodeParent->data == val && delNode->left == NULL && delNode->right == NULL) {
		free(*tree);
		*tree = NULL;
		return;
	} // root with left child
	else if (delNodeParent->data == val && delNode->left != NULL && delNode->right == NULL) {
		node* temp = *tree;
		*tree = (*tree)->left;
		free(temp);
		return;
	} // root with right child
	else if (delNodeParent->data == val && delNode->left == NULL && delNode->right != NULL) {
		node* temp = *tree;
		*tree = (*tree)->right;
		free(temp);
		return;
	} // delNode without children
	else if (delNode->left == NULL && delNode->right == NULL) {
		if (delNodeParent->left && delNodeParent->left->data == delNode->data)
			delNodeParent->left = NULL;
		else
			delNodeParent->right = NULL;
		free(delNode);
	} // delNode with left child
	else if (delNode->left != NULL && delNode->right == NULL) {
		if (delNodeParent->data < delNode->data)
			delNodeParent->right = delNode->left;
		else
			delNodeParent->left = delNode->left;

		free(delNode);
	} // delNode with right child
	else if (delNode->left == NULL && delNode->right != NULL) {
		if (delNodeParent->data < delNode->data)
			delNodeParent->right = delNode->right;
		else
			delNodeParent->left = delNode->right;

		free(delNode);
	} // delNode with 2 children
	else {
		node* newNode = descendToMin(delNode->right);
		std::swap(newNode->data, delNode->data);
		remove(&(delNode->right), val);
	}
}
