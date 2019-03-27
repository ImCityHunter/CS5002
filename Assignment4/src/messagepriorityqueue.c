/*
 * @file messagepriorityqueue.c
 *
 * This file implements the MessagePriorityQueue functions.
 *
 *  @since: October 31, 2018
 *  @author: philip gust, yu2749luca
 */
#include <stdlib.h>
#include "messagepriorityqueue.h"


#include <stdio.h>
/**
 * Create new message priority queue
 *
 * @param maxCapacity the maximum capacity of the queue
 * @return a new MessagePriorityQueue
 */
MessagePriorityQueue* newMPQ(size_t maxCapacity) {
	MessagePriorityQueue* newMPQ = malloc(sizeof(MessagePriorityQueue));
	newMPQ->maxCapacity = maxCapacity;
	newMPQ->msgQueues = calloc (4,sizeof(ArrayDeque*));
	Priority priority;
	for (priority = highest; priority <= lowest; priority++){

		ArrayDeque *deque = newArrayDeque(maxCapacity);
		newMPQ->msgQueues[priority] = deque;
	}

	return newMPQ;
}

/**
 * Deallocate memory for message priority queue.
 *
 * @param queue the MessagePriorityQueue
 */
void deleteMPQ(MessagePriorityQueue* queue) {


	Priority priority;
	for (priority=highest;priority<=lowest;priority++){
		deleteArrayDeque(queue->msgQueues[priority]);
		queue->msgQueues[priority]=NULL;
	}

	free(queue->msgQueues);
	queue->msgQueues = NULL;
	queue->maxCapacity = 0;
}

/**
 * Enque a message with given priority.
 *
 * @paam queue the message priority queue
 * @param message the message to enqueue
 * @param priority the message priority
 */
bool enqueueMessageMPQ(MessagePriorityQueue* queue, const char* message, Priority priority) {


	if(messageSizeMPQ(queue) >= queue->maxCapacity) return false;
	else {
		//other files/functions will increment enqueue size
		return enqueueArrayDequeVal(queue->msgQueues[priority],message);
	}
	return false;
}

/**
 * Dequeue highest priority message from the queue.
 *
 * @param queue the message priority queue
 * @param val the message to return; must be freed
 * @return true if message was returned, false otherwise
 */
bool dequeueMessageMPQ(MessagePriorityQueue* queue, char** val) {
	// your code here
	Priority rank;

	//no need to peek first, because "peek" is already in dequeueArray function
	for(rank=highest;rank<=lowest;rank++){
		if(dequeueArrayDequeVal(queue->msgQueues[rank],val)) return true;
	}

	return false;
}

/**
 * Peek highest priority message from the queue.
 *
 * @param queue the message priority queue
 * @param the message to return
 * @return true if message was returned, false otherwise
 */
bool peekMessageMPQ(MessagePriorityQueue* queue, const char** val) {
	// your code here
	Priority rank;
		for(rank=highest;rank<=lowest;rank++){
			if(peekHeadArrayDequeVal(queue->msgQueues[rank],val)) return true;
		}
	return false;
}

/**
 * Get total number of messages in the priority queue
 *
 * @param queue the MessagePriorityQueue
 * @return total number of messages
 */
size_t messageSizeMPQ(MessagePriorityQueue* queue) {
	Priority rank;
	size_t res=0;
	for(rank=highest;rank<=lowest;rank++){
		res += messageSizeForPriorityMPQ(queue,rank);
	}
	return res;
}

/**
 * Get number of messages with a given priority in the queue.
 *
 * @param queue the MessagePriorityQueue
 * @param priority the message priority
 * @return number of messages for given priority
 */
size_t messageSizeForPriorityMPQ(MessagePriorityQueue* queue, Priority priority) {
	return queue->msgQueues[priority]->list->size;
}

/**
 *
 * Determines whether queue is empty
 *
 * @param queue the MessagePriorityQueue
 * @return true if queue is empty, false otherwise
 */
bool isEmptyMPQ(MessagePriorityQueue* queue) {
	// your code here
	Priority priority;
	for(priority= highest; priority<=lowest;priority++){
		if(!isEmptyForPriorityMPQ(queue,priority)){return false;}
	}
	return true;
	//return messageSizeMPQ(queue) == 0;

}
/**
 * Determines whether queue for given priority is empty
 *
 * @param queue the MessagePriorityQueue
 * @param priority the message priority
 * @return true if queue is empty for priority, false otherwise
 */
bool isEmptyForPriorityMPQ(MessagePriorityQueue* queue, Priority priority) {
	return isArrayDequeEmpty(queue->msgQueues[priority]);
	//return messageSizeForPriorityMPQ(queue,priority)==0;
	//return true;
}


