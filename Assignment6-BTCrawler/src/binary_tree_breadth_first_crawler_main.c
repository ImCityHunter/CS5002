/*
 * binary_tree_breadth_first_crawler_main.c
 *
 * This file contains tree definitions and test functions
 * for a binary tree breadth-first crawler.
 *
 *  Created on: Nov 5, 2018
 *  Author: philip gust
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "binary_tree.h"
#include "binary_tree_iterator.h"

#include "binary_tree_breadth_first_crawler.h"

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
bool countNodesInBinaryTree(BinaryTreeBreadthFirstCrawler *crawler) {


	size_t *countp = getBinaryTreeBreadthFirstCrawlerData(crawler);
	(*countp)++;
	return true;
}


bool breadthSearch (BinaryTreeBreadthFirstCrawler *crawler){
	//printf("start BS \n");

	//char* data = (char *) crawler->itr->curNode->data->strval;
   	char* data = getBinaryTreeBreadthFirstCrawlerData(crawler);
   	//char* node = (char *) crawler->itr->curNode->data->strval;

   	//printf(" %s ",node);


   	//sprintf(data+strlen(data)," %s ",crawler->itr->curNode->data->strval);
   	sprintf(data+strlen(data)," %s ",crawler->itr->visitedNode->data->strval);
	return true;
}


/**
 * Test the iterative crawler function.
 * @param tree the tree to use as data.
 */
void testCrawlerIterative(BinaryTreeNode *tree) {
	printf("\nStart test crawler iterative:\n");

	//size_t count = 0;
	char strbuf[256] = "";
	BinaryTreeBreadthFirstCrawler *crawler = newBinaryTreeBreadthFirstCrawler(tree, breadthSearch);
	startBinaryTreeBreadthFirstCrawlerIterative(crawler, strbuf);
	printf("BreadthSearch: %s\n",strbuf);
	deleteBinaryTreeBreadthFirstCrawler(crawler);

	size_t count=0;
	crawler = newBinaryTreeBreadthFirstCrawler(tree,countNodesInBinaryTree);
	startBinaryTreeBreadthFirstCrawlerIterative(crawler, &count);
	printf("Crawler count: %ld \n",count);
	printf("Tree size: %d \n",binaryTreeSize(tree));



	deleteBinaryTreeBreadthFirstCrawler(crawler);

	printf("End test crawler iterative:\n");
}

/**
 * Test of binary tree iterator for empty (NULL) expr tree
 */
static void testBinaryTreeIteratorNULL(void) {
	const int nodeCount = 0;
    const char* results[][0] = {
    	{},  // inorder
		{},  // postorder
		{},   // preorder
		{}	//breadthFirst
    };

    BinaryTreeNode* tree = NULL;

    for (BinaryTreeIteratorStyle style = inOrder; style <= breadthFirst; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {
			BinaryTreeNode* node;
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			if (node != (BinaryTreeNode*)NULL) {
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
			}
		}
		CU_ASSERT_EQUAL(nodeCount, count);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));  // no nodes
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}

/**
 * Test of binary tree iterator for 0 height expr tree
 */
static void testBinaryTreeIterator0(void) {
	const int nodeCount = 1;
    const char* results[][1] = {
    	{"5"}, 	// inorder
		{"5"}, 	// postorder
		{"5"},  // preorder
		{"5"}   // breadthFirst
    };

    BinaryTreeNode* tree = makeExprTree0();

    for (BinaryTreeIteratorStyle style = inOrder; style <= breadthFirst; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);

		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		//if(style==breadthFirst) printf("here 01 %s \n",itr->curNode->data->strval);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		//if(style==breadthFirst) printf("here 02 %s \n",itr->curNode->data->strval);
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {

			//if(style==breadthFirst) printf("here 03 %s \n",itr->curNode->data->strval);


			BinaryTreeNode* node;
			//if(style==breadthFirst) printf("here 04 %s \n",itr->curNode->data->strval);
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			//if(style==breadthFirst) printf("here 05 %s \n",node->data->strval);
			if (node != (BinaryTreeNode*)NULL) {
				//if(style==breadthFirst) printf("here 06 %s \n",node->data->strval);
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
				//if(style==breadthFirst) printf("here 010 %s \n",results[style][count]);
			}
			//if(style==breadthFirst) printf("here 09");
		}
		//if(style==breadthFirst) printf("here 07");
		CU_ASSERT_EQUAL(nodeCount, count);
		//if(style==breadthFirst) printf("here 08");
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}

