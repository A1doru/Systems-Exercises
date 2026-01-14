#include "strings.h"
#include <stdlib.h>
#define STRING_MAX_LENGTH 200

struct strings{
    char * string;
    struct strings * next;
};

struct strings * create (const char * S[], unsigned S_len){
    // Check if given empty list
    if(S_len == 0){
        return NULL;
    }
    
    // Create pointer to the head of the linked list, for now is NULL
    struct strings * head = NULL;
    // Pointer to point to previously created strings
    struct strings * prev = NULL;
    
    // Now iterate through all S[] to add elements to the list;
    for(int i = 0; i < S_len; i++){
        
        struct strings * new_node = malloc(sizeof(struct strings));
        new_node->string = malloc(sizeof(char) * (STRING_MAX_LENGTH + 1));
        new_node->next = NULL;
        
        // Copying from array to string. If >= 200, then puttin last element '\0'
        strncpy(new_node->string, S[i], STRING_MAX_LENGTH);
        new_node->string[STRING_MAX_LENGTH] = '\0';
        
        
        // If head is still NULL, then it is first element
        if(head == NULL){
            head = new_node;
        }
        
        // If previous node exists putting new as next for prev
        if(prev != NULL){
            prev->next = new_node;
        }
        // Updating prev for next iteration
        prev = new_node;
    }
    
    return head;
}

void destroy (struct strings * s){
    
    struct strings * temp = NULL;
    while(s != NULL){
        temp = s->next;
        if(s->string != NULL){
            free(s->string);
        }
        free(s);
        s = temp;
    }
}


/*
    Remove all the elements from s that match the given prefix p. For example,
    if the sequence consists of the strings "professional", "programmer", "python", 
    and the prefix p is "pro", then the first two elements must be removed, resulting in a 
    sequence containing the string "python". Return the resulting sequence of strings. 
    Again, if the resulting string is empty, the result is the null pointer.
*/
struct strings * remove_prefix (struct strings * s, const char * p){
    // // First check if input is valid
    if(s == NULL || p == NULL){
        return NULL;
    }
    
    // // Creating pointer for the result list, By default is NULL so empty
    struct strings * res = NULL;
    struct strings * prev = NULL;
    
    struct strings * iterator = s;
    while(iterator != NULL){
        // Getting current string
        const char * str = value(iterator);
        size_t p_len = strlen(p);
        int matching = strncmp(str, p, p_len);
        
        // By default string is matching given prefix
        // int matching = 1;
        // // Compare each character
        // for(int i = 0; i < strlen(p); i++){
        //     // Not match
        //     if(str[i] != p[i]){
        //         matching = 0;
        //         break;
        //     }
        // }
        
        // Adding to the result list logic if element is not matching prefix
        if(matching != 0){
            // Allocating memory for new node
            struct strings * new_node = malloc(sizeof(struct strings));
            new_node->string = malloc(sizeof(char) * (strlen(str) + 1));
            new_node->next = NULL;
            
            strcpy(new_node->string, str);
            new_node->string[strlen(str)] = '\0';
        
            // If res is still NULL, means new_node is a head
            if(res == NULL){
                res = new_node;
            }
        
            // If there was any previous node, the assign current as next for prev
            if(prev != NULL){
                prev->next = new_node;
            }
            prev = new_node;
        }
        
        // Putting new iterator
        iterator = next(iterator);
    }
    
    return res;
}

/*
    Given a pointer to an element of the list, return the string value of that element.
*/
const char * value (struct strings * itr){
    if(itr == NULL){
        return NULL;
    }
    return itr->string;
}

/*
    Given a pointer to an element of the list, return a pointer to the next element in the list. 
    If there are no more elements in the list, the result is the null pointer.
*/
struct strings * next (struct strings * itr){
    if(itr == NULL){
        return NULL;
    }
    return itr->next;
}








