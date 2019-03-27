/*
 * @file array_list.c
 *
 * Implementation for ArrayList functions for lecture 2
 *
 * @date Oct 24, 2017
 * @author philip gust
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

/**
 * Create an array list with a fixed capacity.
 *
 * @param capacity capacity of the ArrayList.
 * @return the allocated array list
 */
ArrayList *newArrayList(size_t maxCapacity) {
	ArrayList *list = malloc(sizeof(ArrayList));
	list->size = 0;

	list->capacity = 2;
	list->maxCapacity = maxCapacity;

	//how come this does not work
	//list->vals = malloc(list->capacity * sizeof(char*));
	list->vals=calloc(list->capacity,sizeof(char*));

	return list;
}

/**
 * Add value to list at index. Cannot add NULL string to the list.
 * @param list the ArrayList
 * @param the index for the new value
 * @param val the value to insert; value will be copied to store,
 *     and cannot be null
 * @return false if index out of bounds or exceeds max capacity
 */
bool addArrayListValAt(ArrayList *list, size_t index, const char *val) {
	// cannot add NULL to list
	if (val == NULL) {
		//print error messages to ensure this code should not be run
		printf("error: val is Null \n");
		return false;
	}

	//report error if size=capacity=max capacity
	if(list->size==list->capacity&&list->capacity==list->maxCapacity){
		//print error messages
//		printf("error: list size has reached the max capacity \n");
//		printf("\tsize is %ld\n",list->size);
//		printf("\tcapacity is %ld\n",list->capacity);
//		printf("\tmaxCapacity is %ld\n",list->maxCapacity);
		return false;
	}

	//expand capacity before array is added, if needed
	if(list->size+1>list->capacity){
		list->capacity *=2;

		list->vals=realloc(list->vals,list->capacity * sizeof(char*));

	}
	//if capacity > max, set capacity = max
	if(list->capacity>list->maxCapacity) {
		list->capacity=list->maxCapacity;
		//list->vals=malloc(list->capacity*sizeof(char*));
		list->vals=realloc(list->vals,list->capacity * sizeof(char*));
	}




	//{0,1,2,3} size 4. new index cannot be 5, must be 4 over under
	if (index > list->size) {
		//print error messages
		printf("\terror: input index is beyond the current list size \n");
		return false;
	}
	else if(index==list->size){
		//printf("element is added to last index \n");
		list->size+=1;
		//add element to the index;
		list->vals[index]=strdup(val);
		return true;
		//return setArrayListValAt(list, index, val);
	}
	else if(index<list->size&&index>=0){

		list->size+=1;
		for(int i=list->size-1;i>index;i--){

			list->vals[i]=strdup(list->vals[i-1]);
		}
		list->vals[index]=strdup(val);
		return true;
	}

	//add this print function to ensure this code should never be read
	printf("error: function does not catch all exception! \n");
	//my function should catch all possible input; if not, return false
	return false;
}

/**
 * Add value to start of list. Cannot add NULL string to the list.
 * @param list the ArrayList
 * @param val the value to insert; value will be copied to store,
 *     and cannot be null
 * @return false if index out of bounds or exceeds max capacity
 */
bool addFirstArrayListVal(ArrayList *list, const char *val) {
	 return addArrayListValAt(list, 0, val);
 }

/**
 * Add value to end of list. Cannot add NULL string to the list.
 * @param list the ArrayList
 * @param val the value to insert; value will be copied to store,
 *     and cannot be null
 * @return false if index out of bounds or exceeds max capacity
 */
bool addLastArrayListVal(ArrayList *list, const char *val) {
	 return addArrayListValAt(list, list->size, val);
 }

/**
 * Get value at index.
 * @param list the ArrayList
 * @param the index for the new value
 * @param val result parameter is pointer to result value location;
 *   cannot be null
 * @return false if index out of bounds
 */
bool getArrayListValAt(ArrayList *list, size_t index, const char **val) {
	if (index < list->size) {
		*val = list->vals[index];
		return true;
	}
	return false;
}

