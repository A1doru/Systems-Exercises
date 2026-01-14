// Write a module in a source file called strstack.c that implements a stack of
// strings (zero-terminated arrays of characters) as defined by the operations declared in the following
// header file strstack.h:
#include "strstack.h"
#include <string.h>

// The strstack module must not allocate memory to hold the stack of strings. Instead, that memory
// is provided by the application through the strstack_use_buffer function. The module may of course
// use other internal meta-data variables.

char * STACK_ADDRESS;
size_t STACK_SIZE;
char * STACK_POINTER;
char * LAST_STRING = NULL;

void strstack_use_buffer(char * mem, size_t mem_size){
    STACK_ADDRESS = mem;
    STACK_SIZE = mem_size;
    STACK_POINTER = mem;
    LAST_STRING = NULL;
}

// strstack_clear initializes the stack, resulting in an empty stack.
void strstack_clear(){
    STACK_POINTER = STACK_ADDRESS;
}

// strstack_push pushes a given string on the stack, returning 1 if successful, or 0 in case of
// overflow.
int strstack_push(const char * s){
    size_t len = strlen(s);
    
    // Check if: string + null terminator + space to store the old LAST_STRING pointer fits
    // We store the old LAST_STRING pointer so we can "move back" during pop
    size_t space_needed = len + 1 + sizeof(char *);
    
    if ((STACK_POINTER + space_needed) > (STACK_ADDRESS + STACK_SIZE)) {
        return 0; // Overflow
    }

    char * start_of_new_entry = STACK_POINTER;

    // 1. Copy the string (including null terminator)
    strcpy(STACK_POINTER, s);
    STACK_POINTER += len + 1;

    // 2. Save the pointer to the PREVIOUS string so pop can find it
    // We treat the current STACK_POINTER as a place to hold a char*
    *((char **)STACK_POINTER) = LAST_STRING;
    
    // 3. Update LAST_STRING to this new string's start
    LAST_STRING = start_of_new_entry;
    
    // 4. Move pointer past the stored address
    STACK_POINTER += sizeof(char *);
    
    return 1;
}

// strstack_pop pops a string from the stack, returning that string or 0 if the stack is empty.
// The returned string must be valid only until the next call to any one of the functions of the
// strstack module.
const char * strstack_pop(){
    if (LAST_STRING == NULL) return NULL; // Stack empty

    const char * current_str = LAST_STRING;

    // Find where we stored the "previous" LAST_STRING pointer
    // It is located right after the null terminator of the current string
    char * metadata_loc = (char *)current_str + strlen(current_str) + 1;
    
    // Move LAST_STRING back to the previous one
    LAST_STRING = *((char **)metadata_loc);
    
    // Move the STACK_POINTER back to where this string started
    STACK_POINTER = (char *)current_str;

    return current_str;
}