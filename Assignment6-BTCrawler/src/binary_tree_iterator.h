/*
 * @file binary_tree_iterator.h
 *
 * This file provides the structure and function definitions for an
 * iterator of a binary tree.
 *
 * @since 2018-11-12
 * @author philip gust
 */

#ifndef BINARY_TREE_ITERATOR_H_
#define BINARY_TREE_ITERATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include "binary_tree.h"
#include "array_deque.h"

/**
 * States for iteration.
 */
typedef enum {
	fromLeft = leftLink,
	fromRight = rightLink,
	fromParent = parentLink,

} BinaryTreeIteratorState;

/**
 * Style for iteration.
 */
typedef enum {
	inOrder = fromLeft,
	postOrder = fromRight,
	preOrder = fromParent,
	breadthFirst
} BinaryTreeIteratorStyle;

/**
 * Provides constant for unavailable result
 */
enum {UNAVAILABLE=SIZE_MAX};

/**
 * An iterator for a binary tree
 */
typedef struct {
	/** root node of tree */
	BinaryTreeNode *rootNode;
	/** current node being crawled */
	BinaryTreeNode *curNode;
	/** currently visited node */
	BinaryTreeNode *visitedNode;
	/** style of iterator */
	BinaryTreeIteratorStyle style;
	/** callback traversal state */
	BinaryTreeIteratorState state;
	/** number of nodes traversed */
	size_t count;
	/** the size of the tree */
	size_t size;
	ArrayDeque *deque;
} BinaryTreeIterator;


/**
 * Create and initialize a new BinaryTreeIterator
 *
 * @param theTree binary tree
 * @param the style of iteration
 * @return an iterator for the specified binary tree
 */
BinaryTreeIterator* newBinaryTreeIterator(BinaryTreeNode* theTree, BinaryTreeIteratorStyle style);

/**
 * Freeing iterator storage.
 *
 * @param itr the BinaryTreeIterator to delete
 */
void deleteBinaryTreeIterator(BinaryTreeIterator* itr);

/**
 * Gets next node in the binary tree in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a next node, false otherwise
 */
bool getNextBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef);

/**
 * Gets next value in the binary tree in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned data value will be returned
 * @return true if there is a next node, false otherwise
 */
bool getNextBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef);

/**
 * Determines whether there is another value in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is another value, false otherwise
 */
bool hasNextBinaryTreeIteratorVal(BinaryTreeIterator* itr);

/**
 * Gets previous value in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getPrevBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef);

/**
 * Gets previous value in the binary tree in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned data value will be returned
 * @return true if there is a previous value, false otherwise
 */
bool getPrevBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef);

/**
 * Determines whether there is a previous value in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is a previous value, false otherwise
 */
bool hasPrevBinaryTreeIteratorVal(BinaryTreeIterator* itr);

/**
 * Returns the currently visited node in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef);

/**
 * Returns the currently visited value in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned value will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef);

/**
 * Sets the currently visited value in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef the value to set
 * @return true if the value is set, false otherwise
 */
bool setBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData *dataRef);

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeIterator(BinaryTreeIterator* itr);

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the BinaryTreeIterator
 */
size_t getBinaryTreeIteratorCount(BinaryTreeIterator* itr);

/**
 * Determines whether this is the first call from the iterator since last reset.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeIteratorVal(BinaryTreeIterator *itr);

/**
 * Returns the number of nodes available.
 *
 * @param itr the BinaryTreeIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeIteratorAvailable(BinaryTreeIterator* itr);

#endif /* BINARY_TREE_ITERATOR_H_ */
