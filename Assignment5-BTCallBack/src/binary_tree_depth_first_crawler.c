/*
 * @file binary_tree_crawler.c
 *
 * This file contains the function definitions for a
 * depth-first crawler for a binary tree.
 *
 * @since Nov 7, 2018
 * @author philip gust
 */

#include <stdlib.h>

#include "binary_tree_depth_first_crawler.h"

/**
 * Create and initialize new crawler with the given callback.
 *
 * @param theTree the tree to crawl
 * @param cb the callback for this crawler
 * @return an crawler for the list
 */
BinaryTreeDepthFirstCrawler* newBinaryTreeDepthFirstCrawler(
	BinaryTreeNode* theTree, BinaryTreeDepthFirstCrawlerCallback cb) {
	BinaryTreeDepthFirstCrawler *crawler = malloc(sizeof(BinaryTreeDepthFirstCrawler));
	crawler->callback = cb;
	crawler->callbackData = NULL;
	crawler->rootNode = theTree;

	// set transient crawler state
	resetBinaryTreeDepthFirstCrawler(crawler);

	return crawler;
}

/**
 * Resets the crawler to the root of the tree.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeDepthFirstCrawler(BinaryTreeDepthFirstCrawler *crawler) {
	crawler->count = 0;
	crawler->curNode = crawler->rootNode;
	crawler->state = fromParent;
	return true;
}

/**
 * Delete the crawler by freeing its storage.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler to delete
 */
void deleteBinaryTreeDepthFirstCrawler(BinaryTreeDepthFirstCrawler* crawler){
	crawler->rootNode = NULL;  // do this first!
	crawler->callbackData = NULL;
	crawler->callback = NULL;

	// set transient crawler state
	resetBinaryTreeDepthFirstCrawler(crawler);

	free(crawler);
}

/**
 * Traverses the tree depth-first. Callback is called during
 * traversal when traversal enters from parent, returns from
 * the left child, and returns from right child.
 *
 * Recursive helper function visits the current, then the
 * left subtree, then the right subtree.
 *
 * @param crawler the crawler
 * @return true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
static bool binaryTreeDepthFirstCrawlerRecursive(BinaryTreeDepthFirstCrawler* crawler) {
	BinaryTreeNode *curNode = getBinaryTreeDepthFirstCrawlerNode(crawler);
	if (curNode != NULL) {
		// count visited node
		crawler->count++;

		// notify visiting node from parent
		crawler->state = fromParent;
		if (!crawler->callback(crawler)) return false;


		// visit left child
		crawler->curNode = curNode->linkTo[leftLink];
		if (!binaryTreeDepthFirstCrawlerRecursive(crawler)) return false;
		// notify returning from left child
		crawler->curNode = curNode;
		crawler->state = fromLeft;
		if (!crawler->callback(crawler)) {
			return false;
		}

		// visit right child
		crawler->curNode = curNode->linkTo[rightLink];
		if (!binaryTreeDepthFirstCrawlerRecursive(crawler)) return false;

		// notify returning from right child
		crawler->curNode = curNode;
		crawler->state = fromRight;
		if (!crawler->callback(crawler)) {
			return false;
		}
	}
	return true;
}

/**
 * Traverses the tree depth-first. Callback is called during
 * traversal when traversal enters from parent, returns from
 * the left child, and returns from right child.
 *
 * This recursive version visits the current node, then the
 * left and right subtrees.
 *
 * @param node the root node in the tree
 * @param callback the depth first traversal callback
 * @param callbackData the traversal callback data
 * @param returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeDepthFirstCrawlerRecursive(
		BinaryTreeDepthFirstCrawler* crawler,
		BinaryTreeDepthFirstCrawlerData callbackData) {
	setBinaryTreeDepthFirstCrawlerData(crawler, callbackData);
	return binaryTreeDepthFirstCrawlerRecursive(crawler);
}


/**
 * Traverses the tree depth-first. Callback is called
 * during traversal when traversal enters from parent,
 * when traversal returns from the left child, and when
 * traversal returns from right child.
 *
 * This iterative version uses current node and direction
 * of traversal to determine the next node in the traversal.
 *
 * @param node the root node in the tree
 * @param callback the depth first traversal callback
 * @param callbackData the traversal callback data
 * @return returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeDepthFirstCrawlerIterative(
		BinaryTreeDepthFirstCrawler* crawler,
		BinaryTreeDepthFirstCrawlerData callbackData) {

	// come from missing parent of this node
	crawler->state = fromParent;
	setBinaryTreeDepthFirstCrawlerData(crawler, callbackData);

	while (crawler->curNode != NULL) {
		if (crawler->state == fromParent) {  // coming from parent
			// count visited node
			crawler->count++;

			// notify coming from parent node
			if (!crawler->callback(crawler)) {
				return false;
			}

			if (crawler->curNode->linkTo[leftLink] != NULL) {
				// traverse left from this node
				crawler->state = fromParent;
				crawler->curNode = crawler->curNode->linkTo[leftLink];
			} else {
				// return to this node from missing left child
				crawler->state = fromLeft;
				// stay on same node
			}
		} else if (crawler->state == fromLeft) { // coming from left child
			// notify return from left node
			if (!crawler->callback(crawler)) {
				return false;
			}

			if (crawler->curNode->linkTo[rightLink] != NULL) {
				// traverse right from this node
				crawler->state = fromParent;
				crawler->curNode = crawler->curNode->linkTo[rightLink];
			} else {
				// return to this node from missing right child
				crawler->state = fromRight;
				// stay on same node
			}

		} else if (crawler->state == fromRight) {  // prvLink == rightLink coming from right child
			// notify return from right node
			if (!crawler->callback(crawler)) {
				return false;
			}

			// return from this node as left or right child of parent
			BinaryTreeNodeLink whichChild = linkOfBinaryTreeNodeChild(crawler->curNode);
			crawler->state = (whichChild == leftLink) ? fromLeft : fromRight;
			// done if back at root from right
			crawler->curNode =
				(crawler->curNode == crawler->rootNode) ? NULL : crawler->curNode->linkTo[parentLink];
		}
	}

	return true;
}

/**
 * Returns the number of values returned so far.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the number of values returned so far
 */