/**
 * Test of binary tree iterator for 0 height expr tree
 */
static void testBinaryTreeIterator1(void) {
    const int nodeCount = 3;
    const char* results[][3] = {
    	{"9", "-", "4"}, 	// inorder
		{"9", "4", "-"}, 	// postorder
		{"-", "9", "4"},	// preorder
		{"-", "9", "4"}		// breadthFirst
    };
    BinaryTreeNode* tree = makeExprTree1();

    for (BinaryTreeIteratorStyle style = inOrder; style <= breadthFirst; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {

			BinaryTreeNode* node;
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			if (node != (BinaryTreeNode*)NULL) {
//				if(style == breadthFirst) {printf("\nnode %s, ",node->data->strval);}
//				if(style == breadthFirst) {printf("result %s \n",results[style][count]);}
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
			}
		}
		CU_ASSERT_EQUAL(nodeCount, count);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}

/**
 * Test of binary tree iterator for 1 height expr tree inbalanced right
 */
static void testBinaryTreeIterator12(void) {
    const int nodeCount = 2;
    const char* results[][2] = {
    		{"sqr", "2"}, 	// inorder
			{"2", "sqr"},	// postorder
			{"sqr", "2"},	// preorder
			{"sqr", "2"} 	// breadthFirst
    };
    BinaryTreeNode* tree = makeExprTree12();
    for (BinaryTreeIteratorStyle style = inOrder; style <= breadthFirst; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {
			BinaryTreeNode* node;
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			if (node != (BinaryTreeNode*)NULL) {
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
			}
		}
		CU_ASSERT_EQUAL(nodeCount, count);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}

/**
 * Test of binary tree iterator for 2 height expr tree inbalanced right
 */
static void testBinaryTreeIterator22(void) {
    const int nodeCount = 4;
    const char* results[][4] = {
    	{"9", "-", "sqr", "2"},	// inorder
		{"9", "2", "sqr", "-"},	// postorder
		{"-", "9", "sqr", "2"},	// preorder
    	{"-", "9", "sqr", "2"}	// breadthFirst
    };
    BinaryTreeNode* tree = makeExprTree22();

    for (BinaryTreeIteratorStyle style = inOrder; style <= breadthFirst; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {
			BinaryTreeNode* node;
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			if (node != (BinaryTreeNode*)NULL) {
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
			}
		}
		CU_ASSERT_EQUAL(nodeCount, count);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}

/**
 * Test of binary tree iterator for 2 height expr tree
 */
static void testBinaryTreeIterator3(void) {
    const int nodeCount = 10;
    const char* results[][10] = {
    		{"9", "-", "sqr", "2", "+", "8", "/", "4", "*", "7"},	// inorder
    		{"9", "2", "sqr", "-", "8", "4", "/", "7", "*", "+"},	// postorder
			{"+", "-", "9", "sqr", "2", "*", "/", "8", "4", "7"}	// preorder
    };

    BinaryTreeNode* tree = makeExprTree3();

    for (BinaryTreeIteratorStyle style = inOrder; style <= preOrder; style++) {
		BinaryTreeIterator* itr = newBinaryTreeIterator(tree, style);
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
		int count = 0;
		for ( ; hasNextBinaryTreeIteratorVal(itr) && count < nodeCount; count++) {
			BinaryTreeNode* node;
			CU_ASSERT_TRUE(getNextBinaryTreeIteratorNode(itr, &node));
			if (node != (BinaryTreeNode*)NULL) {
				CU_ASSERT_STRING_EQUAL(node->data->strval, results[style][count]);
			}
		}
		CU_ASSERT_EQUAL(nodeCount, count);
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

		resetBinaryTreeIterator(itr);
		CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(itr));
		CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
		CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));

		deleteBinaryTreeIterator(itr);
    }
    deleteAllBinaryTreeNodes(tree);
}
/**
 * All Trees should have already be printed with BreadthSearch
 * This is just example of using cunit to test crawler
 */
