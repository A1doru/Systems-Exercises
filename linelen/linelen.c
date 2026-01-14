/*
    + 1) Output is LINE which length is min<len<max
    + 2) LINE is max sequence of chars(bytes) terminated with '\n'
    + 3) Parameters min and max are passed as optional command line arguments.
    + 4) By default min = 0, max = inf. 
    + 5) At most 60 characters.
    + 6) If more than 60, then ... in the end.
*/


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000

int main(int argc, char *argv[]){

    unsigned int min = 0;
    unsigned int max = UINT_MAX;

    if(argc == 2) min = atoi(argv[1]);
    else if(argc == 3){
        min =  atoi(argv[1]);
        max = atoi(argv[2]);
    }

    char s[MAX_LINE_LENGTH];
    
    while(fgets(s, sizeof(s), stdin) != NULL){
        size_t length = strlen(s) - 1;
        if(s[length] == '\n'){
            if(length >= min && length <= max){
                if(length > 60){
                    printf("%.60s...\n", s);
                } else{
                    printf("%s", s);
                }
            }
        }
    }

    return 0;
}