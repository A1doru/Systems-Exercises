#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define LINE_LEN 1000
#define OFFSET 128 // to get index of array is code_id - OFFSET

char * words[256-128]; // 256 since we need +1

int read_code(char * line);

int main(int argc, char * argv[]){
    int only_w = 0;
    char codes[4000];
    if(fgets(codes, 4000, (stdin)) == NULL) return EXIT_SUCCESS;
    if((unsigned char)codes[0] < 128){
        only_w = 1;
        printf("%s", codes);
    } else{
        int res = read_code(codes);
        if(res == 0){
            printf("Error");
            return EXIT_FAILURE;
        }
    }
    char buf[LINE_LEN + 1]; // +1 for \0
    while(fgets(buf, LINE_LEN, (stdin)) != NULL){
        if(strlen(buf) > LINE_LEN) {
            printf("Line is too long");
            return EXIT_FAILURE;
        }
        if(only_w == 1){
            printf("%s", buf);
        } else{
            int i = 0;
            while(buf[i] != '\0'){
                if((unsigned char)buf[i] < 128){
                    putchar(buf[i]);
                } else{
                    if(words[(unsigned char)buf[i] - OFFSET] == NULL){
                        return EXIT_FAILURE;
                    }
                    printf("%s", words[(unsigned char)buf[i] - OFFSET]);
                }
                i += 1;
            }
        }
    }

    return EXIT_SUCCESS;
}

// 0 on failure, 1 on success
int read_code(char * line){
    int i = 0;
    while(line[i] != '\n'){
        if((unsigned char)line[i] >= 128){
            size_t code_len = 16;
            int code_index = (unsigned char)line[i] - OFFSET;
            if(words[code_index] != NULL) return 0;
            words[code_index] = malloc(sizeof(char) * code_len);
            if(words[code_index] == NULL) return 0;
            int cur_index = 0;
            i += 1;
            while(isalpha((unsigned char)line[i]) == 1){
                words[code_index][cur_index] = line[i];
                ++cur_index;
                ++i;
                if(cur_index + 1 >= code_len){
                    code_len *= 2;
                    words[code_index] = realloc(words[code_index], code_len);
                }
                if((unsigned char)line[i] < 0) return 0;
            }
            words[code_index][cur_index] = '\0';
        } else{
            return 0;
        }
    }

    return 1;
}