static void testBinaryCrawlerIterator_tree10_cunit(void){

	printf("\n\n\n\tTest Crawler with cunit (tree10): \n");
	BinaryTreeNode *tree10 = makeExprTree3();
	BinaryTreeBreadthFirstCrawler *crawler = newBinaryTreeBreadthFirstCrawler(tree10, breadthSearch);
	//size_t count = 0;
	const char* result={" +  -  *  9  sqr  /  7  2  8  4 "};
	char strbuf[256] = "";

	startBinaryTreeBreadthFirstCrawlerIterative(crawler, strbuf);
	printf("\tBreadthSearch: %s\n",strbuf);
	printf("\tResult: %s\n",result);
	CU_ASSERT_STRING_EQUAL(strbuf,result);
	deleteBinaryTreeBreadthFirstCrawler(crawler);
	int treeSize=binaryTreeSize(tree10);
	size_t count=0;
	crawler = newBinaryTreeBreadthFirstCrawler(tree10,countNodesInBinaryTree);
	startBinaryTreeBreadthFirstCrawlerIterative(crawler, &count);
	printf("\tCrawler count: %ld \n",count);
	printf("\tTree size: %d \n",treeSize);
	CU_ASSERT_EQUAL(binaryTreeSize(tree10), count);

	resetBinaryTreeBreadthFirstCrawler(crawler);
	CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(crawler->itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(crawler->itr));
	CU_ASSERT_EQUAL(treeSize, getBinaryTreeIteratorAvailable(crawler->itr));
	deleteBinaryTreeBreadthFirstCrawler(crawler);
}
/**
 * All Trees should have already be printed with BreadthSearch
 * This is just example of using cunit to test crawler
 */
