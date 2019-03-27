/*
 * @file linked_list_iterator.h
 *
 * This file provides the structure and function definitions for an
 * iterator for a singly array list.
 *
 * @since 2018-10-03
 * @author philip gust
 */

#ifndef ARRAYLIST_ITERATOR_H_
#define ARRAYLIST_ITERATOR_H_

#include <stdbool.h>

#include "array_list.h"

/**
 * An iterator for a singly-array list.
 */
typedef struct {
  ArrayList *theList;
  //LinkedNode *curNode;
  size_t curIndex;
  size_t count;
} ArrayListIterator;

/**
 * Value returned by getArrayListIteratorAvailable if count unavailable
 */
extern const size_t UNAVAILABLE;

/**
 * Create and initialize new iterator.
 *
 * @param theList the ArrayList to iterate
 * @return an iterator for the list
 */
ArrayListIterator* newArrayListIterator(ArrayList* theList);

/**
 * Delete the iterator by freeing its storage.
 *
 * @param itr the ArrayListIterator to delete
 */
void deleteArrayListIterator(ArrayListIterator* itr);

/**
 * Gets next link value in the array list.
 *
 * @param itr the ArrayListIterator
 * @param val result parameter is pointer to result value location;
 *   cannot be null
 * @return true if next value returned, false if iterator is at end of list
 */
bool getNextArrayListIteratorVal(ArrayListIterator* itr, const char **value);

/**
 * Determines whether there is another value in the array list.
 *
 * @param itr the ArrayListIterator
 * @return true if there is another value, false otherwise
 */
bool hasNextArrayListIteratorVal(ArrayListIterator* itr);

/**
 * Gets previous link value in the array list.
 *
 * The previous value is the one prior to the value returned by a
 * call to getNextLinkListVal(). In other words, it is the value
 * returned by the last call to getNextLinkListVal(). The count
 * will be decremented by 1, so that the sum of the count and the
 * available values is the length of list. If the iterator is at
 * the beginning of the list, there is no previous value.
 *
 * @param itr the ArrayListIterator
 * @param val result parameter is pointer to result value location;
 *   cannot be null
 * @return true if previous value returned, false if iterator is at end of list
 */
 bool getPrevArrayListIteratorVal(ArrayListIterator* itr, const char **val);

 /**
  * Determines whether there is a previous value in the array list.
  *
  * The previous value is the one prior to the value returned by a call
  * to getNextLinkListVal(). In other words, it is the value returned
  * by the last call to getNextLinkListVal(). If the iterator is at
  * the beginning of the list, there is no previous value.
  *
  * @param itr the ArrayListIterator
  * @return true if there is a previous node, false otherwise
  */
bool hasPrevArrayListIteratorVal(ArrayListIterator* itr);

/**
 * Resets the array list iterator to the head of the list.
 *
 * @param itr the ArrayListIterator
 * @return true if successful, false if not supported
 */
bool resetArrayListIterator(ArrayListIterator* itr);

/**
 * Returns the number of values returned so far.
 *
 * @param itr the ArrayListIterator
 * @return the number of values returned so far
 */
size_t getArrayListIteratorCount(ArrayListIterator* itr);

/**
 * Returns the number of values available.
 *
 * @param itr the ArrayListIterator
 * @return available number of values or UNAVAILABLE if cannot perform operation.
 */
size_t getArrayListIteratorAvailable(ArrayListIterator* itr);

#endif /* ARRAYLIST_ITERATOR_H_ */
