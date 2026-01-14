/**
    iterator:
        - sequence of characters T
        - sequence of separators S



 */


#include "iterator.h"
#include <stdlib.h>
#include <string.h>

struct iterator{
    struct sequence * T;
    struct sequence * S;
    const char * current_pos;
};


struct iterator * create_iterator(){
    struct iterator * i = malloc(sizeof(struct iterator));
    if(i == NULL){
        return NULL;
    }

    i->T = malloc(sizeof(struct sequence));

    char * default_S = ",;";
    i->S = malloc(sizeof(struct sequence));
    i->S->begin = default_S;
    i->S->end = default_S + 1;

    i->current_pos = NULL;

    if(i->S == NULL){
        return NULL;
    }

    return i;
}

void destroy_iterator(struct iterator * i){
    free(i->T);
    free(i->S);
    free(i);
}

int set_text(struct iterator * i, const struct sequence * T){
    if(i == NULL || T == NULL){
        return 0;
    }
    // allocating new memory for the TEXT
    memcpy(i->T, T, sizeof(struct sequence));
    if(i->T == NULL){
        return 0;
    }

    // allocating memory fot the character pointer
    i->current_pos = malloc(sizeof(char *));
    i->current_pos = i->T->begin;

    return 1;
}

int set_separators(struct iterator * i, const struct sequence * S){
    if(i == NULL || S == NULL){
        return 0;
    }

    // removing all previous data
    memcpy(i->S, S, sizeof(struct sequence));
    if(i->S == NULL){
        return 0;
    }

    return 1;
}

// Returns 1 if character is separator, -1 on failure, 0 if is not a separator
int is_separator(struct sequence * S, char c){
    if(S == NULL){
        return -1;
    }

    if(strchr(S->begin, c) != NULL){
        return 1; // is separator
    } else{
        return 0; // not separator
    }
}

int get_next(struct iterator * i, struct sequence * X){
    if(i == NULL || X == NULL){
        return 0;
    }

    if(i->T == NULL || i->S == NULL){
        return 0;
    }

    if(i->current_pos == i->T->end){
        return 0;
    }

    // Find begin for X using current_pos
    for(const char * p = i->current_pos; p < i->T->end; p++){
        if(is_separator(i->S, *p) == 1){
            i->current_pos++;
        } else{
            break;
        }
    }
    if(i->current_pos == i->T->end){
        return 0; // sequence is empty
    }
    X->begin = i->current_pos; // setting beginning

    // Find position of first separator after beginning
    for(const char * p = i->current_pos; p < i->T->end; p++){
        if(is_separator(i->S, *p) == 0){
            i->current_pos++; // if not separator, increase pointer
        } else{
            break;
        }
    }

    X->end = i->current_pos ;

    return 1;
}

