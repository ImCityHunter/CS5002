/*
 * binary_search_tree.c
 *
 *  @since 2017-02-22
 *  @author Philip Gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <assert.h>

#include "binary_search_tree.h"

/**
 * Find the node with the smallest value that is greater than
 * or equal to the given data.
 *
 * @param node the root of a binary tree
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = node;
	BinaryTreeNode* prv = NULL;

	while (cur != NULL) {
		int comp = compareBinaryTreeNodeData(data, cur->data);
		if (comp < 0) {
			// data less than node: mark node and go left to lesser node
			prv = cur;
			cur = cur->linkTo[leftLink];
		} else if (comp > 0) {
			// data greater than node: look for smaller value in its right subtree
			cur = cur->linkTo[rightLink];
		} else {
			return cur; // found node: return it.


		}
	}
	return prv;  // return least greater marked node
}

/**
 * Find the node with the specified value or the node that would
 * be the parent of the specified value if it were in the tree.
 *
 * @param node the root of the binary tree
 * @param the value beings sought
 * @return  the node with the specified value or the node that
 * 	would be the parent of the specified value if it were in the tree
 *
 * For implementation only
 */
BinaryTreeNode*
  findLastBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = node;
	BinaryTreeNode* prv = NULL;

	while (cur != NULL) {
		prv = cur;	// remember parent node;
		int c = compareBinaryTreeNodeData(data, cur->data);
		if (c < 0) {
			// value less than node: see if room for node as left child
			cur = cur->linkTo[leftLink];
		} else if (c > 0) {
			// value greater than node: see if room for node as right child
			cur = cur->linkTo[rightLink];
		} else {
			// node with value already in tree: return it
			return cur;
		}
	}
	return prv;
}

/**
 * Find the node in the tree whose data equals the given data
 *
 * @param node the root of a binary tree
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findEqualBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = findLastBinarySearchTreeNode(node, data);
	return ((cur != NULL) && (compareBinaryTreeNodeData(data, cur->data) == 0)) ? cur : NULL;
}

/**
 * Add the data to the left or right of the specified node.
 *
 * @param node the parent of the new node
 * @param data the node data for the new node (takes ownership of data)
 * @return new node or NULL if data already in tree
 *
 * For implementation only
 */
static BinaryTreeNode*
  addBinarySearchTreeChildNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	if (node == NULL) {
		return newBinaryTreeNode(data);  // return root node

	}

	int comp = compareBinaryTreeNodeData(data, node->data);
	if (comp == 0) {
		return NULL;  // no action if node already in tree
	}

	// determine on which side to insert this child
	BinaryTreeNodeLink whichLink = (comp < 0) ? leftLink : rightLink;

	// add new node as child
	BinaryTreeNode* newNode = newBinaryTreeNode(data);
	if  (addBinaryTreeNodeAfter(newNode, node, whichLink)) {
		return newNode;
	}
	// error: child position not empty
	deleteBinaryTreeNode(newNode);
	return NULL;
}

/**
 * Add a node to a binary search tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the new node or NULL if already in the tree
 */
BinaryTreeNode* addBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode *last = findLastBinarySearchTreeNode(node, data);
	return addBinarySearchTreeChildNode(last, data);
}

/**
 * Splice the specified node out of the tree. The node
 * must have only 0 or 1 children.
 *
 * @param node the node to splice out
 */
static void spliceBinarySearchTreeNode (BinaryTreeNode* node) {
	BinaryTreeNode* nextNode;
	BinaryTreeNode* prevNode;
	if (node->linkTo[leftLink] != NULL) {
		nextNode = node->linkTo[leftLink];
	} else {
		nextNode = node->linkTo[rightLink];
	}

	if (node->linkTo[parentLink] == NULL) { // is root
		prevNode = NULL;
	} else {
		prevNode = node->linkTo[parentLink];
		BinaryTreeNodeLink link = // left or right parent link
				(prevNode->linkTo[leftLink] == node) ? leftLink : rightLink;
		prevNode->linkTo[link] = nextNode; // relink parent link to next node
	}
	if (nextNode != NULL) {
		nextNode->linkTo[parentLink] = prevNode;
	}
}

/**
 * Remove this node from the tree.
 * 
 * @param node the node to remove
 * @return the parent of the node removed
 *
 * For implementation only
 */
BinaryTreeNode* deleteBinarySearchTreeChildNode (BinaryTreeNode* node) {
	BinaryTreeNodeLink exteriorLink =
		(node->linkTo[leftLink] == NULL) ? rightLink : leftLink;
	BinaryTreeNodeLink interiorLink = otherBinaryTreeNodeChildLink(exteriorLink);
	BinaryTreeNode* nextNode = node;
	if (nextNode->linkTo[exteriorLink] != NULL) {
		// find deepest interior node of exterior child node
		nextNode = nextNode->linkTo[exteriorLink];
		while (nextNode->linkTo[interiorLink] != NULL) {
			nextNode = nextNode->linkTo[interiorLink];
		}
		// Remove interior node by having it become the next larger
		BinaryTreeNodeData *t = node->data; // exchange node data
		node->data = nextNode->data;
		nextNode->data = t;
	}
	// record the parent of node being removed
	BinaryTreeNode* parentNode = nextNode->linkTo[parentLink];

	// then splicing out the no longer needed node
	spliceBinarySearchTreeNode(nextNode);

	// free the spliced out node
	deleteBinaryTreeNode(nextNode);

	return parentNode;
}

/**
 * Remove the node with this node data from the tree.
 *
 * @param node the root of a binary search tree
 * @param data of the node to remove
 * @return the parent node of the node removed or NULL if node not in the tree.
 */
BinaryTreeNode* deleteBinarySearchTreeNode (BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* nodeToRemove = findEqualBinarySearchTreeNode(node, data);
	if (nodeToRemove == NULL) {
		return NULL;
	}
	return deleteBinarySearchTreeChildNode(nodeToRemove);
}

