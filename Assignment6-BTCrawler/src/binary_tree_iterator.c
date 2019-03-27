/*
 * @file binary_tree_iterator.c
 *
 * This file provides the function implementations for a binary tree interator.
 *
 * @since 2018-11-12
 * @author philip gust
 */

#include <stdio.h>


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "binary_tree_iterator.h"

/**
 * Create and initialize a new BinaryTreeIterator
 *
 * @param theTree binary tree
 * @param the style of iteration
 * @return an iterator for the specified binary tree
 */
BinaryTreeIterator* newBinaryTreeIterator(
	BinaryTreeNode* rootNode, BinaryTreeIteratorStyle style) {
	BinaryTreeIterator* itr = (BinaryTreeIterator*)malloc(sizeof(BinaryTreeIterator));

	itr->rootNode = rootNode;
	itr->style = style;
 	itr->size =   // UNAVAILABLE causes size to be computed on first use
	  (rootNode == NULL) ? 0 : UNAVAILABLE;  // compute on first access

 	itr->deque = malloc(sizeof(ArrayDeque));
 	itr->deque = newArrayDeque(SIZE_MAX);
 	//enqueueArrayDequeVal(itr->deque,(void*)itr->rootNode);
 	resetBinaryTreeIterator(itr);
 	return itr;
}

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeIterator(BinaryTreeIterator* itr) {
	itr->count = 0;
	itr->curNode = itr->rootNode;
	itr->state = fromParent;
	itr->visitedNode = NULL;

	return true;
}

/**
 * Delete the iterator by freeing its storage.
 *
 * @param itr the LinkedListIterator to delete
 */
void deleteBinaryTreeIterator(BinaryTreeIterator* itr) {
	itr->rootNode = NULL;  // do this first
	itr->style = inOrder;	// default style
	itr->size = 0;

	resetBinaryTreeIterator(itr);
	free((void*)itr);
}

/**
 * Gets next link node in the binary tree in infix order.
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a next node, false otherwise
 */
bool getNextBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef) {

	if(itr->style == breadthFirst && itr->curNode != NULL){
					void *visited = itr->curNode; //temporary



					if(itr->curNode == itr->rootNode && isArrayDequeEmpty(itr->deque)){
							enqueueArrayDequeVal(itr->deque,(void*)itr->rootNode);
							//printf("Input root node success \n");
					}

					if(dequeueArrayDequeVal(itr->deque, &visited)){

							itr->curNode = *nodeRef = itr->visitedNode = (BinaryTreeNode *) visited;
							*nodeRef = (BinaryTreeNode *) visited;
							//printf("deque %s \n",(*nodeRef)->data->strval);

							BinaryTreeNode *left = itr->curNode->linkTo[leftLink];
							BinaryTreeNode *right = itr->curNode->linkTo[rightLink];

							if(left!=NULL) enqueueArrayDequeVal(itr->deque,left);
							if(right!=NULL) enqueueArrayDequeVal(itr->deque,right);

							const void* check;
							if(!peekFirstArrayDequeVal(itr->deque, &check)) itr->curNode = NULL;

							itr->count++;

							return true;
					}

					return false;
	}
	else{

					while (itr->curNode != NULL) {


						BinaryTreeNode *visitedNode = itr->curNode;  // set visited node


						if (itr->state == fromParent) {  // coming from parent
							if (itr->curNode->linkTo[leftLink] != NULL) {
								// traverse left from this node
								itr->state = fromParent;
								itr->curNode = itr->curNode->linkTo[leftLink];
							} else {
								// return to this node from missing left child
								itr->state = fromLeft;
								// stay on same node
							}

							// return last visited for preOrder style
							if (itr->style == preOrder) {
								*nodeRef = itr->visitedNode = visitedNode;
								itr->count++; // count visited node
								return true;  // return with visited node;
							}
						} else if (itr->state == fromLeft) { // coming from left child
							if (itr->curNode->linkTo[rightLink] != NULL) {
								// traverse right from this node
								itr->state = fromParent;
								itr->curNode = itr->curNode->linkTo[rightLink];
							} else {
								// return to this node from missing right child
								itr->state = fromRight;
								// stay on same node
							}

							// return lastVisited for inOrder style
							if (itr->style == inOrder) {
								*nodeRef = itr->visitedNode = visitedNode;
								itr->count++; // count visited node
								return true;  // return with visited node;
							}
						} else if (itr->state == fromRight){  // coming from right child
							if (itr->curNode == itr->rootNode) {
								// iteration complete, so no next node
								itr->state = fromParent;
								itr->curNode = NULL;
							} else {
								// return to parent from right node
								BinaryTreeNodeLink whichChild = linkOfBinaryTreeNodeChild(itr->curNode);
								itr->state = (whichChild == leftLink) ? fromLeft : fromRight;
								itr->curNode = itr->curNode->linkTo[parentLink];
							}

							// return lastVisited for postOrder style
							if (itr->style == postOrder) {
								*nodeRef = itr->visitedNode = visitedNode;
								itr->count++; // count visited node
								return true;  // return with visited node;
							}
						}



						}
					return false;
	}
	return false;
}