/**
 * Get value at first index.
 * @param list the LinkedList
 * @param the index for the new value
 * @param val result parameter is pointer to result value location;
 *   cannot be null
 * @return false if list is empty
 */
bool getFirstArrayListVal(ArrayList *list, const char **val) {
	return getArrayListValAt(list, 0, val);
}

/**
 * Get value at last index.
 * @param list the LinkedList
 * @param the index for the new value
 * @param val result parameter is pointer to result value location;
 *   cannot be null
 * @return false if list is empty
 */
bool getLastArrayListVal(ArrayList *list, const char **val) {
	if (list->size == 0) {
		return NULL;
	}
	return getArrayListValAt(list, list->size-1, val);
}


/**
 * Set value at index.
 * @param list the ArrayList
 * @param the index for the new value
 * @param val the value to set; cannot be null
 * @return false if index out of bounds or value is null
 */
bool setArrayListValAt(ArrayList *list, size_t index, const char *val) {

	// cannot add NULL to list
	if (val == NULL) {
		return false;
	}
	if (index < list->size) {
		free(list->vals[index]);
		list->vals[index] = strdup(val);
		return true;
	}
	return false;
}

/**
 * Set value at first index.
 * @param list the LinkedList
 * @param the index for the new value
 * @param val the value to set; cannot be null
 * @return false if list is empty
 */
bool setFirstArrayListVal(ArrayList *list, const char *val) {
	return setArrayListValAt(list, 0, val);
}

/**
 * Set value at last index.
 * @param list the LinkedList
 * @param the index for the new value
 * @param val value to setresult value location;
 *   cannot be null
 * @return false if list is empty
 */
bool setLastArrayListVal(ArrayList *list, const char *val) {
	if (list->size == 0) {
		return false;
	}
	return setArrayListValAt(list, list->size-1, val);
}

/**
 * Returns number of items in the array list.
 * @param list the array list
 * @return the number of items in the array list.
 */
size_t arrayListSize(ArrayList *list) {
    return list->size;
}

/**
 * Determines whether array list is empty.
 * @param list the array list
 * @return true if array list is empty, flase otherwise
 */
bool isArrayListEmpty(ArrayList *list) {
	return list->size == 0;
}

/**
 * Delete the array list value at the specified index.
 * @param list the array list
 * @param index the index
 * @return if index out of bounds
 */
bool deleteArrayListValAt(ArrayList *list, size_t index) {
	if (index >= list->size) {
		return false;
	}

	// free string before overwriting location
	free(list->vals[index]);

	// move elements down
	list->size--;
	for (int i = index; i < list->size; i++) {
		// move string down
		list->vals[i] = list->vals[i+1];
	}



	return true;
}

/**
 * Delete the first array list value.
 * @param list the array list
 * @return if list is empty
 */
bool deleteFirstArrayListVal(ArrayList *list) {
	return deleteArrayListValAt(list, 0);
}

/**
 * Delete the last array list value.
 * @param list the array list
 * @return if list is empty
 */
bool deleteLastArrayListVal(ArrayList *list) {
	if (list->size > 0) {
		return deleteArrayListValAt(list, list->size-1);
	}
	return false;
}


/**
 * Deletes all array list values.
 * @param list the array list
 */
void deleteAllArrayListVals(ArrayList *list) {
	for (int i = 0; i < list->size; i++) {
		free(list->vals[i]);
		list->vals[i] = NULL;
	}
	list->size = 0;
}

/**
 * Delete the array list. Frees copies of all strings,
 * then the array list, and finally the list itself.
 * Strongly recommend resetting all struct fields to
 * default {NULL, 0, 0} before freeing struct in case
 * this function is called twice with same array list
 *
 * @param list the array list
 */
void deleteArrayList(ArrayList *list) {
	// free the strings in the array
	deleteAllArrayListVals(list);

	// free the list array
	free(list->vals);

	// set fields to safe values
	list->vals = NULL;
	list->capacity = 0;
	list->size = 0;

	//delete maxCapacity
	list->maxCapacity=0;
	// free the list itself
	free(list);
}
