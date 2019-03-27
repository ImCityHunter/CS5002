/*
 * @file linked_list_iterator_main.c
 *
 * This file exercises the singly linked list and singly linked list
 * iterators functions.
 *
 * @since 2018-10-14
 * @author philip gust
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list_iterator.h"


/**
 * Test LinkedListIterator functions
 */
void testLinkedListIterator(void) {
	printf("\nstart testLinkedListIterator\n");

	printf("initial list\n");
	LinkedList *list = newLinkedList(10);
	printLinkedList(list);
	printf("list size: %ld\n", linkedListSize(list));

	// add 5 nodes to the list
	printf("\nAdding 6 values to list\n");
	addLastLinkedListVal(list, "A");
	addLastLinkedListVal(list, "B");
	addLastLinkedListVal(list, "C");
	addLastLinkedListVal(list, "D");
	addLastLinkedListVal(list, "E");
	addLastLinkedListVal(list, "F");
	printLinkedList(list);

	printf("list size: %ld\n", linkedListSize(list));

	printf("\nTraversing list forward with iterator\n");
	LinkedListIterator *itr = newLinkedListIterator(list);
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));
	while (hasNextLinkedListIteratorVal(itr)) {
		const char *val;
		if (getNextLinkedListIteratorVal(itr, &val)) {
			printf("iterator next: \"%s\"\n", val);
		} else {
			printf("iterator next: unavailable\n");
		}
	}
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));

	printf("\nMoving back one from end with iterator\n");
	printf("iterator has prev: %s\n", hasPrevLinkedListIteratorVal(itr) ? "true" : "false");
	const char *val;
	if (getPrevLinkedListIteratorVal(itr, &val)) {
		printf("iterator prev: \"%s\"\n", val);
	} else {
		printf("iterator prev: unavailable\n");
	}
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));

	printf("\nMoving forward one to end with iterator\n");
	if (getNextLinkedListIteratorVal(itr, &val)) {
		printf("iterator next: \"%s\"\n", val);
	} else {
		printf("iterator next: unavailable\n");
	}
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));

//	printf("\nResetting iterator\n");
//	resetLinkedListIterator(itr);
//	printf("iterator has next: %s\n", hasNextLinkedListIteratorVal(itr) ? "true" : "false");
//	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
//	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));


	//move pointer from A to D


	printf("\n------------------------------------------------------\n");
	printf("My Test Functions: \n");
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));
	while (hasPrevLinkedListIteratorVal(itr)) {
		const char *val;
		if (getPrevLinkedListIteratorVal(itr, &val)) {
			printf("iterator next: \"%s\"\n", val);
		} else {
			printf("iterator next: unavailable\n");
		}
	}
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));
	printf("\nResetting iterator\n");
	resetLinkedListIterator(itr);
	printf("iterator has next: %s\n", hasNextLinkedListIteratorVal(itr) ? "true" : "false");
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));
	getNextLinkedListIteratorVal(itr,&val);
	getNextLinkedListIteratorVal(itr,&val);
	getNextLinkedListIteratorVal(itr,&val);
	getNextLinkedListIteratorVal(itr,&val);
	printf("\nMove Pointer in order to test getFirstNode function \n");
	printf("Current Node %s \n",val);
	LinkedNode *testfirst= getFirstLinkedNode(itr->curNode);
	printf("Test Get First Node\n");
	printf("First Node (head): %s\n",testfirst->data);

	printf("Test Get Last Node\n");
	LinkedNode *testlast = 	getLastLinkedNode(itr->curNode);
	printf("Last Node (last): %s\n",testlast->data);

	resetLinkedListIterator(itr);

	printf("\nTest Delete Function \n");

	printLinkedList(list);
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));
	deleteLinkedListValAt(list, 2);
	printLinkedList(list);
	printf("iterator count: %ld\n", getLinkedListIteratorCount(itr));
	printf("iterator avail: %ld\n", getLinkedListIteratorAvailable(itr));

	LinkedNode *previous = getLinkedNodeAt(list->head,2);
	LinkedNode *next = getLinkedNodeAt(list->head,3);
	printf("Check if previous & next nodes of deleted node are connected\n");
	printf("print next node of %s:  %s\n",previous->data,previous->next->data);
	printf("print previous node of %s:  %s\n",next->data,next->prev->data);

	printf("\nPrint List Before Deleted\n");
	printLinkedList(list);
	printf("Delete Index at %ld \n", linkedListSize(list));
	deleteLinkedListValAt(list, linkedListSize(list));
	printLinkedList(list);
	printf("Nothing should change\n");



	printf("\nTrying to move back one from beginning with iterator\n");
	printf("iterator has prev: %s\n", hasPrevLinkedListIteratorVal(itr) ? "true" : "false");
	if (getPrevLinkedListIteratorVal(itr, &val)) {
		printf("iterator prev: \"%s\"\n", val);
	} else {
		printf("iterator prev: unavailable\n");
	}

	printf("\nDeleting iterator and linked list\n");
	deleteLinkedListIterator(itr);
	deleteLinkedList(list);

	printf("end testLinkedListIterator\n");
}

/**
 * Test functions.
 */
int main(void) {
	testLinkedListIterator();

	printf("program exiting\n");
}