/**
 * Gets next value in the binary tree in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned data value will be returned
 * @return true if there is a next node, false otherwise
 */
bool getNextBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef) {
	BinaryTreeNode *node;
	bool hasVal = getNextBinaryTreeIteratorNode(itr, &node);
	if (hasVal) {
		*dataRef = node->data;
	}
	return hasVal;
}

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the LinkedListIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextBinaryTreeIteratorVal(BinaryTreeIterator* itr) {
	// iterator already expired
	if(itr->style==breadthFirst){
		size_t size = binaryTreeSize(itr->rootNode);
		if((itr->count - size)==0){
			return false;
		}
		else return true;

	}



	if (itr->curNode == NULL) return false;

	BinaryTreeIterator testItr = *itr;  // local copy of iterator struct
	BinaryTreeNode *node;
	bool hasVal = getNextBinaryTreeIteratorNode(&testItr, &node);
	if (!hasVal) {
			*itr = testItr;
			 //itr->curNode=NULL;
	}  // update iterator from local copy

	return hasVal;
}


/**
 * Gets previous link node in the binary tree in infix order
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getPrevBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef) {
	return false;
}

/**
 * Gets previous value in the binary tree in iterator order.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned data value will be returned
 * @return true if there is a previous value, false otherwise
 */
bool getPrevBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef) {
	return false;
}

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevBinaryTreeVal(BinaryTreeIterator* itr) {
	return false;
}

/**
 * Returns the currently visited node in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param nodeRef address where returned node will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getBinaryTreeIteratorNode(BinaryTreeIterator* itr, BinaryTreeNode **nodeRef) {
	bool hasVisited = itr->visitedNode != NULL;
	if (hasVisited) {
		*nodeRef = itr->visitedNode;
	}
	return hasVisited;
}

/**
 * Returns the currently visited value in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef address where returned value will be returned
 * @return true if there is a previous node, false otherwise
 */
bool getBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData **dataRef) {
	BinaryTreeNode *nodeRef;
	bool hasVisited = getBinaryTreeIteratorNode(itr, &nodeRef);
	if (hasVisited) {
		*dataRef = nodeRef->data;
	}
	return hasVisited;
}

/**
 * Sets the currently visited value in binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @param dataRef the value to set
 * @return true if the value is set, false otherwise
 */
bool setBinaryTreeIteratorVal(BinaryTreeIterator* itr, BinaryTreeNodeData *dataRef) {
	BinaryTreeNode *nodeRef;
	bool hasVisited = getBinaryTreeIteratorNode(itr, &nodeRef);
	if (hasVisited) {
		nodeRef->data = dataRef;
	}
	return hasVisited;
}

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the BinaryTreeIterator
 */
size_t getBinaryTreeIteratorCount(BinaryTreeIterator* itr) {
  return itr->count;
}

/**
 * Determines whether this is the first call from the iterator since last reset.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool isFirstBinaryTreeIteratorVal(BinaryTreeIterator *itr) {
	return itr->count == 0;
}

/**
 * Returns the number of nodes available.
 *
 * @param itr the BinaryTreeIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
size_t getBinaryTreeIteratorAvailable(BinaryTreeIterator* itr) {
	if (itr->size == UNAVAILABLE) {
		itr->size = binaryTreeSize(itr->rootNode);
	}
	return itr->size - itr->count;
}
