/**
 * @file binary_tree_depth_first_crawler.h
 *
 * This file contains the type and function declarations
 * for a depth-first crawler for a binary tree.
 *
 * @since Nov 7, 2018
 * @author philip gust
 */

#ifndef BINARY_TREE_DEPTH_FIRST_CRAWLER_H_

#include <stdbool.h>
#include <stdint.h>
#include "binary_tree.h"

/**
 * States for depth-first traversal
 */
typedef enum {
	fromLeft,
	fromRight,
	fromParent,
} BinaryTreeDepthFirstCrawlerState;

/**
 * Provides constant for unavailable result
 */
enum {UNAVAILABLE=SIZE_MAX};

/**
 * Definition covers void* depth-first crawler data
 */
typedef void *BinaryTreeDepthFirstCrawlerData;

/** Forward declaration of struct */
struct BinaryTreeDepthFirstCrawler;

/**
 * Definition of depth-first traversal callback
 */
typedef bool (*BinaryTreeDepthFirstCrawlerCallback)
	(struct BinaryTreeDepthFirstCrawler*);

/**
 * A crawler for a binary tree
 */
typedef struct BinaryTreeDepthFirstCrawler{
	/** root node of tree */
	BinaryTreeNode *rootNode;
	/** current node being crawled */
	BinaryTreeNode *curNode;
	/** callback traversal state */
	BinaryTreeDepthFirstCrawlerState state;
	/** number of nodes traversed */
	size_t count;
	/** the crawler callback function */
	BinaryTreeDepthFirstCrawlerCallback callback;
	/** the crawler callback data */
	BinaryTreeDepthFirstCrawlerData callbackData;
} BinaryTreeDepthFirstCrawler;



/**
 * Create and initialize new crawler with the given callback.
 *
 * @param theTree the BinaryTreeDepthFirstCrawler to crawl
 * @param cb the callback for this crawler
 * @return an crawler for the list
 */
BinaryTreeDepthFirstCrawler* newBinaryTreeDepthFirstCrawler(BinaryTreeNode* theTree, BinaryTreeDepthFirstCrawlerCallback cb);

/**
 * Delete the crawler by freeing its storage.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler to delete
 */
void deleteBinaryTreeDepthFirstCrawler(BinaryTreeDepthFirstCrawler* crawler);

/**
 * Traverses the tree depth-first. Callback is called
 * during traversal when traversal enters from parent,
 * when traversal returns from the left child, and when
 * traversal returns from right child.
 *
 * @param node the root node in the tree
 * @param callback the depth first traversal callback
 * @param callbackData the traversal callback data
 * @param returns true if traversal completed, false if
 *   traversal terminated before traversal completed
 */
bool startBinaryTreeDepthFirstCrawlerIterative(
		BinaryTreeDepthFirstCrawler* crawler,
		BinaryTreeDepthFirstCrawlerData callbackData);

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
		BinaryTreeDepthFirstCrawlerData callbackData);

/**
 * Determines whether this is the first call from the crawler since last reset.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Determines whether there will be another call from the crawler
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if there is another value, false otherwise
 */
bool hasNextBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Returns the number of values returned so far.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the number of values returned so far
 */
size_t getBinaryTreeDepthFirstCrawlerCount(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Returns the number of values available.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeDepthFirstCrawlerAvailable(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Resets the crawler to the root of the tree.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeDepthFirstCrawler(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Gets the crawler callback data.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the crawler data
 */
BinaryTreeDepthFirstCrawlerData getBinaryTreeDepthFirstCrawlerData(BinaryTreeDepthFirstCrawler *crawler);

/**
 * Sets the crawler callback data. Enables callback function
 * to update shared data across multiple callbacks.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @param data the BinaryTreeCrawlerData
 * @return the crawler data
 */
void setBinaryTreeDepthFirstCrawlerData(BinaryTreeDepthFirstCrawler *crawler, BinaryTreeDepthFirstCrawlerData *data);

/**
 * Gets current tree node value in the binary tree.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @param val result parameter is pointer to result value location;  cannot be null
 * @return the current binary tree node value
 */
bool getBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler* crawler, BinaryTreeNodeData **val);

/**
* Sets the current tree node list value
*
* @param crawler the BinaryTreeDepthFirstCrawler
* @param val result parameter is pointer to result value location; cannot be null
* @return true if current value was set, false otherwise
*/
bool setBinaryTreeDepthFirstCrawlerVal(BinaryTreeDepthFirstCrawler* crawler, BinaryTreeNodeData *val);

/**
 * Gets current tree node in the binary tree.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the current BinaryTreeNode
 */
BinaryTreeNode *getBinaryTreeDepthFirstCrawlerNode(BinaryTreeDepthFirstCrawler* crawler);

/**
 * Gets the state of the crawler.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler
 * @return the crawler state
 */
BinaryTreeDepthFirstCrawlerState getBinaryTreeDepthFirstCrawlerState(BinaryTreeDepthFirstCrawler* crawler);

#endif /* BINARY_TREE_DEPTH_FIRST_CRAWLER_H_*/
