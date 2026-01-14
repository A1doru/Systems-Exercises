#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2000

struct rules{
    char * p;       // pattern to match
    char * t;      // text to be replaced with, instead of : put \n in order to imitate lines
};

size_t current_size = 0;
size_t capacity = 8;
struct rules ** r;

void increase_r(){
    size_t new_capacity = capacity * 2;
    struct rules ** temp = realloc(r, sizeof(struct rules *) * new_capacity);

    if(temp == NULL){
        printf("ERROR WHILE RESIZING");
    }

    r = temp;
    capacity = new_capacity;
}

void add_rules(FILE * f);           // reads rules from the file and saves them   
int find_match(char * ch);        // returns amount of chars needed to skip, zero if no match

void print_debug(){
    for(int i = 0; i < current_size; i++){
        printf("PATTERN: %s TEXT:%s MY T-LENGTH IS:%d\n", r[i]->p, r[i]->t, strlen(r[i]->t));
    }
}

int main(int argc, char * argv[]){
    r = malloc(sizeof(struct rules *) * capacity);
    if(r == NULL){
        printf("MEMORY ERROR");
        return EXIT_FAILURE;
    }

    if(argc < 2){
        FILE * f = fopen("./RULES", "r");
        if(f == NULL) {
            printf("FILE ERROR");
            return EXIT_FAILURE;
        }
        add_rules(f);
        fclose(f);
    } else{
        for(int i = 1; argv[i] != NULL; i++){
            FILE * f = fopen(argv[i], "r");
            if(f == NULL) {
                printf("invalid rules file %s\n", argv[i]);
                return EXIT_FAILURE;
            }
            add_rules(f);
            fclose(f);
        }
    }
    // print_debug();

    char line[2001];
    while(fgets(line, 2001, (stdin)) != NULL){
        int i = 0;
        while(line[i] != '\0'){
            int jump = find_match(&line[i]);
            if(jump > 0){
                i += jump;
            } else{
                putchar(line[i]);
                ++i;
            }
        }
    }

    return EXIT_SUCCESS;
}

int find_match(char * ch){
    for(int i = 0; i < current_size; ++i){
        size_t len = strlen(r[i]->p);
        // printf("I AM HERE:%s MY LENGTH IS: %d\n", r[i]->p, len);
        if(memcmp(ch, r[i]->p, len) == 0){
            printf("%s", r[i]->t);
            return len;
        }
    }

    return 0;
}


void add_text(char ** t_buf, int * ti){
    if(*t_buf != NULL){
        (*t_buf)[*ti] = '\0';
        size_t t_len = strlen(*t_buf);
        r[current_size - 1]->t = malloc(sizeof(char) * t_len);
        memcpy(r[current_size - 1]->t, *t_buf, t_len);
        free(*t_buf);
    }
    *t_buf = malloc(100000);
    *ti = 0;
}

void add_rules(FILE * f){
    char * t_buf = NULL;
    int ti = 0;
    char line[2001];
    while(fgets(line, 2001, f) != NULL){
        char * p_start = &line[0];
        char * semi_col = strchr(p_start, ':'); 
        if(line[0] != ':' && semi_col != NULL){
            char * p_end = semi_col;

            size_t p_len = p_end - p_start;
            r[current_size] = malloc(sizeof(struct rules *));
            if(r[current_size] == NULL){
                printf("MEM ERROR");
            } 
            r[current_size]->p = malloc(sizeof(char) * p_len);
            if(r[current_size]->p == NULL){
                printf("MEM ERROR");
            }
            memcpy(r[current_size]->p, p_start, p_len);
            add_text(&t_buf, &ti);

            // NOW READ REST OF THE DEF LINE: 
            char * t = p_end + 1;
            for(int i = 0; t[i] != '\0' && t[i] != '\n'; ++i){
                t_buf[ti] = t[i];
                ++ti;
            }

            current_size++;
            if(current_size >= capacity){
                increase_r();
            }

        } else if(line[0] == ':') { 
            for(int i = 0; line[i] != '\0' && line[i] != '\n'; ++i){
                if(i == 0 && line[i] == ':'){
                    t_buf[ti] = '\n';
                    ++ti;
                } else{
                    t_buf[ti] = line[i];
                    ++ti;
                }
            }
        } else{
            // char * hello = "hello";
            // printf("%d\n\n\n", strcmp(hello, t_buf));
            // add_text(&t_buf, &ti);
            continue;
        }
    }   
    add_text(&t_buf, &ti);
    free(t_buf);
}