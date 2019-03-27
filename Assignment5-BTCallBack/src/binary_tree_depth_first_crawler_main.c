/*
 * binary_tree_depth_first_crawler_main.c
 *
 * This file contains tree definitions and test functions
 * for a binary tree depth-first crawler.
 *
 *  Created on: Nov 5, 2018
 *  Author: philip gust
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree_depth_first_crawler.h"

/**
 * Utility function to create and initiaize a TreeNodeData instance.
 *
 * @param val the value for the data
 * @return the new BinaryTreeNodeData
 */
BinaryTreeNodeData *newBinaryTreeNodeData(const char* val) {
	BinaryTreeNodeData* data = malloc(sizeof(BinaryTreeNodeData));
	data->strval = val;
	return data;
}

/*
 * Creates the following height 0 expression tree:
 *
 *                   5
 */
BinaryTreeNode* makeExprTree0() {
	// root node
	BinaryTreeNodeData* rootData = newBinaryTreeNodeData("5");
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	return root;
}

/*
 * Creates the following height 1 balanced expression tree:
 *
 *                   -
 *        .----------'----------.
 *        9                     4
 */
BinaryTreeNode* makeExprTree1() {
	// root node
	BinaryTreeNodeData* rootData = newBinaryTreeNodeData("-");
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = newBinaryTreeNodeData("9");
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = newBinaryTreeNodeData("4");
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);


	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	return root;
}

/*
 * Creates the following height 1 right-heavy expression tree:
 *
 *                  sqr
 *        .----------'----------.
 *                              2
 */
BinaryTreeNode* makeExprTree12() {
	// root node
	BinaryTreeNodeData* rootData = newBinaryTreeNodeData("sqr");
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// right level 1
	BinaryTreeNodeData* node11Data = newBinaryTreeNodeData("2");
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);


	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	return root;
}

/*
 * Creates the following height 2 right-heavy expression tree:
 *
 *                   -
 *        .----------'----------.
 *        9                    sqr
 *                         .----'----.
 *                                   2
 */
BinaryTreeNode* makeExprTree22() {
	// root node
	BinaryTreeNodeData* rootData = newBinaryTreeNodeData("-");
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = newBinaryTreeNodeData("9");
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = newBinaryTreeNodeData("sqr");
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);

	// right right level 2
	BinaryTreeNodeData* node23Data = newBinaryTreeNodeData("2");
	BinaryTreeNode* node23 = newBinaryTreeNode(node23Data);

	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node23, node11, rightLink);

	return root;
}

/**
 * Creates the following height 3 expression tree:
 *                    +
 *         .----------'----------.
 *         -                     *
 *    .----'----.           .----'----.
 *    9        sqr          /         7
 *           .--'--.     .--'--.
 *                 2     8     4
 */
BinaryTreeNode* makeExprTree3() {
	// root node
	BinaryTreeNodeData* rootData = newBinaryTreeNodeData("+");
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = newBinaryTreeNodeData("-");
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = newBinaryTreeNodeData("*");
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);

	// left left level 2
	BinaryTreeNodeData* node20Data = newBinaryTreeNodeData("9");
	BinaryTreeNode* node20 = newBinaryTreeNode(node20Data);

	// right left level 2
	BinaryTreeNodeData* node21Data = newBinaryTreeNodeData("sqr");
	BinaryTreeNode* node21 = newBinaryTreeNode(node21Data);

	// left right level 22
	BinaryTreeNodeData* node22Data = newBinaryTreeNodeData("/");
	BinaryTreeNode* node22 = newBinaryTreeNode(node22Data);

	// right right level 2
	BinaryTreeNodeData* node23Data = newBinaryTreeNodeData("7");
	BinaryTreeNode* node23 = newBinaryTreeNode(node23Data);


	// right left level 3
	BinaryTreeNodeData* node30Data = newBinaryTreeNodeData("2");
	node30Data->strval = "2";
	BinaryTreeNode* node30 = newBinaryTreeNode(node30Data);

	// left right level 3
	BinaryTreeNodeData* node31Data = newBinaryTreeNodeData("8");
	BinaryTreeNode* node31 = newBinaryTreeNode(node31Data);

	// right right level 3
	BinaryTreeNodeData* node32Data = newBinaryTreeNodeData("4");
	BinaryTreeNode* node32 = newBinaryTreeNode(node32Data);

	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	// level2 left left to level 1 left
	addBinaryTreeNodeAfter(node20, node10, leftLink);

	// level2 right left to level 1 left
	addBinaryTreeNodeAfter(node21, node10, rightLink);

	// level2 left right to level 1 right
	addBinaryTreeNodeAfter(node22, node11, leftLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node23, node11, rightLink);

	// level3 left left right
	// use right for to make operator prefix for single parameter
	addBinaryTreeNodeAfter(node30, node21, rightLink);

	// level3 left left right
	addBinaryTreeNodeAfter(node31, node22, leftLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node32, node22, rightLink);

	return root;
}

