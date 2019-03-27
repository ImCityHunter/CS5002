/*
 * binary_tree.c
 *
 *  @since 2017-02-17
 *  @author Philip Gust
 */
#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"
//#include "binary_tree_node_queue.h"

/**
 * Adds a BinaryTreeNode as a child of the parent node.
 *
 * @param child the child node o add
 * @param parent the parent of the child
 * @param whichChild one of {leftLink, rightLink}
 * @return false if node has a child in the position, true otherwise
 */
bool addBinaryTreeNodeAfter(
		BinaryTreeNode* child,
		BinaryTreeNode* parent,
		BinaryTreeNodeLink whichChild) {
	if (parent->linkTo[whichChild] != NULL) {
		return false;
	}
	parent->linkTo[whichChild] = child;
	child->linkTo[parentLink] = parent;
	return true;
}

/**
 * Free the node storage for the binary tree specified by root.
 * Data must be freed by caller.
 *
 * @param root the root of a binary tree
 */
void deleteAllBinaryTreeNodes(BinaryTreeNode* root) {
	if (root != NULL) {
		deleteAllBinaryTreeNodes(root->linkTo[leftLink]);
		deleteAllBinaryTreeNodes(root->linkTo[rightLink]);
		deleteBinaryTreeNode(root);
	}
}

/**
 * Return the BinaryTreeNodeLink for a child of a parent node.
 * The childNode must be a child of the parent node.
 *
 * @param parentNode the parentNode
 * @param childNode the child node
 * @return leftLink if the child is a left child, rightLink if
 *  parentNode is a right child, or parentLink if childNode or
 *  parentNode if childNode is not a child of the parentNode.
 */
BinaryTreeNodeLink linkOfParentBinaryTreeNodeChild(
		BinaryTreeNode* parentNode, BinaryTreeNode* childNode) {
	BinaryTreeNodeLink whichLink = parentLink;
	if (parentNode != NULL) {
		if (parentNode->linkTo[rightLink] == childNode) {
			whichLink = rightLink;
		} else if (parentNode->linkTo[leftLink] == childNode) {
			whichLink = leftLink;
		}
	}
	return whichLink;
}

/**
 * Return the BinaryTreeNodeLink for a child of a parent node.
 *
 * @param childNode the child node
 * @return leftLink if the child is a left child, or rightLink if
 *   the child is a rightLink; or parentLink if child is a root.
 */
BinaryTreeNodeLink linkOfBinaryTreeNodeChild(BinaryTreeNode* childNode) {
	BinaryTreeNode* parentNode = childNode->linkTo[parentLink];
	return linkOfParentBinaryTreeNodeChild(parentNode, childNode);
}

/**
 * Find the root of a binary tree from a node.
 * @param node the node
 * @return the root node
 */
BinaryTreeNode* findBinaryTreeNodeRoot(BinaryTreeNode* node) {
	BinaryTreeNode* n = node;
	if (n != NULL) {
		while (n->linkTo[parentLink] != NULL) {
			n = n->linkTo[parentLink];
		}
	}
	return n;
}

/**
 *
 * Returns depth of a binary tree node to its root node. The depth of a node
 * is the number of edges from the node to the tree's root node. A root node
 * will have a depth of 0.
 *
 * @param node a node in the tree
 * @return the depth of the node to the tree root or -1 if node is NULL
 */
int binaryTreeNodeDepth(BinaryTreeNode* node) {
	int depth = -1;
	if (node != NULL) {
		BinaryTreeNode *cur = node;
		do {
			cur = cur->linkTo[parentLink];
			depth++;
		} while (cur != NULL);
	}
	return depth;
}


/**
 * Returns height of a binary tree from the root node. The height of a node
 * is the number of edges on the longest path from the node to a leaf. A leaf
 * node will have a height of 0. A NULL node will have a height of -1.
 *
 * @param node a node in the tree
 * @return the height of the node to the tree root
 */
int binaryTreeHeight(BinaryTreeNode* node) {
	int height = -1;
	if (node != NULL) {
		int lHeight = binaryTreeHeight(node->linkTo[leftLink]);
		int rHeight = binaryTreeHeight(node->linkTo[rightLink]);
		height = 1 + ((lHeight > rHeight) ? lHeight : rHeight);
	}
	return height;
}

/**
 * Returns number of nodes in a binary tree from the root node.
 *
 * Note: This is recursive implementation
 *
 * @param node the root node in the tree
 * @return the number of nodes in the tree
 */
int binaryTreeSize(BinaryTreeNode* node) {
	int size = 0;
	if (node != NULL) {
		size = 1 + binaryTreeSize(node->linkTo[leftLink])
		         + binaryTreeSize(node->linkTo[rightLink]);
	}
	return size;
}

