/**
 * @file array_list_main.c
 *
 * Test program for ArrayList and functions.
 *
 * @date Oct 22, 2018
 * @author philip gust
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <inttypes.h>

#include "arraylist_iterator.h"
#include "array_list_crawler.h"

/**
 * Test ArrayListIterator functions
 */
void testArrayListIterator(void) {
	printf("\nstart testArrayListIterator\n");

	printf("initial list\n");
	ArrayList *list = newArrayList(5);
	//printArrayList(list);
	//printf("list size: %ld\n", linkedListSize(list));

	// add 5 nodes to the list
	printf("\nAdding 5 values to list\n");
	addLastArrayListVal(list, "A");
	addLastArrayListVal(list, "B");
	addLastArrayListVal(list, "C");
	addLastArrayListVal(list, "D");
	addLastArrayListVal(list, "E");
	printArrayList(list);

	printf("list size: %ld\n", arrayListSize(list));
	printf("\nTraversing list forward with iterator\n");
	ArrayListIterator *itr = newArrayListIterator(list);
	printf("iterator count: %ld\n", getArrayListIteratorCount(itr));
	printf("iterator avail: %ld\n", getArrayListIteratorAvailable(itr));
	while (hasNextArrayListIteratorVal(itr)) {
		const char *val;
		if (getNextArrayListIteratorVal(itr, &val)) {
			printf("iterator next: \"%s\"\n", val);
		} else {
			printf("iterator next: unavailable\n");
		}
	}
	printf("iterator count: %ld\n", getArrayListIteratorCount(itr));
	printf("iterator avail: %ld\n", getArrayListIteratorAvailable(itr));

	printf("\nMoving back one from end with iterator\n");
	printf("iterator has prev: %s\n", hasPrevArrayListIteratorVal(itr) ? "true" : "false");
	const char *val;
	if (getPrevArrayListIteratorVal(itr, &val)) {
		printf("iterator prev: \"%s\"\n", val);
	} else {
		printf("iterator prev: unavailable\n");
	}
	printf("iterator count: %ld\n", getArrayListIteratorCount(itr));
	printf("iterator avail: %ld\n", getArrayListIteratorAvailable(itr));

	printf("\nMoving forward one to end with iterator\n");
	if (getNextArrayListIteratorVal(itr, &val)) {
		printf("iterator next: \"%s\"\n", val);
	} else {
		printf("iterator next: unavailable\n");
	}
	printf("iterator count: %ld\n", getArrayListIteratorCount(itr));
	printf("iterator avail: %ld\n", getArrayListIteratorAvailable(itr));

	printf("\nResetting iterator\n");
	resetArrayListIterator(itr);
	printf("iterator has next: %s\n", hasNextArrayListIteratorVal(itr) ? "true" : "false");
	printf("iterator count: %ld\n", getArrayListIteratorCount(itr));
	printf("iterator avail: %ld\n", getArrayListIteratorAvailable(itr));

	printf("\nTrying to move back one from beginning with iterator\n");
	printf("iterator has prev: %s\n", hasPrevArrayListIteratorVal(itr) ? "true" : "false");
	if (getPrevArrayListIteratorVal(itr, &val)) {
		printf("iterator prev: \"%s\"\n", val);
	} else {
		printf("iterator prev: unavailable\n");
	}

	printf("\nDeleting iterator and array list\n");
	deleteArrayListIterator(itr);
	deleteArrayList(list);

	printf("end testArrayListIterator\n");
}

/**
 * Print "visited" for each value in the list
 * @param crawler the crawler
 * @return true to continue crawling
 */
bool visitedCallback(ArrayListCrawler *crawler) {
	printf("visited\n");
	return true;
}

/**
 * Print the list values as a comma-separated list in parens.
 * @param crawler the crawler
 * @return true to continue crawling
 */
bool printListCallback(ArrayListCrawler *crawler) {
	// print start of list
	if (isFirstArrayListCrawlerVal(crawler)) {
		printf("( ");
	}
	// print current value
	const char* val;
	getArrayListCrawlerVal(crawler, &val);
	printf("\"%s\"", val);

	// print list item separator or end of list
	if (hasNextArrayListCrawlerVal(crawler)) {
		printf(", ");
	} else {
		printf(" )\n");
	}
	return true;
}

/**
 * Finds the largest string in the list
 * @param crawler the crawler
 * @param true to continue crawling
 */
bool getMaxValCallback(ArrayListCrawler *crawler) {
	char *maxVal = getArrayListCrawlerCallbackData(crawler);
	const char *curVal;
	getArrayListCrawlerVal(crawler, &curVal);
	// first value or larger value
	if (maxVal == NULL || strcmp(curVal, maxVal) > 0) {
		// temporarily cast away const setting void*
		setArrayListCrawlerCallbackData(crawler, (void*)curVal);
	}
	return true;
}

/**
 * Computes the aggregate length of the strings in the list
 * @param crawler the crawler
 * @param true to continue crawling
 */
bool getStrLenCallback(ArrayListCrawler *crawler) {
	size_t *len = getArrayListCrawlerCallbackData(crawler);
	const char *curVal;
	getArrayListCrawlerVal(crawler, &curVal);
	*len += strlen(curVal);
	return true;
}

/**
 * Finds the a string in the list
 * @param crawler the crawler
 * @param true to continue crawling
 */
