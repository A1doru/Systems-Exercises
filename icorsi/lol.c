
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STRING_MAX_LENGTH 200

struct strings{
    char * self;
    struct strings * next;
};

struct strings * create (const char * S[], unsigned S_len){
    if(S_len == 0){
        return 0;
    }
    
    struct strings * first = malloc(sizeof(struct strings));
    struct strings * last = malloc(sizeof(struct strings));

    
    for(unsigned i = 0; i < S_len; i++){
        size_t len = strlen(S[i]);
        if(len > STRING_MAX_LENGTH){
            len = STRING_MAX_LENGTH;
        }
        struct strings * new_node = malloc(sizeof(struct strings));
        new_node->self = malloc(len);
    
        
        // Copy string from give array to the self field of new node
        memcpy(new_node->self, S[i], len);
        new_node->next = 0;
        
        // Add first element. First element also last element
        if(first->self == 0){
            first = new_node;
            last = new_node;
        } else{
            last->next = new_node;
            last = new_node;
        }

        new_node = 0;
    }
    
    return first;
}

void destroy (struct strings * s){
    struct strings * to_destroy = 0;
    while(s != 0){
        to_destroy = s;
        free(to_destroy);
        s = s->next;
    }
}

struct strings * remove_prefix (struct strings * s, const char * p){
    return 0;
}


const char * value (struct strings * itr){
    if(!itr){
        return 0;
    }
    
    char * copy = malloc(sizeof(strlen(itr->self)));
    memcpy(copy,itr->self, strlen(itr->self));
    return copy;
}

struct strings * next (struct strings * itr){
    if(!itr){
        return 0;
    }
    
    return itr->next;
}

int main(){
    const char * S[] = { "ciao" };
    struct strings * s = create(S, 1);
    struct strings * itr = s;
    if(itr != NULL) printf("1 - Success\n");
    const char * v = value(itr);
    printf("My value: %s\n", v);
    if(v != S[0]) printf("2 - Success\n");
    if(strcmp(v, S[0]) == 0) printf("3 - Success\n");
    itr = next(itr);
    if(itr == NULL) printf("4 - Success\n");
    destroy(s);
}