/*
 * @file array_list_main.c
 *
 * Test program for ArrayList and functions for lecture 2
 *
 * @date Oct 22, 2018
 * @author  philip gust
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"


/**
 * Print the input list.
 *
 * @param list
 */
void printList(ArrayList *list){
	printf("Print List: { ");
	for (int i=0;i<list->size;i++) printf("%s ",list->vals[i]);
	printf("}\n");

}

/**
 * Test functions.
 */
int main(void) {
	/*
	 * Create a list with a maxCapacity
	 * Test if list is empty
	 * Expect empty
	 * Test if list is 0
	 * Expect 0
	 */
	size_t maxCap=20;
	printf("Create an array with Capacity of %ld \n",maxCap);
	ArrayList *list = newArrayList(maxCap);
	bool empty = isArrayListEmpty(list);
	printf("\nTest isArrayList Empty. Expect: True \n");
	printf("list empty? %s\n", empty ? "true" : "false");
	size_t size = arrayListSize(list);
	printf("Test arrayListSize with empty array (maxCap10). Expect: 0 \n");
	printf("list size: %ld\n", size);

	/*
	 * Test AddLastArrayListVal by adding 5 elements
	 * Array list is Not Empty
	 * Array size should be 5
	 */
	printf("Test AddLastArrayListVal by adding values \n");
	printf("\nadding 5 values\n");
	addLastArrayListVal(list, "A");
	addLastArrayListVal(list, "B");
	addLastArrayListVal(list, "C");
	addLastArrayListVal(list, "D");
	addLastArrayListVal(list, "E");
	printList(list);
	empty = isArrayListEmpty(list);
	printf("Test isArrayListEmpty. Expect: false \n");
	printf("list empty? %s\n", empty ? "true" : "false");
	size = arrayListSize(list);
	printf("Test arrayListSize. Expect: 5 \n");
	printf("list size: %ld\n", size);
	printf("\n");

	//Test getArrayListAt function
	const char *val;
	bool status = getArrayListValAt(list, 0, &val);
	printf("Test getArrayListValAt. Expect: A \n");
	if (status) printf("list[0]: %s\n", val);
	else printf("cannot access list[0]\n");

	//Test getFirstArrayListVal function
	status = getFirstArrayListVal(list,&val);
	printf("Test getFirstArrayListVal. Expect: A \n");
	if(status) printf("list[0]: %s\n",val);
	else printf("cannot access \n");

	status = getArrayListValAt(list, 4, &val);
	printf("\nTest getArrayListValAt. Expect: E \n");
	if (status) printf("list[4]: %s\n", val);
	else printf("cannot access list[4]\n");

	//Test if element can be switched at given index
	status = setArrayListValAt(list, 4, "Z");
	printf("\nTest setArrayListAt (change index 4). \n");
	if (status) printf("setting list[4]: Z\n");
	else printf("cannot set list[4]\n");


	printf("\n");
	status = getArrayListValAt(list, 4, &val);
	printf("print index 4. Expect: Z \n");
	if (status) printf("list[4]: %s\n", val);
	else printf("cannot access list[4]\n");


	status = getArrayListValAt(list, 5, &val);
	printf("\nTest getArrayListValAt with an out-of-bound index. Expect: no access \n");
	if (status) printf("list[5]: %s\n", val);
	else printf("cannot access list[5]\n");

	//delete an element at index 0 and see if elements are shifted
	//size should decrease by 1
	//list shoud not be empty
	printf("\n");
	status = deleteArrayListValAt(list, 2);
	if (status)
	printf("delete list[2]\n");
	else printf("cannot delete list[2]\n");
	empty = isArrayListEmpty(list);
	printf("list empty? %s\n", empty ? "true" : "false");
	size = arrayListSize(list);
	printf("list size: %ld\n", size);
	printf("Test if all elements move left from index 2\n");
	printList(list);



	/*
	 * add two values at index 2
	 * see if all elements are shifted right
	 * size is expected to increase by 2
	 * list should be not be empty
	 */
	printf("\nTest addArrayListValAt by adding two values at index 2 \n");
	status= addArrayListValAt(list,2,"J");
	if (status) printf("add Val at list[2] \n");
	else printf("cannot access list[2]\n");
	status= getArrayListValAt(list,2,&val);
	printf("Test Val at list[2]. Expect: J\n");
	if (status) printf("Val at list[2]: %s\n",val);
	else printf("cannot access list[2]\n");
	printf("\nTest addArrayListValAt by adding two values at index 2 \n");
	status= addArrayListValAt(list,2,"P");
	if (status) printf("add Val at list[2] \n");
	else printf("cannot access list[2]\n");


	status= getArrayListValAt(list,2,&val);
	printf("Test Val at list[2]. Expect: P\n");
	if (status) printf("Val at list[2]: %s\n",val);
	else printf("cannot access list[2]\n");

	printf("\nTest setLastArrayListVal\n");
	status=getLastArrayListVal(list , &val);
	if(status) printf("Current LastArrayListVal: %s\n",val);
	else printf("cannot access last index\n");
	//this line sometimes has warning for no reason.
	//build and run again. it might be gone. #eclipselife
	status=setLastArrayListVal(list , "Q");
	if(status) printf("Change last index. Expect: Q\n");
	else printf("cannot access last index\n");
	status=getLastArrayListVal(list , &val);
	if(status) printf("Current LastArrayListVal: %s\n",val);
	else printf("cannot access last index\n");

	printf("\nTest if the ArrayList size has increased. Expect: 6\n");
	size=arrayListSize(list);
	printf("list size: %ld\n", size);
	printf("Test if all elements shift right twice from index 2 \n");
	printList(list);

	/*
	 * Be sure that index beyond list size cannot be added
	 */
	printf("\nAdd an element at index 7 while size is 6. Expect: Not Success\n");
	status=addArrayListValAt(list,7,"H");
	if(status) printf("add Val at list[7]\n");
	else printf("Not Success\n");
	printList(list);

	/*
	 * Test addFirstArray
	 */

	printf("\nTest addFirstArrayListVal\n");
	printList(list);
	status= addFirstArrayListVal(list,"K");
	if(status) printf("add Val at index. Expect: K at index 0\n");
	else printf("not success \n");
	printList(list);

	printf("\nTest setFirstArryListVal\n");
	status= setFirstArrayListVal(list,"A");
	if(status) printf("replace index 0. Expect: A at index 0\n");
	else printf("not success\n");
	printList(list);


	/*
	 * check if capacity double every time when it increases
	 * check if capacity stop increasing at maxCap
	 * check if size can equal to capacity, before capacity increases
	 *
	 *
	 */
	printf("\nAdd ArrayList up to %ld elements where maxCap is set at\n",maxCap);
	for(int i=list->size;i<maxCap;i++){
		status=addArrayListValAt(list,i,"F");
		if(status) printf("size: %ld, capacity: %ld, maxCap: %ld\n",list->size,list->capacity,list->maxCapacity);
		else return printf("has reached maxCapacity\n");
	}
	size=arrayListSize(list);
	printf("list size: %ld\n", size);
	printList(list);

	printf("\nAdd an extra element after size has reached maxCap. Expect: not success \n");
	status=addArrayListValAt(list,0,"T");
	if(status) printf("Val at list[0] is added\n");
	else printf("not success. list is at Max Capacity \n");

	printf("\nTest deleAllArrayListVals\n");
	printf("deleting all array list values\n");
	deleteAllArrayListVals(list);
	empty = isArrayListEmpty(list);
	printf("list empty? %s\n", empty ? "true" : "false");
	size = arrayListSize(list);
	printf("list size: %ld\n", size);


	printf("\ndeleting array list\n");
	deleteArrayList(list);
	size=arrayListSize(list);
	printf("size is %ld \n",size);
	printf("cap is %ld \n",list->capacity);
	printf("maxCap is %ld \n",list->maxCapacity);


	printf("program exiting\n");

	return EXIT_SUCCESS;
}