/**
 * Traversal callback counts nodes in pre-order.
 * @param node the BinaryTreeNode
 * @param state the traversal state
 * @param data pointer to the int count
 * @return true to continue crawling, false to terminate crawling
 */
bool countNodesInBinaryTree(BinaryTreeDepthFirstCrawler *crawler) {
	// count node on entry from parent (pre-order)
	BinaryTreeDepthFirstCrawlerState state = getBinaryTreeDepthFirstCrawlerState(crawler);
	if (state == fromParent) {
		size_t *countp = getBinaryTreeDepthFirstCrawlerData(crawler);
		(*countp)++;
	}
	return true;
}


/**
 * Write infix order expression string to traversal data string buffer.
 * left, mid, right
 * @param crawler the BinaryTreeDepthFirstCrawler;
 * @returns true to continue
 */
bool toInfix(BinaryTreeDepthFirstCrawler *crawler) {
	BinaryTreeNode *curNode = getBinaryTreeDepthFirstCrawlerNode(crawler);
	char *data = getBinaryTreeDepthFirstCrawlerData(crawler);
	BinaryTreeDepthFirstCrawlerState state = getBinaryTreeDepthFirstCrawlerState(crawler);

	switch (state) {
	case fromParent:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			sprintf(data+strlen(data), "( ");
		}
		break;
	case fromLeft:
		sprintf(data+strlen(data), "%s ", curNode->data->strval);
		break;
	case fromRight:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			sprintf(data+strlen(data), ") ");
		}
		if (isBinaryTreeNodeRoot(curNode)) {
			// trim trailing blank at end
			*(data+strlen(data)-1) = '\0';
		}
		break;
	}
	return true;
}

/**
 * Write Prefix order expression string to traversal data string buffer.
 * mid, left, right
 * @param crawler the BinaryTreeDepthFirstCrawler;
 * @returns true to continue
 */
bool toPrefix(BinaryTreeDepthFirstCrawler *crawler) {
	BinaryTreeNode *curNode = getBinaryTreeDepthFirstCrawlerNode(crawler);
	char *data = getBinaryTreeDepthFirstCrawlerData(crawler);
	BinaryTreeDepthFirstCrawlerState state = getBinaryTreeDepthFirstCrawlerState(crawler);

	switch (state) {
	case fromParent:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			sprintf(data+strlen(data), "( ");

		}
		sprintf(data+strlen(data), "%s ", curNode->data->strval);
		break;
	case fromLeft:
		//sprintf(data+strlen(data), "%s ", curNode->data->strval);
		break;
	case fromRight:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			sprintf(data+strlen(data), ") ");
		}
		if (isBinaryTreeNodeRoot(curNode)) {
			// trim trailing blank at end
			*(data+strlen(data)-1) = '\0';
		}
		break;
	}
	return true;
}

/**
 * Write Postfix order expression string to traversal data string buffer.
 *
 * @param crawler the BinaryTreeDepthFirstCrawler;
 * @returns true to continue
 */
