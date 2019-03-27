/*
 * binary_search_tree_main.c
 *
 * This file provides the unit tests for a binary tree iterator.
 *
 * @since 2017-02-15
 * @author philip gust, HoKang Yu
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "binary_tree.h"
#include "binary_search_tree.h"
#include "binary_tree_iterator.h"



/**
 * Test of depth 2 binary search tree and binary tree iterator
 *                     D
 *           .---------'---------.
 *           B                   F
 *       .---'---.           .---'---.
 *       A       C           E       G
 */
static void testBinarySearchTree0(void) {
    const char* results[] = {"A", "B", "C", "D", "E", "F", "G", NULL};
    const char *data[] = { "D", "B", "F", "A", "C", "E", "G", NULL};
    const char* BTResults[] ={"G","F","E","D","C","B","A",NULL};

    const char* forwardPostOrder [] ={"A","C","B","E","G","F","D",NULL};
    const char* backwardPostOrder[] ={"G","E","F","C","A","B","D",NULL};

    const char* forwardPreOrder [] ={"D","B","A","C","F","E","G",NULL};
    const char* backwardPreOrder [] ={"D","F","G","E","B","C","A",NULL};

    BinaryTreeNode *root = NULL;
    for (int i = 0; data[i] != NULL; i++) {
		// create data and add to tree
    		BinaryTreeNodeData *nodeData = malloc(sizeof(BinaryTreeNodeData));
    		nodeData->strval = data[i];
    		BinaryTreeNode *node = addBinarySearchTreeNode(root, nodeData);
    		CU_ASSERT_PTR_NOT_NULL_FATAL(node);
    		if (root == NULL) {
    			root = node;
    		}
    }
    size_t height = binaryTreeHeight(root);
    CU_ASSERT_EQUAL(height, 2);

    BinaryTreeIterator *itr = newBinaryTreeIterator(root, inOrder,forwardTraversal);
    BinaryTreeNode *node;
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
    		//printf(" %s ",node->data->strval);
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[i]);
    }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, inOrder, backwardTraversal);

    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, BTResults[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, postOrder, forwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, forwardPostOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, postOrder, backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, backwardPostOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, preOrder, forwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, forwardPreOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, preOrder, backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, backwardPreOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);
}

/**
 * Test of depth 3 binary search tree and binary tree iterator
 *             E
 *    .--------'----------.
 *    A                   F
 *    '---.               '---.
 *        C                   G
 *     .--'--.
 *     B     D
 */
static void testBinarySearchTree1(void) {
    const char* results[] = {"A", "B", "C", "D", "E", "F", "G", NULL};
    const char* data[] = { "E", "A", "F", "C", "G", "B",  "D", NULL};
    const char* BTResults[] = {"G", "F", "E", "D", "C", "B", "A", NULL};

    const char* forwardPostOrder [] ={ "B", "D", "C", "A", "G", "F",  "E", NULL};
    const char* backwardPostOrder[] ={ "G", "F", "D", "B", "C", "A",  "E", NULL};

    const char* forwardPreOrder [] ={"E", "A", "C", "B", "D", "F",  "G", NULL};
    const char* backwardPreOrder [] ={"E", "F", "G", "A", "C", "D",  "B", NULL};
    BinaryTreeNode *root = NULL;
    for (int i = 0; data[i] != NULL; i++) {
		// create data and add to tree
    		BinaryTreeNodeData *nodeData = malloc(sizeof(BinaryTreeNodeData));
    		nodeData->strval = data[i];
    		BinaryTreeNode *node = addBinarySearchTreeNode(root, nodeData);
    		CU_ASSERT_PTR_NOT_NULL_FATAL(node);
    		if (root == NULL) {
    			root = node;
    		}
    }
    size_t height = binaryTreeHeight(root);
    CU_ASSERT_EQUAL(height, 3);

    BinaryTreeIterator *itr = newBinaryTreeIterator(root, inOrder,forwardTraversal);
    BinaryTreeNode *node;
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[i]);
    }

    deleteBinaryTreeIterator(itr);
    itr = newBinaryTreeIterator(root, inOrder, backwardTraversal);

    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, BTResults[i]);
        		//printf(" %s,",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, postOrder, forwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, forwardPostOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, postOrder, backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, backwardPostOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, preOrder, forwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, forwardPreOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, preOrder, backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, backwardPreOrder[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);
}

/**
 * Test of depth 6 binary search tree and binary tree iterator
 *   A
 *     B
 *       C
 *         D
 *           E
 *             F
 *               G
 */
static void testBinarySearchTree2(void) {
    const char* results[] = {"A", "B", "C", "D", "E", "F", "G", NULL} ;
    const char *data[] = {"A", "B", "C", "D", "E", "F", "G", NULL};
    const char* BTResults[] = {"G", "F", "E", "D", "C", "B", "A", NULL};
    BinaryTreeNode *root = NULL;
    for (int i = 0; data[i] != NULL; i++) {
    		// create data and add to tree
    		BinaryTreeNodeData *nodeData = malloc(sizeof(BinaryTreeNodeData));
    		nodeData->strval = data[i];
    		BinaryTreeNode *node = addBinarySearchTreeNode(root, nodeData);
    		CU_ASSERT_PTR_NOT_NULL_FATAL(node);
    		if (root == NULL) {
    			root = node;
    		}
    }

    size_t height = binaryTreeHeight(root);
    CU_ASSERT_EQUAL(height, 6);

    BinaryTreeIterator *itr = newBinaryTreeIterator(root, inOrder,forwardTraversal);
    BinaryTreeNode *node;
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[i]);
    }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, inOrder,backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, BTResults[i]);
        }
    deleteBinaryTreeIterator(itr);
}

