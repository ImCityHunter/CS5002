/*
 * binary_search_tree_impl.h
 *
 * This file contains implementation-only function definitions.
 * These are subject to change as the implementation of public
 * functions changes.
 *
 *  @since 2017-02-22
 *  @author Philip Gust
 */

#ifndef BINARY_SEARCH_TREE_IMPL_H_
#define BINARY_SEARCH_TREE_IMPL_H_

#include "binary_search_tree.h"

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
	findLastBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Add the data to the left or right of the specified node.
 *
 * @param node the parent of the new node
 * @param data the node data for the new node (takes ownership of data)
 *
 * For implementation only
 */
BinaryTreeNode*
  addBinarySearchTreeChildNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Remove this node from the tree.
 *
 * @param node the node to remove
 * @return the parent of the node removed
 *
 * For implementation only
 */
BinaryTreeNode* deleteBinarySearchTreeChildNode (BinaryTreeNode* node);

#endif /* BINARY_SEARCH_TREE_IMPL_H_ */