bool toPostfix(BinaryTreeDepthFirstCrawler *crawler) {
	BinaryTreeNode *curNode = getBinaryTreeDepthFirstCrawlerNode(crawler);
	char *data = getBinaryTreeDepthFirstCrawlerData(crawler);
	BinaryTreeDepthFirstCrawlerState state = getBinaryTreeDepthFirstCrawlerState(crawler);

	switch (state) {
	case fromParent:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			//sprintf(data+strlen(data), "( ");
		}
		break;
	case fromLeft:
		//sprintf(data+strlen(data), "%s ", curNode->data->strval);
		break;
	case fromRight:
		if (!isBinaryTreeNodeLeaf(curNode)) {
			//sprintf(data+strlen(data), ") ");
		}
		sprintf(data+strlen(data), "%s ", curNode->data->strval);
		if (isBinaryTreeNodeRoot(curNode)) {
			// trim trailing blank at end
			*(data+strlen(data)-1) = '\0';
		}
		break;
	}
	return true;
}
/**
 * Test the iterative crawler function.
 * @param tree the tree to use as data.
 */
void testCrawlerIterative(BinaryTreeNode *tree) {
	printf("\nStart test crawler iterative:\n");

	size_t count = 0;
	BinaryTreeDepthFirstCrawler *crawler = newBinaryTreeDepthFirstCrawler(tree, countNodesInBinaryTree);
	bool result = startBinaryTreeDepthFirstCrawlerIterative(crawler, &count);
	printf("Count of tree is %zu\n", count);
	printf("Crawler count of tree is %zu\n", getBinaryTreeDepthFirstCrawlerCount(crawler));
	deleteBinaryTreeDepthFirstCrawler(crawler);

	char strbuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toInfix);
	result = startBinaryTreeDepthFirstCrawlerIterative(crawler, strbuf);
	printf("infix: %s\n", strbuf);
	char prebuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toPrefix);
	result = startBinaryTreeDepthFirstCrawlerIterative(crawler, prebuf);
	printf("prefix: %s\n", prebuf);
	char postbuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toPostfix);
	result = startBinaryTreeDepthFirstCrawlerIterative(crawler, postbuf);
	printf("postfix: %s\n", postbuf);
	deleteBinaryTreeDepthFirstCrawler(crawler);

	printf("End test crawler iterative:\n");
}

/**
 * Test the recursive crawler function.
 * @param tree the tree to use as data.
 */
void testCrawlerRecursive(BinaryTreeNode *tree) {
	printf("\nStart test crawler recursive:\n");

	size_t count = 0;
	BinaryTreeDepthFirstCrawler *crawler = newBinaryTreeDepthFirstCrawler(tree, countNodesInBinaryTree);
	bool result = startBinaryTreeDepthFirstCrawlerRecursive(crawler, &count);
	printf("Count of tree is %zu\n", count);
	printf("Crawler count of tree is %zu\n", crawler->count);
	deleteBinaryTreeDepthFirstCrawler(crawler);

	char strbuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toInfix);
	result = startBinaryTreeDepthFirstCrawlerRecursive(crawler, strbuf);
	printf("infix: %s\n", strbuf);
	char prebuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toPrefix);
	result = startBinaryTreeDepthFirstCrawlerIterative(crawler, prebuf);
	printf("prefix: %s\n", prebuf);
	char postbuf[256] = "";
	crawler = newBinaryTreeDepthFirstCrawler(tree, toPostfix);
	result = startBinaryTreeDepthFirstCrawlerIterative(crawler, postbuf);
	printf("postfix: %s\n", postbuf);
	deleteBinaryTreeDepthFirstCrawler(crawler);

	printf("End test crawler recursive:\n");
}

/**
 * This function creates trees and uses them to
 * test the recursive and iterative versions of
 * the depth-first binary tree crawler.
 */
int main(void) {
	BinaryTreeNode *tree0 = makeExprTree0();
	BinaryTreeNode *tree1 = makeExprTree1();
	BinaryTreeNode *tree12 = makeExprTree12();
	BinaryTreeNode *tree22 = makeExprTree22();
	BinaryTreeNode *tree3 = makeExprTree3();

	testCrawlerRecursive(tree0);
	testCrawlerIterative(tree0);

	testCrawlerRecursive(tree1);
	testCrawlerIterative(tree1);

	testCrawlerRecursive(tree12);
	testCrawlerIterative(tree12);

	testCrawlerRecursive(tree22);
	testCrawlerIterative(tree22);

	testCrawlerRecursive(tree3);
	testCrawlerIterative(tree3);
}
