/*
 * @file binary_tree_crawler.c
 *
 * This file contains the function definitions for a
 * breadth-first crawler for a binary tree.
 *
 * @since Nov 7, 2018
 * @author philip gust
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree_breadth_first_crawler.h"


/**
 * Create and initialize new crawler with the given callback.
 *
 * @param theTree the tree to crawl
 * @param cb the callback for this crawler
 * @return an crawler for the list
 */
BinaryTreeBreadthFirstCrawler* newBinaryTreeBreadthFirstCrawler(
	BinaryTreeNode* theTree, BinaryTreeBreadthFirstCrawlerCallback cb) {
	BinaryTreeBreadthFirstCrawler *crawler = malloc(sizeof(BinaryTreeBreadthFirstCrawler));
	crawler->callback = cb;
	crawler->callbackData = NULL;
    crawler->itr = malloc(sizeof(BinaryTreeIterator*));
    crawler->itr = newBinaryTreeIterator(theTree,breadthFirst);
	//crawler->rootNode = theTree;

	// set transient crawler state
	resetBinaryTreeBreadthFirstCrawler(crawler);

	return crawler;
}

/**
 * Resets the crawler to the root of the tree.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeBreadthFirstCrawler(BinaryTreeBreadthFirstCrawler *crawler) {
//	crawler->count = 0;
//	crawler->curNode = crawler->rootNode;
//	//crawler->state = fromParent;
	resetBinaryTreeIterator(crawler->itr);
	return true;
}

/**
 * Delete the crawler by freeing its storage.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler to delete
 */
void deleteBinaryTreeBreadthFirstCrawler(BinaryTreeBreadthFirstCrawler* crawler){
	//crawler->rootNode = NULL;  // do this first!
	crawler->callbackData = NULL;
	crawler->callback = NULL;

	// set transient crawler state
	resetBinaryTreeBreadthFirstCrawler(crawler);

	free(crawler);
}

/**
 * Traverses the tree breadth-first. Callback is called during
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
static bool binaryTreeBreadthFirstCrawlerRecursive(BinaryTreeBreadthFirstCrawler* crawler) {
	//printf("Recursive not needed \n");
	BinaryTreeNode *curNode = getBinaryTreeBreadthFirstCrawlerNode(crawler);
	if(curNode!=NULL){

	}
	return true;
}

/**
 * Traverses the tree breadth-first. Callback is called during
 * traversal when traversal enters from parent, returns from
 * the left child, and returns from right child.
 *
 * This recursive version visits the current node, then the
 * left and right subtrees.
 *
 * @param node the root node in the tree
 * @param callback the breadth first traversal callback
 * @param callbackData the traversal callback data
 * @param returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeBreadthFirstCrawlerRecursive(
		BinaryTreeBreadthFirstCrawler* crawler,
		BinaryTreeBreadthFirstCrawlerData callbackData) {
	setBinaryTreeBreadthFirstCrawlerData(crawler, callbackData);
	return binaryTreeBreadthFirstCrawlerRecursive(crawler);
}


/**
 * Traverses the tree breadth-first. Callback is called
 * during traversal when traversal enters from parent,
 * when traversal returns from the left child, and when
 * traversal returns from right child.
 *
 * This iterative version uses current node and direction
 * of traversal to determine the next node in the traversal.
 *
 * @param node the root node in the tree
 * @param callback the breadth first traversal callback
 * @param callbackData the traversal callback data
 * @return returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeBreadthFirstCrawlerIterative(
		BinaryTreeBreadthFirstCrawler* crawler,
		BinaryTreeBreadthFirstCrawlerData callbackData) {

	BinaryTreeNode * dataRef;
	//crawler->callbackData = callbackData;
	setBinaryTreeBreadthFirstCrawlerData(crawler, callbackData);
	//BinaryTreeIterator* itr = newBinaryTreeIterator(crawler->rootNode,breadthFirst);
	//getNextBinaryTreeIteratorNode(itr,dataRef);
	while(getNextBinaryTreeIteratorNode(crawler->itr,&dataRef)){
		//printf("in crawler \n");
		//printf(" %s ",crawler->itr->curNode->data->strval);
		if(!crawler->callback(crawler)){

			return false;
		}


	}
	return true;









	//write codes here

	return true;
}

/**
 * Returns the number of values returned so far.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the number of values returned so far
 */
size_t getBinaryTreeBreadthFirstCrawlerCount(BinaryTreeBreadthFirstCrawler *crawler) {
	return crawler->itr->count;
}

/**
 * Determines whether this is the first call from the crawler since last reset.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler *crawler) {
	return crawler->itr->count == 1;
}

/**
 * Determines whether there will be another call from the crawler
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if there is another value, false otherwise
 */
bool hasNextBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler *crawler) {
	return false;  // temporary
}

/**
 * Returns the number of values available.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeBreadthFirstCrawlerAvailable(BinaryTreeBreadthFirstCrawler *crawler) {
	return UNAVAILABLE;  // temporary
}


/**
 * Gets the crawler callback data.
 *
 * @param crawler the BinaryTreeDeptFirstCrawler
 * @return the crawler data
 */
BinaryTreeBreadthFirstCrawlerData getBinaryTreeBreadthFirstCrawlerData(BinaryTreeBreadthFirstCrawler *crawler) {
	return crawler->callbackData;
}

/**
 * Sets crawler callback data. Enables callback function
 * to update shared data across multiple callbacks.
 *
 * @param crawler the BinaryTreeDeptFirstCrawler
 * @param data the BinaryTreeDeptFirstCallerData
 */
void setBinaryTreeBreadthFirstCrawlerData(BinaryTreeBreadthFirstCrawler *crawler, BinaryTreeBreadthFirstCrawlerData *data) {
	crawler->callbackData = data;
}

/**
 * Gets current tree node value in the array list.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @param val result parameter is pointer to result value location;  cannot be null
 * @return the current binary tree node value
 */
bool getBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler* crawler, BinaryTreeNodeData **val) {
	bool hasNode = crawler->itr->curNode != NULL;
	if (hasNode) {
		*val = crawler->itr->curNode->data;
	}
	return hasNode;
}

/**
 * Sets the current tree node value.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @param val result parameter is pointer to result value location; cannot be null
 * @return true if current value was set, false otherwise
 */
bool setBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler* crawler, BinaryTreeNodeData *val) {
	bool hasNode = crawler->itr->curNode != NULL;
	if (hasNode) {
		crawler->itr->curNode->data = val;
	}
	return hasNode;
}

/**
 * Gets current tree node in the binary tree.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the current BinaryTreeNode
 */
BinaryTreeNode *getBinaryTreeBreadthFirstCrawlerNode(BinaryTreeBreadthFirstCrawler* crawler) {

	return crawler->itr->curNode;
}

/**
 * Gets the state of the crawler.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the crawler state
 */
//BinaryTreeBreadthFirstCrawlerState getBinaryTreeBreadthFirstCrawlerState(BinaryTreeBreadthFirstCrawler* crawler) {
//	return crawler->state;
//}
