/*
 * binary_tree_main.c
 * This is a temporary main program with the sample expression tree and
 * two traversal callbacks that I showed in the 2017-03-02 class session.
 * This will allow you to explore how the depth-first tree walker and
 * and a callback interact. This file will be replaced with a full unit
 * test suite for the added functionality and the functions you will be
 * creating.
 *
 * @since 2017-03-02
 * @author Philip Gust
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl_tree.h"

/**
 * Creates the following expression tree:
 *                    +
 *         .----------'----------.
 *         -                     *
 *    .----'----.           .----'----.
 *    9        sqr          /         7
 *           .--'--.     .--'--.
 *                 2     8     4
 */
BinaryTreeNode* makeBinaryExprTree() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "+";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = malloc(sizeof(BinaryTreeNodeData));
	node10Data->strval = "-";
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = malloc(sizeof(BinaryTreeNodeData));
	node11Data->strval = "*";
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);

	// left left level 2
	BinaryTreeNodeData* node20Data = malloc(sizeof(BinaryTreeNodeData));
	node20Data->strval = "9";
	BinaryTreeNode* node20 = newBinaryTreeNode(node20Data);

	// right left level 2
	BinaryTreeNodeData* node21Data = malloc(sizeof(BinaryTreeNodeData));
	node21Data->strval = "sqr";
	BinaryTreeNode* node21 = newBinaryTreeNode(node21Data);

	// left right level 22
	BinaryTreeNodeData* node22Data = malloc(sizeof(BinaryTreeNodeData));
	node22Data->strval = "/";
	BinaryTreeNode* node22 = newBinaryTreeNode(node22Data);

	// right right level 2
	BinaryTreeNodeData* node23Data = malloc(sizeof(BinaryTreeNodeData));
	node23Data->strval = "7";
	BinaryTreeNode* node23 = newBinaryTreeNode(node23Data);


	// right left level 3
	BinaryTreeNodeData* node30Data = malloc(sizeof(BinaryTreeNodeData));
	node30Data->strval = "2";
	BinaryTreeNode* node30 = newBinaryTreeNode(node30Data);

	// left right level 3
	BinaryTreeNodeData* node31Data = malloc(sizeof(BinaryTreeNodeData));
	node31Data->strval = "8";
	BinaryTreeNode* node31 = newBinaryTreeNode(node31Data);

	// right right level 3
	BinaryTreeNodeData* node32Data = malloc(sizeof(BinaryTreeNodeData));
	node32Data->strval = "4";
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
 * Creates the following search tree:
 *                    N
 *         .----------'----------.
 *         F                     U
 *    .----'----.           .----'----.
 *    D         G           P         X
 *           .--'--.     .--'--.
 *                 J     O     R
 */
BinaryTreeNode* makeBinarySearchTree() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addBinarySearchTreeNode((BinaryTreeNode*)NULL, nodeData);


	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "D";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "G";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "P";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "J";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "O";
	addBinarySearchTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "R";
	addBinarySearchTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *                          .----'----.
 *     	                    P         X
 *     	                          .---'---.
 *     	                                   Z
 * The AVL algorithm re-balances it using a left-rotation about U as:
 *                    U
 *         .----------'----------.
 *         N                     X
 *    .----'----..           .---'---.
 *    F         P                    Z
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedOuterRight() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "P";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "Z";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL
 * balanced.
 *                        N
 *             .----------'----------.
 *             F                     U
 *        .----'----.
 *        B         H
 *    .---'---.
 *    A
 *
 * The AVL algorithm re-balances it using a right-rotation about F as:
 *                        F
 *             .----------'----------.
 *             B                     N
 *        .----'----.            .---'---.
 *        A                      H       U
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedOuterLeft() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "H";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "A";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL
 * balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *                          .----'----.
 *     	                    P         X
 *     	                .---'---.
                                R
 *
 * The AVL algorithm re-balances it using a double rotation about U as:
 *                        P
 *             .----------'----------.
 *             N                     U
 *        .----'----.            .---'---.
 *        F                      R       X
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedInnerRightRight() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "P";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "R";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL
 * balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *                          .----'----.
 *     	                    P         X
 *     	                .---'---.
 *                       O
 *
 * The AVL algorithm re-balances it using a double rotation about U as:
 *                        P
 *             .----------'----------.
 *             N                     U
 *        .----'----.            .---'---.
 *        F         O                    X
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedInnerRightLeft() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "P";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "O";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL
 * balanced.
 *                        N
 *             .----------'----------.
 *             F                     U
 *        .----'----.
 *        B         H
 *              .---'---.
 *                      J
 *
 * The AVL algorithm re-balances it using a double-rotation about F as:
 *                        H
 *             .----------'----------.
 *             F                     N
 *        .----'----.            .---'---.
 *        B                      J       U
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedInnerLeftRight() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "H";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "J";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is not AVL
 * balanced.
 *                        N
 *             .----------'----------.
 *             F                     U
 *        .----'----.
 *        B         H
 *              .---'---.
 *              G
 *
 * The AVL algorithm re-balances it using a double-rotation about F as:
 *                        H
 *             .----------'----------.
 *             F                     N
 *        .----'----.            .---'---.
 *        B         G                    U
 *
 */