static void testBinaryCrawlerIterator_tree0_cunit(void){

	printf("\n\n\n\tTest Crawler with cunit (tree0): \n");
	BinaryTreeNode *tree0 = makeExprTree0() ;
	BinaryTreeBreadthFirstCrawler *crawler = newBinaryTreeBreadthFirstCrawler(tree0, breadthSearch);
	//size_t count = 0;
	const char* result=" 5 ";
	char strbuf[256] = "";

	startBinaryTreeBreadthFirstCrawlerIterative(crawler, strbuf);
	printf("\tBreadthSearch: %s\n",strbuf);
	printf("\tResult: %s\n",result);
	CU_ASSERT_STRING_EQUAL(strbuf,result);
	deleteBinaryTreeBreadthFirstCrawler(crawler);
	int treeSize=binaryTreeSize(tree0);
	size_t count=0;
	crawler = newBinaryTreeBreadthFirstCrawler(tree0,countNodesInBinaryTree);
	startBinaryTreeBreadthFirstCrawlerIterative(crawler, &count);
	printf("\tCrawler count: %ld \n",count);
	printf("\tTree size: %d \n",treeSize);
	CU_ASSERT_EQUAL(binaryTreeSize(tree0), count);

	resetBinaryTreeBreadthFirstCrawler(crawler);
	CU_ASSERT_TRUE(hasNextBinaryTreeIteratorVal(crawler->itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(crawler->itr));
	CU_ASSERT_EQUAL(treeSize, getBinaryTreeIteratorAvailable(crawler->itr));
	deleteBinaryTreeBreadthFirstCrawler(crawler);
}
/**
 * All Trees should have already be printed with BreadthSearch
 * This is just example of using cunit to test crawler
 */
static void testBinaryCrawlerIterator_NULL_cunit(void){

	printf("\n\n\n\tTest Crawler with cunit (treeNULL): \n");
	BinaryTreeNode *treeNULL = NULL;
	BinaryTreeBreadthFirstCrawler *crawler = newBinaryTreeBreadthFirstCrawler(treeNULL, breadthSearch);
	//size_t count = 0;
	const char* result="";
	char strbuf[256] = "";

	startBinaryTreeBreadthFirstCrawlerIterative(crawler, strbuf);
	printf("\tBreadthSearch: %s\n",strbuf);
	printf("\tResult: %s\n",result);
	CU_ASSERT_STRING_EQUAL(strbuf,result);
	deleteBinaryTreeBreadthFirstCrawler(crawler);
	int treeSize=binaryTreeSize(treeNULL);
	size_t count=0;
	crawler = newBinaryTreeBreadthFirstCrawler(treeNULL,countNodesInBinaryTree);
	startBinaryTreeBreadthFirstCrawlerIterative(crawler, &count);
	printf("\tCrawler count: %ld \n",count);
	printf("\tTree size: %d \n",treeSize);
	CU_ASSERT_EQUAL(binaryTreeSize(treeNULL), count);

	resetBinaryTreeBreadthFirstCrawler(crawler);
	CU_ASSERT_FALSE(hasNextBinaryTreeIteratorVal(crawler->itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(crawler->itr));
	CU_ASSERT_EQUAL(treeSize, getBinaryTreeIteratorAvailable(crawler->itr));
	deleteBinaryTreeBreadthFirstCrawler(crawler);
}


/**
 * Test all the functions for this application.
 *
 * @return test error code
 */
static int test_all(void) {
	// initialize the CUnit test registry -- only once per application
	CU_initialize_registry();

	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("BinaryTreeIterator Tests", NULL, NULL);
	// add the tests to the suite
	CU_add_test(pSuite, "testBinaryTreeIteratorNULL", testBinaryTreeIteratorNULL);
	CU_add_test(pSuite, "testBinaryTreeIterator0", testBinaryTreeIterator0);
	CU_add_test(pSuite, "testBinaryTreeIterator1", testBinaryTreeIterator1);
	CU_add_test(pSuite, "testBinaryTreeIterator12", testBinaryTreeIterator12);
	CU_add_test(pSuite, "testBinaryTreeIterator2", testBinaryTreeIterator22);
	CU_add_test(pSuite, "testBinaryTreeIterator3", testBinaryTreeIterator3);

	CU_add_test(pSuite,"testBinaryCrawlerIterator",testBinaryCrawlerIterator_tree10_cunit);
	CU_add_test(pSuite,"testBinaryCrawlerIterator",testBinaryCrawlerIterator_NULL_cunit);
	CU_add_test(pSuite,"testBinaryCrawlerIterator",testBinaryCrawlerIterator_tree0_cunit);

	// run all test suites using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	// display information on failures that occurred
	CU_basic_show_failures(CU_get_failure_list());

	// Clean up registry and return status
	CU_cleanup_registry();
	return CU_get_error();
}
/**
 * This function creates trees and uses them to
 * test the recursive and iterative versions of
 * the breadth-first binary tree crawler.
 */
int main(void) {
	BinaryTreeNode *tree0 = makeExprTree0();
	BinaryTreeNode *tree1 = makeExprTree1();
	BinaryTreeNode *tree12 = makeExprTree12();
	BinaryTreeNode *tree22 = makeExprTree22();
	BinaryTreeNode *tree3 = makeExprTree3();


	testCrawlerIterative(tree0);
	testCrawlerIterative(tree1);
	testCrawlerIterative(tree12);
	testCrawlerIterative(tree22);
	testCrawlerIterative(tree3);

	// test all the functions
	CU_ErrorCode code = test_all();

	return (code == CUE_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}
