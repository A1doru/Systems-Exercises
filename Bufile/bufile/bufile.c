#include "bufile.h"
#include <stdlib.h>


typedef struct bufile {
    char * begin;
    char * end;
} BUFILE;

BUFILE * bufopen(char * begin, char * end){
    BUFILE * buf_p = malloc(sizeof(BUFILE));

    if(buf_p){
        buf_p->begin = begin;
        buf_p->end = end;
    }
    return buf_p;
}

void bufclose(BUFILE * buf){
    free(buf);
}

char * bufgets(char *s, int size, BUFILE * buf){
    int i;

    if(buf->begin == buf->end) return NULL;

    for(i = 0; i < size - 1; i++){
        s[i] = *(buf->begin++);
        if(s[i] == '\n' || buf->begin == buf->end){
            s[i+1] = '\0';
            return s;
        }
    }

    s[i] = '\0';
    return s;
}

/**

    Struct: end: next char after last

    1) At most size - 1 charachter i < size
    2) bug->begin < buf->end
    3) or if current == '\n'

    Always store '\0' after last character

    Error if:
    1) Already finsihed, start == end
 */