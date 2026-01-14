#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define OFFSET 128

struct wg{
    char * content;
    int count;
    size_t length;
    int gain;
};

size_t current_size = 0;
size_t size = 8;
struct wg ** words;
struct wg ** codes;

void resize_words();
struct wg * word_met(char * word, size_t len);
void calc_gain();
void sort_codes();
void print_codes();
void print_encoding();
int is_code(char * word, size_t len);

void print_content(){
    printf("\n\nWORDS ARE:\n");
    for(int i = 0; i < current_size; i++){
        printf("%s -> %d\n", words[i]->content, words[i]->count);
    }
}

void print_codes_debug(){
    printf("\n\nCODEs ARE:\n");
    for(int i = 0; i < current_size; i++){
        printf("%s -> %d -> %d\n", codes[i]->content, codes[i]->gain, codes[i]->count);
    }
}

int main(int argc, char * argv[]){
    words = malloc(sizeof(struct wg *) * size);
    char c;
    char file[2000000];
    int i = 0;
    // Loop to copy content of the file
    while((c = getchar()) != EOF){
        file[i] = c;
        ++i;
    }
    int j = 0;
    while(file[j] != '\0'){
        if(isalpha(file[j]) == 1 && file[j] != '\n'){
            // here save words and calculate gain
            char * start = &file[j];
            while(isalpha(file[j]) == 1){
                ++j;
            }
            char * end = &file[j];
            size_t len = end - start;
            char * word = malloc(sizeof(char) * len);
            memcpy(word, start, len);
            struct wg * cur = word_met(word, len);
            if(cur != NULL){
                cur->count = cur->count + 1;
            } 
            else{
                words[current_size] = malloc(sizeof(struct wg));
                if(words[current_size] == NULL) return EXIT_FAILURE; // error
                words[current_size]->content = malloc(sizeof(char) * len);
                if(words[current_size]->content == NULL) return EXIT_FAILURE; // error
                memcpy(words[current_size]->content, word, len);
                words[current_size]->count = 1;
                words[current_size]->length = len;
                ++current_size;
                if(current_size >= size){
                    resize_words();
                }
            }
            free(word);
        } else{
            ++j; // if character is not alpha then just continue reading content
        }
    }
    codes = malloc(sizeof(struct wg *) * current_size);
    calc_gain();
    sort_codes();
    print_codes();
    
    if(current_size != 0) putchar('\n');
    j = 0;
    while(file[j] != '\0'){
        if(isalpha(file[j]) == 1 && file[j] != '\n'){
            // here save words and calculate gain
            char * start = &file[j];
            while(isalpha(file[j]) == 1){
                ++j;
            }
            char * end = &file[j];
            size_t len = end - start;
            char * word = malloc(sizeof(char) * len);
            memcpy(word, start, len);
            int cur = is_code(word, len);
            if(cur != -1){
                putchar(cur);
            } else{
                printf("%s", word);
            }

        } else{
            putchar(file[j]);
            ++j; // if character is not alpha then just continue reading content
        }
    }
    
}

void resize_words(){
    size_t new_size = size * 2;
    struct wg ** temp = realloc(words, sizeof(struct wg *) * new_size); 

    if(temp == NULL){
        printf("ERROR WITH RESIZING");
    }

    words = temp;
    size = new_size;
}

int is_code(char * word, size_t len){
    for(int i = 0; i < current_size; ++i) {
        if(codes[i]->length == len) {
            if(memcmp(codes[i]->content, word, len) == 0) {
                return i + OFFSET;
            }
        }
    }
    return -1;
}

struct wg * word_met(char * word, size_t len) {
    for(int i = 0; i < current_size; ++i) {
        if(words[i]->length == len) {
            if(memcmp(words[i]->content, word, len) == 0) {
                return words[i];
            }
        }
    }
    return NULL;
}

void calc_gain(){
    int k = 0;
    for(int i = 0; i < current_size; ++i){
        int count = words[i]->count;
        size_t length = words[i]->length;
        int gain = count * length - length - 1 - count;
        if(gain > 0){
            words[i]->gain = gain;
            codes[k] = words[i];
            ++k;
        }
    }

        current_size = k; // from this point current_size is size of codes array
    
}

int compare(const void * arg1, const void * arg2){
    const struct wg * a = *(const struct wg **)arg1;
    const struct wg * b = *(const struct wg **)arg2;
    if(a->gain > b->gain) return -1;
    if(a->gain < b->gain) return 1;
    return strcmp(a->content, b->content);
}

void sort_codes(){
    qsort(codes, current_size, sizeof(struct wg *),compare);
    if(current_size > 128){
        current_size = 128;
    } 
}

void print_codes(){
    for(int i = 0; i < 128; i++){
        if(i < current_size){
            putchar(i + OFFSET);
            printf("%s", codes[i]->content);
        } else{
            return;
        }
    }
}