BinaryTreeNode* makeAvlTree_OverbalancedInnerLeftLeft() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "H";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "G";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is AVL balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *    .----'----.           .----'----.
 *    B                     P         X
 *     	                .---'---.
 *                      O       R
 *
 * After deleting B, the AVL algorithm re-balances it using a double
 * rotation about U as:
 *                        P
 *             .----------'----------.
 *             N                     U
 *        .----'----.            .---'---.
 *        F         O            R       X
 *
 */
BinaryTreeNode* makeAvlTree_BalancedInnerRightLeft() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "P";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "O";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "R";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is AVL balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *    .----'----.           .----'----.
 *    B         J                     X
 *     	    .---'---.
 *          G       L
 *
 * After deleting X, the AVL algorithm re-balances it using a double
 * rotation about J as:
 *                        J
 *             .----------'----------.
 *             F                     N
 *        .----'----.            .---'---.
 *        B         G            L       U
 *
 */
BinaryTreeNode* makeAvlTree_BalancedInnerLeftRight() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "J";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "X";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "G";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "L";
	root = addAvlTreeNode(root, nodeData);

	return root;
}

/**
 * Creates the following binary search tree that is AVL balanced.
 *         F
 *    .----'----.
 *    B         J
 *     	    .---'---.
 *          G
 *
 * After deleting B, the AVL algorithm re-balances it using a double
 * rotation about J as:
 *             G
 *        .----'----.
 *        F         J
 *
 */
BinaryTreeNode* makeAvlTree_BalancedOuterRight() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "B";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "J";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "G";
	root = addAvlTreeNode(root, nodeData);

	return root;
}
/**
 * Creates the following binary search tree that is not AVL balanced.
 *                    N
 *         .----------'----------.
 *         F                     U
 *
 * After deleting F, The AVL algorithm should leave it unchanged as:
 *                    N
 *         .----------'----------.
 *                               U
 *
 */
