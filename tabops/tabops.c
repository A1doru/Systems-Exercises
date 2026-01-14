
/**
    Each line - sequence of data items; then these data items are printed in stdout according to the format.

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH  1024
#define MAX_ITEMS 26

int tokenize_line(char * line, const char * delim, char * items_res[]){
    // Getting adress of first token
    char * token = strtok(line, delim);
    if(token == NULL){
        return 0;
    }
    int token_count = 0;

    while(token != NULL && token_count < MAX_ITEMS){
        items_res[token_count] = token;
        token_count++;
        token = strtok(NULL, delim);
    }

    return token_count;
}

void print_formatted(char * items_res[], int items_count, const char * format){

    for(int i = 0; i < strlen(format); i++){
        // If caught placeholder
        if(format[i] == '@'){
            int index = format[i+1] - 'a';
            if(index >= 0 && index < items_count){
                printf("%s", items_res[index]);
            }
            i++;
        } else{
            putchar(format[i]);
        }
    }
    putchar('\n');
}

void process_file(FILE * source, const char * delim, const char * format){

    char * line = malloc(LINE_LENGTH);

    while(fgets(line, LINE_LENGTH, source) != NULL){
        if(line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        char * items[MAX_ITEMS];
        int items_count = tokenize_line(line, delim, items);
        print_formatted(items, items_count, format);
    }
    free(line);
}


int main(int argc, char * argv[]){

    char * filename = NULL;
    char * delim = " \t";
    char * format = "@a";

    int file_prosessed = 0;

    for(int i = 1; i < argc; i++){
        if(strncmp("format=", argv[i], 7) == 0){
            format = strchr(argv[i], '=');
            format++;
        } else if(strncmp("delim=", argv[i], 6) == 0){
            delim = strchr(argv[i], '=');
            delim++;
        } else{
            filename = argv[i];
            FILE * src = fopen(filename, "r");
            if(src == NULL){
                return 1;
            }
            file_prosessed = 1;
            process_file(src, delim, format);
            fclose(src);
            filename = NULL;
        }
    }
    if(file_prosessed == 0){
        process_file(stdin, delim, format);
    }
}


