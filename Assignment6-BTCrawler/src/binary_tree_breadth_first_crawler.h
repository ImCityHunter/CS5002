/**
 * @file binary_tree_breadth_first_crawler.h
 *
 * This file contains the type and function declarations
 * for a breadth-first crawler for a binary tree.
 *
 * @since Nov 7, 2018
 * @author philip gust
 */

#ifndef BINARY_TREE_BREADTH_FIRST_CRAWLER_H_

#include <stdbool.h>
#include <stdint.h>
#include "binary_tree.h"
#include "binary_tree_iterator.h"

/**
 * States for breadth-first traversal
 */
//typedef enum {
//	fromLeft,
//	fromRight,
//	fromParent,
//} BinaryTreeBreadthFirstCrawlerState;

/**
 * Provides constant for unavailable result
 */
//enum {UNAVAILABLE=SIZE_MAX};

/**
 * Definition covers void* breadth-first crawler data
 */
typedef void *BinaryTreeBreadthFirstCrawlerData;

/** Forward declaration of struct */
struct BinaryTreeBreadthFirstCrawler;

/**
 * Definition of breadth-first traversal callback
 */
typedef bool (*BinaryTreeBreadthFirstCrawlerCallback)
	(struct BinaryTreeBreadthFirstCrawler*);

/**
 * A crawler for a binary tree
 */
typedef struct BinaryTreeBreadthFirstCrawler{
	/** root node of tree */
//	BinaryTreeNode *rootNode;
//
//	/** current node being crawled */
//	BinaryTreeNode *curNode;
//	/** callback traversal state */
//	//BinaryTreeBreadthFirstCrawlerState state;
//	/** number of nodes traversed */
//	size_t count;
	BinaryTreeIterator *itr;
	/** the crawler callback function */
	BinaryTreeBreadthFirstCrawlerCallback callback;
	/** the crawler callback data */
	BinaryTreeBreadthFirstCrawlerData callbackData;
} BinaryTreeBreadthFirstCrawler;



/**
 * Create and initialize new crawler with the given callback.
 *
 * @param theTree the BinaryTreeBreadthFirstCrawler to crawl
 * @param cb the callback for this crawler
 * @return an crawler for the list
 */
BinaryTreeBreadthFirstCrawler* newBinaryTreeBreadthFirstCrawler(BinaryTreeNode* theTree, BinaryTreeBreadthFirstCrawlerCallback cb);

/**
 * Delete the crawler by freeing its storage.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler to delete
 */
void deleteBinaryTreeBreadthFirstCrawler(BinaryTreeBreadthFirstCrawler* crawler);

/**
 * Traverses the tree breadth-first. Callback is called
 * during traversal when traversal enters from parent,
 * when traversal returns from the left child, and when
 * traversal returns from right child.
 *
 * @param node the root node in the tree
 * @param callback the breadth first traversal callback
 * @param callbackData the traversal callback data
 * @param returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeBreadthFirstCrawlerIterative(
		BinaryTreeBreadthFirstCrawler* crawler,
		BinaryTreeBreadthFirstCrawlerData callbackData);

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
		BinaryTreeBreadthFirstCrawlerData callbackData);

/**
 * Determines whether this is the first call from the crawler since last reset.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Determines whether there will be another call from the crawler
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if there is another value, false otherwise
 */
bool hasNextBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Returns the number of values returned so far.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the number of values returned so far
 */
size_t getBinaryTreeBreadthFirstCrawlerCount(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Returns the number of values available.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeBreadthFirstCrawlerAvailable(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Resets the crawler to the root of the tree.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeBreadthFirstCrawler(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Gets the crawler callback data.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the crawler data
 */
BinaryTreeBreadthFirstCrawlerData getBinaryTreeBreadthFirstCrawlerData(BinaryTreeBreadthFirstCrawler *crawler);

/**
 * Sets the crawler callback data. Enables callback function
 * to update shared data across multiple callbacks.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @param data the BinaryTreeCrawlerData
 * @return the crawler data
 */
void setBinaryTreeBreadthFirstCrawlerData(BinaryTreeBreadthFirstCrawler *crawler, BinaryTreeBreadthFirstCrawlerData *data);

/**
 * Gets current tree node value in the binary tree.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @param val result parameter is pointer to result value location;  cannot be null
 * @return the current binary tree node value
 */
bool getBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler* crawler, BinaryTreeNodeData **val);

/**
* Sets the current tree node list value
*
* @param crawler the BinaryTreeBreadthFirstCrawler
* @param val result parameter is pointer to result value location; cannot be null
* @return true if current value was set, false otherwise
*/
bool setBinaryTreeBreadthFirstCrawlerVal(BinaryTreeBreadthFirstCrawler* crawler, BinaryTreeNodeData *val);

/**
 * Gets current tree node in the binary tree.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the current BinaryTreeNode
 */
BinaryTreeNode *getBinaryTreeBreadthFirstCrawlerNode(BinaryTreeBreadthFirstCrawler* crawler);

/**
 * Gets the state of the crawler.
 *
 * @param crawler the BinaryTreeBreadthFirstCrawler
 * @return the crawler state
 */
//BinaryTreeBreadthFirstCrawlerState getBinaryTreeBreadthFirstCrawlerState(BinaryTreeBreadthFirstCrawler* crawler);

#endif /* BINARY_TREE_DEPTH_FIRST_CRAWLER_H_*/