BinaryTreeNode* makeAvlTree_BalancedHeight1() {
	// root node
	BinaryTreeNodeData* nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "N";
	BinaryTreeNode* root = 	addAvlTreeNode((BinaryTreeNode*)NULL, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "F";
	root = addAvlTreeNode(root, nodeData);

	nodeData = malloc(sizeof(BinaryTreeNodeData));
	nodeData->strval = "U";
	root = addAvlTreeNode(root, nodeData);

	return root;
}


/**
 * Write the binary tree in prefix order to an output string.
 *
 * @param node the root of a binary tree
 * @param outstr the output string
 * @return the number of characters written
 */
int binaryTreeToStr(BinaryTreeNode* node, char* outstr) {
	if (isBinaryTreeNodeLeaf(node)) {
		return sprintf(outstr, "%s ",node->data->strval);
	} else {
		int n = sprintf(outstr, "( %s ",node->data->strval);

		if (node->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
			n+= binaryTreeToStr(node->linkTo[leftLink], outstr+n);
		}
		if (node->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
			n+= binaryTreeToStr(node->linkTo[rightLink], outstr+n);
		}
		n+= sprintf(outstr+n, ") ");
		return n;
	}
}

/**
 * Write the AVL tree in prefix order with weights to an output string.
 *
 * @param node the root of an AVL tree
 * @param outstr the output string
 * @return the number of characters written
 */
int avlTreeToStr(BinaryTreeNode* node, char* outstr) {
	if (isBinaryTreeNodeLeaf(node)) {
		return sprintf(outstr, "%s[%d] ",node->data->strval, node->balanceFactor);
	} else {
		int n = sprintf(outstr, "( %s[%d] ",node->data->strval, node->balanceFactor);

		if (node->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
			n += avlTreeToStr(node->linkTo[leftLink], outstr+n);
		}
		if (node->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
			n += avlTreeToStr(node->linkTo[rightLink], outstr+n);
		}
		n+= sprintf(outstr+n, ") ");
		return n;
	}

	if (isBinaryTreeNodeRoot(node)) {
		printf("\n");
	}
}

/**
 * Test program for binary tree, search tree, and AVL tree operations.
 */
int main(void) {
	char outstr[512];

	// create expression tree
	BinaryTreeNode* exprTree = makeBinaryExprTree();
	strcpy(outstr,"");
	binaryTreeToStr(exprTree, outstr);
	printf("\nPrefix of expression tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( + ( - 9 ( sqr 2 ) ) ( * ( / 8 4 ) 7 ) )\n");

	// create expression tree
	BinaryTreeNode* searchTree = makeBinarySearchTree();
	strcpy(outstr,"");
	binaryTreeToStr(searchTree, outstr);
	printf("\nPrefix of search tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N ( F D ( G J ) ) ( U ( P O R ) X ) )\n");

	BinaryTreeNode* avlTree = makeAvlTree_OverbalancedOuterRight();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of right overbalanced outer right avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( U[0] ( N[0] F[0] P[0] ) ( X[1] Z[0] ) )\n");

	avlTree = makeAvlTree_OverbalancedOuterLeft();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left overbalanced outer left avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( F[0] ( B[-1] A[0] ) ( N[0] H[0] U[0] ) )\n");

	avlTree = makeAvlTree_OverbalancedInnerRightRight();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left overbalanced inner right right avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( P[0] ( N[-1] F[0] ) ( U[0] R[0] X[0] ) )\n");

	avlTree = makeAvlTree_OverbalancedInnerRightLeft();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left overbalanced inner right left avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( P[0] ( N[0] F[0] O[0] ) ( U[1] X[0] ) )\n");

	avlTree = makeAvlTree_OverbalancedInnerLeftLeft();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left overbalanced inner left left avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( H[0] ( F[0] B[0] G[0] ) ( N[1] U[0] ) )\n");

	avlTree = makeAvlTree_OverbalancedInnerLeftRight();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left overbalanced inner left right avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( H[0] ( F[-1] B[0] ) ( N[0] J[0] U[0] ) )\n");

	avlTree = makeAvlTree_BalancedInnerRightLeft();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left balanced inner right left avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N[1] ( F[-1] B[0] ) ( U[-1] ( P[0] O[0] R[0] ) X[0] ) )\n");

	BinaryTreeNodeData treeNodeB = {"B"};
	avlTree = deleteAvlTreeNode(avlTree, &treeNodeB);
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left balanced inner right left avl tree with 'B' removed:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( P[0] ( N[0] F[0] O[0] ) ( U[0] R[0] X[0] ) )\n");

	avlTree = makeAvlTree_BalancedInnerLeftRight();
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of right balanced inner left right avl tree:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N[-1] ( F[1] B[0] ( J[0] G[0] L[0] ) ) ( U[1] X[0] ) )\n");

	BinaryTreeNodeData treeNodeA = {"A"};  // "A" not in tree
	avlTree = deleteAvlTreeNode(avlTree, &treeNodeA);
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left balanced inner left right avl tree with 'A' NOT removed:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N[-1] ( F[1] B[0] ( J[0] G[0] L[0] ) ) ( U[1] X[0] ) )\n");

	BinaryTreeNodeData treeNodeX = {"X"};
	avlTree = deleteAvlTreeNode(avlTree, &treeNodeX);
	strcpy(outstr,"");
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left balanced inner left right avl tree with 'X' removed:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( J[0] ( F[0] B[0] G[0] ) ( N[0] L[0] U[0] ) )\n");

	avlTree = makeAvlTree_BalancedInnerLeftRight();
	avlTree = deleteAvlTreeNode(avlTree, &treeNodeB);
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of left balanced inner left right avl tree with 'B' removed:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N[-1] ( J[-1] ( F[1] G[0] ) L[0] ) ( U[1] X[0] ) )\n");

	BinaryTreeNodeData treeNodeF = {"F"};
	avlTree = makeAvlTree_BalancedHeight1();
	avlTree = deleteAvlTreeNode(avlTree, &treeNodeF);
	avlTreeToStr(avlTree, outstr);
	printf("\nPrefix of right balanced avl tree with 'F' removed:\n");
	printf("result: %s\n", outstr);
	printf("expect: ( N[1] U[0] )\n");

	return EXIT_SUCCESS;
}