/**
 * Test of binary search tree and binary tree iterator
 * Adding A to tree twice fails
 */
static void testBinarySearchTree3(void) {
	BinaryTreeNodeData *nodeData0 = malloc(sizeof(BinaryTreeNodeData));
	nodeData0->strval = "A";
	BinaryTreeNode *node0 = addBinarySearchTreeNode(NULL, nodeData0);
	CU_ASSERT_PTR_NOT_NULL_FATAL(node0);

	BinaryTreeNodeData *nodeData1 = malloc(sizeof(BinaryTreeNodeData));
	nodeData1->strval = "A";
	BinaryTreeNode *node1 = addBinarySearchTreeNode(node0, nodeData1);
	CU_ASSERT_PTR_NULL_FATAL(node1);  // cannot add duplicate value
}

/**
 * Test of depth 4 binary search tree and binary tree iterator.
 *                     D
 *           .---------'---------.
 *           B                   F
 *       .---'---.           .---'---.
 *      A1       C           E       G
 *  .---'---.
 *  A0      A3
 *      .---'
 *      A2
 *
 * Deleting B causes tree to become
 *                     D
 *           .---------'---------.
 *           A3                   F
 *       .---'---.           .---'---.
 *      A1       C           E       G
 *  .---'---.
 *  A0      A2
 *
 *  Delete operation should return A1
 */
static void testBinarySearchTree4(void) {
    const char* results0[] = {"A0", "A1", "A2", "A3", "B", "C", "D", "E", "F", "G", NULL};
    const char* results1[] = {"A0", "A1", "A2", "A3", "C", "D", "E", "F", "G", NULL};
    const char *data[] = { "D", "B", "F", "A1", "A3", "A2", "A0", "C", "E", "G", NULL};
    const char* BTResults1[] = { "G", "F", "E", "D", "C", "A3", "A2", "A1", "A0", NULL};
    const char* BTResults2[] = { "G", "F", "E", "D", "C", "A3", "A2", "A1", "A0", NULL};
    BinaryTreeNode *root = NULL;
    for (int i = 0; data[i] != NULL; i++) {
		// create data and add to tree
    		BinaryTreeNodeData *nodeData = malloc(sizeof(BinaryTreeNodeData));
    		nodeData->strval = data[i];
    		BinaryTreeNode *node = addBinarySearchTreeNode(root, nodeData);
    		CU_ASSERT_PTR_NOT_NULL_FATAL(node);
    		if (root == NULL) {
    			root = node;
    		}
    }
    size_t height = binaryTreeHeight(root);
    CU_ASSERT_EQUAL(height, 4);

    BinaryTreeIterator *itr = newBinaryTreeIterator(root, inOrder,forwardTraversal);
    BinaryTreeNode *node;
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results0[i]);
    }
    deleteBinaryTreeIterator(itr);

    // delete node B from tree
    BinaryTreeNodeData nodeBData = {"B"};
    BinaryTreeNode *nodeA1 = deleteBinarySearchTreeNode(root, &nodeBData);
    CU_ASSERT_PTR_NOT_NULL_FATAL(nodeA1);

    // make sure nodeA1 data matches A1
    CU_ASSERT_STRING_EQUAL(nodeA1->data->strval, "A1");

    // make sure height has decreased
    height = binaryTreeHeight(root);
    CU_ASSERT_EQUAL(height, 3);

    // make sure node B is gone from tree
    itr = newBinaryTreeIterator(root, inOrder,forwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results1[i]);
    }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, inOrder,backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, BTResults1[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);

    itr = newBinaryTreeIterator(root, inOrder,backwardTraversal);
    for (int i = 0; getNextBinaryTreeIteratorNode(itr, &node); i++) {
        		CU_ASSERT_STRING_EQUAL(node->data->strval, BTResults2[i]);
        		//printf(" %s ",node->data->strval);
        }
    deleteBinaryTreeIterator(itr);
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
	CU_add_test(pSuite, "testBinarySearchTree0", testBinarySearchTree0);
	CU_add_test(pSuite, "testBinarySearchTree1", testBinarySearchTree1);
	CU_add_test(pSuite, "testBinarySearchTree2", testBinarySearchTree2);
	CU_add_test(pSuite, "testBinarySearchTree3", testBinarySearchTree3);
	CU_add_test(pSuite, "testBinarySearchTree4", testBinarySearchTree4);

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
 * Main program to invoke test functions
 *
 * @return the exit status of the program
 */
int main(void) {

	// test all the functions
	CU_ErrorCode code = test_all();

	return (code == CUE_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}


