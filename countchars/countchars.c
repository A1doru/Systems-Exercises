#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define MAX_LENGTH 4096

int main(int argc, char * argv[]){
    if(argc == 1){
        printf("No target characters specified.\n");
        return 1;
    }

    const unsigned char * target = (const unsigned char *)argv[1];

    int i = 2;
    while(i < argc){
        char * filename = argv[i];
        FILE * f = fopen(filename, "r");
        if(f == NULL){
            printf("Error reading file %s\n", filename);
            i++;
            continue;
        }
        if(ferror(f) != 0) continue;
        printf("%s", filename);
        int j = 0;
        while(target[j] != '\0'){
            int counter = 0;
            unsigned char * buf = malloc(MAX_LENGTH);
            if(buf == NULL) return 1;
            while(fgets(buf, MAX_LENGTH,f) != NULL){
                size_t line_len = strlen(buf);
                // printf("LINE LEN IS: %d\n", line_len);
                unsigned char * buf_end = buf + line_len - 1;
                unsigned char * occ = buf;
                unsigned char * ptr = (const unsigned char *)buf;
                while(1){
                    occ = memchr(ptr, target[j], buf_end - ptr + 1);
                    if(occ == NULL){
                        break;
                    }
                    ++counter;
                    ptr = occ + 1;
                }
            }
            free(buf);
            rewind(f);
            printf(" %c:%d", target[j], counter);
            j++;
        }
        putchar('\n');
        ++i;
    }
}