size_t getBinaryTreeDepthFirstCrawlerCount(BinaryTreeDepthFirstCrawler *crawler) {
	return crawler->count;
}

/**
 * Determines whether this is the first call from the crawler since last reset.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler *crawler) {
	return crawler->count == 1;
}

/**
 * Determines whether there will be another call from the crawler
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if there is another value, false otherwise
 */
bool hasNextBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler *crawler) {
	return false;  // temporary
}

/**
 * Returns the number of values available.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeDepthFirstCrawlerAvailable(BinaryTreeDepthFirstCrawler *crawler) {
	return UNAVAILABLE;  // temporary
}


/**
 * Gets the crawler callback data.
 *
 * @param crawler the BinaryTreeDeptFirstCrawler
 * @return the crawler data
 */
BinaryTreeDepthFirstCrawlerData getBinaryTreeDepthFirstCrawlerData(BinaryTreeDepthFirstCrawler *crawler) {
	return crawler->callbackData;
}

/**
 * Sets crawler callback data. Enables callback function
 * to update shared data across multiple callbacks.
 *
 * @param crawler the BinaryTreeDeptFirstCrawler
 * @param data the BinaryTreeDeptFirstCallerData
 */
void setBinaryTreeDepthFirstCrawlerData(BinaryTreeDepthFirstCrawler *crawler, BinaryTreeDepthFirstCrawlerData *data) {
	crawler->callbackData = data;
}

/**
 * Gets current tree node value in the array list.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @param val result parameter is pointer to result value location;  cannot be null
 * @return the current binary tree node value
 */
bool getBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler* crawler, BinaryTreeNodeData **val) {
	bool hasNode = crawler->curNode != NULL;
	if (hasNode) {
		*val = crawler->curNode->data;
	}
	return hasNode;
}

/**
 * Sets the current tree node value.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @param val result parameter is pointer to result value location; cannot be null
 * @return true if current value was set, false otherwise
 */
bool setBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler* crawler, BinaryTreeNodeData *val) {
	bool hasNode = crawler->curNode != NULL;
	if (hasNode) {
		crawler->curNode->data = val;
	}
	return hasNode;
}

/**
 * Gets current tree node in the binary tree.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the current BinaryTreeNode
 */
BinaryTreeNode *getBinaryTreeDepthFirstCrawlerNode(BinaryTreeDepthFirstCrawler* crawler) {
	return crawler->curNode;
}

/**
 * Gets the state of the crawler.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the crawler state
 */
BinaryTreeDepthFirstCrawlerState getBinaryTreeDepthFirstCrawlerState(BinaryTreeDepthFirstCrawler* crawler) {
	return crawler->state;
}
