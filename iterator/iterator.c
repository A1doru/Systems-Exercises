#include "iterator.h"
#include <stdlib.h>
#include <string.h>
/**
    iterator:
        - 

 */

/*
    T       is starting adress of the string
    T_end   is end of the string
    S       sequence of separator characters
    pointer is an adress of the start of current iteration
*/
struct iterator{
    char * T;
    char * T_end;
    char * S;
    const char * pointer;
};

/*
    Creates new iterator. By default T is null. S is ",;";
    Pointer is also null;
*/
struct iterator * create_iterator(){
    struct iterator * i = malloc(sizeof(struct iterator));

    if(!i){
        return NULL;
    }

    i->T = NULL;
    i->T_end = i->T;
    i->S = malloc(3); 
    if(!i->S) { 
        free(i); 
        return NULL; 
    }
    strcpy(i->S, ",;");
    i->pointer = i->T;
    
    return i;
}

/*
    Destroys iterator and T if present
*/
void destroy_iterator(struct iterator * i){
    if(i->T != NULL){
        free(i->T);
    }
    free(i->S);
    free(i);
}



/*
    We need to copy the data into T that is between T->begin and T->end
 */
int set_text(struct iterator * i, const struct sequence * T){
    if(i == NULL || T == NULL){
        return 0;
    }

    // First clean previous data in i->T if there is smth
    if(i->T != NULL){
        free(i->T);
    }

    // Now allocate enough memory to store end - begin characters.
    size_t len = T->end - T->begin;
    i->T = malloc(len);
    if(i->T == NULL){
        return 0;
    }

    // Now copy all data from T to i->T
    memcpy(i->T, T->begin, len);

    // Set end of text as first byte + length of string
    i->T_end = i->T + len;

    // Put pointer to the first character of the sequence of characters
    i->pointer = i->T;
    
    return 1;
}

/*
    Also we need to copy all memory between S->begin and S->end to i->S
*/
int set_separators(struct iterator * i, const struct sequence * S){
    // Check if i and S are valid pointers
    if(i == NULL || S == NULL){
        return 0;
    }

    // Now clean old data (since for S we have default data we dont need to check if it is empty):
    free(i->S);

    // Now allocate enough space for new data +1 to put \0:
    size_t len = S->end - S->begin;
    i->S = malloc(len + 1);
    if(i->S == NULL){
        return 0;
    }
    // Copy data 
    memcpy(i->S, S->begin, len);
    i->S[len] = '\0';

    return 1;
}

/*
    Helper function:
        - returns 0 if characters is not separator
        - returns 1 if char is separator
 */
int is_sep(char * S, const char c){
    if(strchr(S, c) != NULL){
        return 1;
    } else{
        return 0;
    }
}

/*
    Here i will iterate through my characters and look if this characters contains 
    in the separator string.
*/
int get_next(struct iterator * i, struct sequence * X){
    // First check if given valid pointers
    if(i == NULL || X == NULL || i->pointer == i->T_end){
        return 0;
    }

    // First loop to find begin of X <==> first non-separator character
    for(i->pointer; i->pointer < i->T_end; i->pointer++){
        if(is_sep(i->S, *i->pointer) == 0){
            X->begin = i->pointer;
            // stop the loop
            break;
        }
    }

    // Check if we already at the end
    if(i->pointer == i->T_end){
        return 0; // No more tokens
    }

    // Second loop from the current pointer position until first separator character
    for(i->pointer; i->pointer < i->T_end; i->pointer++){
        if(is_sep(i->S, *i->pointer) == 1){
            X->end = i->pointer;
            return 1;
        }
    }

    X->end = i->T_end;

    return 1;
}