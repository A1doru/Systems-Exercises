// Write a program called imagenames in a source file called imagenames.c. The
// program must read a set of file names from the standard input, one file name per line, each
// not larger than 1000 characters. The program must output the names of image files stripped of
// directory names and name extensions. The file name without directory names is the suffix of the
// full file name that follows the last (rightmost) directory-separator character ’/’, or the full name if
// there are no directory separators. The extension, if it exists, is the shortest suffix of the file name
// that includes a period character ’.’.
// The program must recognize a set of extensions that indicate image files. By default, these extensions are .jpg, .jpeg, .png, .tiff, and .tif. However, if a command-line parameter is given,
// then the program must interpret that parameter as the name of a file from which the program
// must read the set of file extensions. This file contains any number of extentions, one per line including the period character. If for whatever reason the program fails to read the extensions from
// the given file, the program must fall back to the default extensions.
// For example, when running imagenames without command-line parameters and with the following
// input:
// android/Messaging1550748367499.jpg
// books/feyerabend_paul_against_method.pdf
// gpu_computing_gems_9780123849892.pdf
// strange_fruit.html
// android/Messaging1552068751642.jpg
// android/smile.gif
// lib/images/usi-logo.png
// lib/images/usi-logo.pdf
// weather/lugano-2019.04.03.png
// beyond_vietnam.html
// lib/images/pantheon.jpeg
// lib/images/ANTO.JPEG
// The output must be
// Messaging1550748367499
// Messaging1552068751642
// usi-logo
// lugano-2019.04.03
// pantheon

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *defaults[] = {
    ".jpg",
    ".jpeg",
    ".png",
    ".tiff",
    ".tif",
    NULL
};

void resize_ext(char ***extensions, int new_size){
    if(extensions != NULL){
        *extensions = realloc(*extensions, sizeof(char *) * new_size);
    }
}

int main(int argc, char * argv[]){
    char **extensions = (char **)defaults;
    int is_dynamic = 0;
    if(argc > 1){
        char * file_name = argv[1];
        FILE * f = fopen(file_name, "r");
        char buf[10];
        int curr_size = 5;
        extensions = malloc(sizeof(char*) * curr_size);
        int i = 0;
        while(fgets(buf, 10, f) != NULL){
            size_t ext_len = 0;
            for(int j = 0; buf[j] != '\n'; j++){
                ext_len++;
            }
            ext_len++; // to include also \0
            buf[ext_len - 1] = '\0';
            extensions[i] = malloc(ext_len);
            memcpy(extensions[i], buf, ext_len);
            if(i >= curr_size - 1){
                curr_size *= 2;
                resize_ext(&extensions, curr_size);
            }
            i++;
        }
        extensions[i] = NULL;
        is_dynamic = 1;
    }

    char * line = malloc(sizeof(char) * 1000);
    char * line_end = line + 999;

    while(fgets(line, 1000, stdin) != NULL){
        char * line_ptr = line;
        size_t line_len = 0;
        for(int j = 0; line[j] != '\n'; j++){
            line_len++;
        }
        char * without_dir = line_ptr;
        without_dir[line_len] = '\0';
        while(1){
            without_dir = memchr(line_ptr,'/', line_end - line_ptr + 1);
            if(without_dir == NULL){
                without_dir = line_ptr;
                break;
            }
            line_ptr = without_dir + 1;
        }

        // printf("%s\n", without_dir);

        char * ext_ptr = without_dir;
        line_ptr = without_dir;

        while(1){
            size_t remaining = strlen(line_ptr);
            ext_ptr = memchr(line_ptr, '.', remaining);
            if(ext_ptr == NULL){
                ext_ptr = line_ptr - 1;
                break;
            }
            line_ptr = ext_ptr + 1;
        }

        //printf("%s\n", ext_ptr);

        size_t ext_len = 0; // without dir len
        for(int j = 0; ext_ptr[j] != '\0'; j++){
            ext_len++;
        }
        // printf("EXT LEN: %d\n", ext_len);
        int match = 0;
        for(int i = 0; extensions[i] != NULL; i++){
            size_t ext_len_c = strlen(extensions[i]);
            if(ext_len_c == ext_len){
                if(memcmp(ext_ptr, extensions[i], ext_len) == 0){
                    match = 1;
                }
            }
            if(match == 1) break;
        }

        if(match == 1){

            size_t name_len = 0;
            for(char * len_ptr = without_dir; len_ptr != ext_ptr; len_ptr++){
                name_len++;
            }
            char * name = malloc(name_len + 1); // +1 for \0
            memcpy(name, without_dir, name_len);
            name[name_len] = '\0';
            printf("%s\n", name);
        }
    }

    // 3. Conditional Cleanup
    if (is_dynamic) {
        free(extensions);
    }

    return 0;
}