bool findStrCallback(ArrayListCrawler *crawler) {
	char *targetVal = getArrayListCrawlerCallbackData(crawler);
	const char *curVal;
	getArrayListCrawlerVal(crawler, &curVal);
	bool found = (strcmp(targetVal, curVal) == 0);
	return (!found);  // continue if not found
}

/**
 * Transliterates characters in list strings.
 * @param crawler the crawler
 * @param true to continue crawling
 */
bool translitCallback(ArrayListCrawler *crawler) {
	const char **xlit = getArrayListCrawlerCallbackData(crawler);
	const char *fromChars = xlit[0];  // from transliteration chars
	const char *toChars = xlit[1];      // to transliteration chars

	// current string to transliterate
	const char *fromStr;
	getArrayListCrawlerVal(crawler, &fromStr);

	// transliterate curVal chars found in fromChars to ones in toChars
	size_t len = strlen(fromStr);
	char toStr[len+1];	// transliterated string
	for (int i = 0; i < len; i++) {
		const char *p = strchr(fromChars, fromStr[i]);
		toStr[i] = (p == NULL) ? fromStr[i] : toChars[p-fromChars];
	}
	toStr[len] = '\0';

	setArrayListCrawlerVal(crawler, toStr);  // function allocates copy of local string
	return true;
}

/**
 * This function tests array list crawler.
 */
void testArrayListCrawler() {
	printf("\nstart testArrayListCrawler\n");

	printf("Initial array list\n");
	ArrayList *list = newArrayList(SIZE_MAX);
	printArrayList(list);
	printf("list size: %lu\n", arrayListSize(list));

	// add 5 nodes to the list
	printf("\nAdding 5 values to list\n");
	addLastArrayListVal(list, "A");
	addLastArrayListVal(list, "B");
	addLastArrayListVal(list, "C");
	addLastArrayListVal(list, "B");
	addLastArrayListVal(list, "A");
	printArrayList(list);

	printf("list size: %lu\n", arrayListSize(list));

	printf("\ncrawler with visitedCallback\n");
	ArrayListCrawler *crawler = newArrayListCrawler(list, visitedCallback);
	printf("iterator count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("iterator avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	const char *val;
	if (getArrayListCrawlerVal(crawler, &val)) {
		printf("error: got crawler val \"%s\" before crawler started\n", val);
	} else {
		printf("crawler val not available before crawler started\n");
	}
	bool result = startArrayListCrawler(crawler, NULL); //what does original startArrayListCrawler do in call back function?
	printf("crawler returned: %s\n", result ? "true" : "false");
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	deleteArrayListCrawler(crawler);

	// use callback to print list of strings in list
	printf("\ncrawler with printListCallback\n");
	crawler = newArrayListCrawler(list, printListCallback);
	result = startArrayListCrawler(crawler, NULL);
	printf("crawler returned: %s\n", result ? "true" : "false");
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	deleteArrayListCrawler(crawler);

	// use callback to get the maximum string in list
	printf("\ncrawler with getMaxValCallback\n");
	crawler = newArrayListCrawler(list, getMaxValCallback); //getMaxValCallBack = cb function
	result = startArrayListCrawler(crawler, NULL);
	printf("crawler returned: %s\n", result ? "true" : "false");
	const char *maxVal = getArrayListCrawlerCallbackData(crawler);
	printf("callback found max value \"%s\"\n", maxVal);
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	deleteArrayListCrawler(crawler);

	// use callback to get the aggregate length of strings in list
	printf("\ncrawler with getStrLenCallback\n");
	crawler = newArrayListCrawler(list, getStrLenCallback);
	size_t count = 0;
	result = startArrayListCrawler(crawler, &count);
	printf("crawler returned: %s\n", result ? "true" : "false");
	printf("length of list strings: %lu\n", count);
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	deleteArrayListCrawler(crawler);

	// use callback to find string in list
	printf("\ncrawler with findStrCallback\n");
	crawler = newArrayListCrawler(list, findStrCallback);
	size_t found = 0;
	const char *lookingFor = "B";
	for ( ; startArrayListCrawler(crawler, (void*)lookingFor) == false; found++) {
		size_t foundAt = getArrayListCrawlerCount(crawler)-1;
		printf("index of \"%s\" is: %lu\n", lookingFor, foundAt);
	}
	printf("found %lu occurrences of \"%s\"\n", found, lookingFor);
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));
	deleteArrayListCrawler(crawler);

	// use callback to transliterate characters in list strings
	printf("\ncrawler with translitCallback\n");
	crawler = newArrayListCrawler(list, translitCallback);
	const char *toLowerCase[2] = {
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			"abcdefghijklmnopqrstuvwxyz"
	};
	result = startArrayListCrawler(crawler, toLowerCase);
	printf("crawler returned: %s\n", result ? "true" : "false");
	printArrayList(list);
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));

	printf("\ncrawler with translitCallback\n");
	const char *toUpperCase[2] = {
			"abcdefghijklmnopqrstuvwxyz",
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	};
	// must reset crawler to start at beginning of list
	resetArrayListCrawler(crawler);
	result = startArrayListCrawler(crawler, toUpperCase);
	printf("crawler returned: %s\n", result ? "true" : "false");
	printArrayList(list);
	printf("crawler count: %lu\n", getArrayListCrawlerCount(crawler));
	printf("crawler avail: %lu\n", getArrayListCrawlerAvailable(crawler));

	deleteArrayListCrawler(crawler);

	printf("end testArrayListCrawler\n");
}

/**
 * Test functions.
 */
int main(void) {
	testArrayListIterator();
	testArrayListCrawler();
	printf("program exiting\n");
}
