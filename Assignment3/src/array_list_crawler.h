/*
 * @file array_list_crawler.h
 *
 * This file provides the structure and function definitions for a
 * crawler for a singly linked list.
 *
 * @since 2018-10-29
 * @author philip gust
 */

#ifndef LINKED_LIST_CRAWLER_H_
#define LINKED_LIST_CRAWLER_H_

#include <stdbool.h>
#include "arraylist_iterator.h"

/** Forward declaration for the ArrayListCrawler struct */
struct ArrayListCrawler;

/**
 * ArrayListCrawler callback function type.
 * Returns true to continue crawling, false to stop crawling
 */
typedef bool (*ArrayListCrawlerCallback)(struct ArrayListCrawler *crawler);

/**
 * A crawler for a singly-linked list.
 */
typedef struct ArrayListCrawler{
  /** The ArrayListIterator */
  ArrayListIterator *itr;

  /** The ArrayListCrawler callback */
  ArrayListCrawlerCallback callback;

  /** The ArrayListCrawler callback data */
  void *callbackData;
} ArrayListCrawler;

/**
 * Create and initialize new crawler with the given callback.
 *
 * @param list the ArrayList to crawl
 * @param cb the callback for this crawler
 * @return an crawler for the list
 */
ArrayListCrawler* newArrayListCrawler(ArrayList* theList, ArrayListCrawlerCallback cb);

/**
 * Delete the crawler by freeing its storage.
 *
 * @param crawler the ArrayListCrawler to delete
 */
void deleteArrayListCrawler(ArrayListCrawler* crawler);

/**
 * Start crawling the ArrayList with the specified data
 */
bool startArrayListCrawler(ArrayListCrawler *crawler, void *data);

/**
 * Determines whether this is the first call from the crawler since last reset.
 *
 * @param crawler the ArrayListCrawler
 * @return true if successful, false if not supported
 */
bool isFirstArrayListCrawlerVal(ArrayListCrawler *crawler);

/**
 * Determines whether there will be another call from the crawler
 *
 * @param itr the ArrayListIterator
 * @return true if there is another value, false otherwise
 */
bool hasNextArrayListCrawlerVal(ArrayListCrawler *crawler);

/**
 * Returns the number of values returned so far.
 *
 * @param itr the ArrayListIterator
 * @return the number of values returned so far
 */
size_t getArrayListCrawlerCount(ArrayListCrawler *crawler);

/**
 * Returns the number of values available.
 *
 * @param itr the ArrayListIterator
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getArrayListCrawlerAvailable(ArrayListCrawler *crawler);

/**
 * Resets the linked list crawler to the head of the list.
 *
 * @param crawler the ArrayListCrawler
 * @return true if successful, false if not supported
 */
bool resetArrayListCrawler(ArrayListCrawler *crawler);

/**
 * Gets the crawler callback data.
 *
 * @param crawler the ArrayListCrawler
 * @return the crawler data
 */
void *getArrayListCrawlerCallbackData(ArrayListCrawler *crawler);

/**
 * Sets the crawler callback data. Enables callback function
 * to update shared data across multiple callbacks.
 *
 * @param crawler the ArrayListCrawler
 * @param data the ArrayListCrawler data
 * @return the crawler data
 */
void setArrayListCrawlerCallbackData(ArrayListCrawler *crawler, void *data);

/**
 * Gets current link value in the linked list.
 *
 * @param itr the ArrayListIterator
 * @param val result parameter is pointer to result value location;  cannot be null
 * @return the current linked list value
 */
bool getArrayListCrawlerVal(ArrayListCrawler* crawler, const char **val);

/**
* Gets value in the linked list at the index.
*
* @param itr the ArrayListIterator
* @param index the index
* @param val result parameter is pointer to result value location; cannot be null
* @return true if previous value returned, false if iterator is at end of list
*/
bool getArrayListCrawlerValAt(ArrayListCrawler* crawler, size_t index, const char **val);

/**
* Sets the current linked list value
*
* @param crawler the ArrayListCrawler
* @param val result parameter is pointer to result value location; cannot be null
* @return true if current value was set, false otherwise
*/
bool setArrayListCrawlerVal(ArrayListCrawler* crawler, const char *val);

/**
* Sets the linked list value at the index
*
* @param crawler the ArrayListCrawler
* @param index the index
* @param val result parameter is pointer to result value location; cannot be null
* @return true if current value was set, false otherwise
*/
bool setArrayListCrawlerValAt(ArrayListCrawler* crawler, size_t index, const char *val);

#endif /* ARRAY_LIST_CRAWLER_H_ */
