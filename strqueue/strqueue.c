#include "strqueue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char * QUEUE_MEMORY = NULL;
static size_t QUEUE_SIZE;
static char * QUEUE_POINTER = NULL;

static char RESULT_BUFFER[1024];

void strqueue_use_buffer(char * mem, size_t mem_size){
    QUEUE_MEMORY = mem;
    QUEUE_SIZE = mem_size;
    QUEUE_POINTER = QUEUE_MEMORY;
}

// strqueue_clear initializes the queue, resulting in an empty queue.
void strqueue_clear(){
    QUEUE_POINTER = QUEUE_MEMORY; // reset the pointer to the start of the queue memory
}

// strqueue_enqueue adds a given string to the queue, returning 1 if successful, or 0 in case
// there is no space to fit that string in the queue. Notice that it would be incorrect to return 0
// when enough space is available.
int strqueue_enqueue(const char * s){
    if(QUEUE_MEMORY == NULL || QUEUE_POINTER == NULL) return 0;
    size_t len = strlen(s) + 1; 
    size_t space_used = QUEUE_POINTER - QUEUE_MEMORY;
    size_t space_left = QUEUE_SIZE - space_used;
    if(len >= space_left) return 0; // not enough space

    memcpy(QUEUE_POINTER, s, len);
    QUEUE_POINTER += len;

    return 1;
}

// strqueue_dequeue extracts and returns the first string from the queue, returning that string
// (char pointer) or 0 if the queue is empty. The returned string must be valid only until the
// next call to any one of the functions of the strqueue module.
const char * strqueue_dequeue(){
    if(QUEUE_MEMORY == NULL || QUEUE_POINTER == NULL) return 0;
    if(QUEUE_POINTER == QUEUE_MEMORY) return 0; // is empty
    size_t len = strlen(QUEUE_MEMORY) + 1; // length of the first string
    memcpy(RESULT_BUFFER, QUEUE_MEMORY, len);
    char * next_str = QUEUE_MEMORY + len;
    if(QUEUE_POINTER - next_str > 0){
        memmove(QUEUE_MEMORY, next_str, (size_t)(QUEUE_POINTER - next_str));
    }

    QUEUE_POINTER -= len;

    return RESULT_BUFFER;
}