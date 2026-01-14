/*
    Copies stdio and puts to stdout

    Given pairs of opener and closer chars.
    Pairs are given as string of length 2n.
    First command-line argument
    By default string is "()[]{}"


    Ommitting if o and c are consecutive.
    Or if inside o_1 anc c_1 there are only ommitted characters

    Input line is terminated with \n and does not contain more than 1000 chars
 */







#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Check if given character is closer. Return its pair_index. Otherwise -1;
*/
int is_closer(char ch, char * c){
    for(size_t i = 0; i < strlen(c); i++){
        if(ch == c[i]){
            // returning pair_index;
            return i;
        }
    }

    return -1;
}

int main(int argc, char * argv[]){
    // Allocating memory for default pairs string
    char * pairs = "()[]{}";

    // Check if new pairs were given, if yes assign
    if(argc == 2){
        pairs = argv[1];
    }

    // Creating array of for openers and closers, where openers[i] will be opener for closers[i].
    size_t pair_len = strlen(pairs);
    char * o = malloc((pair_len / 2) + 1);
    char * c = malloc((pair_len / 2) + 1);

    size_t pair_index = 0;

    for(size_t i = 0; i < pair_len; i++){
        if(i % 2 == 0){
            o[pair_index] = pairs[i];
        } else if(i % 2 == 1){
            c[pair_index] = pairs[i];
            pair_index++;
        }
    }

    o[pair_index] = '\0';
    c[pair_index] = '\0';

    // Allocate enough space for line
    char * line = malloc(sizeof(char) * 1001);
    int line_index = 0;
    int o_index;

    // Iterate throught the lines
    for(int ch = getchar(); ch != EOF; ch = getchar()){
        if(ch == '\n'){
            line[line_index] = '\0';
            line_index = 0;
            printf("%s\n", line);
        } else if((o_index = is_closer(ch, c)) != -1){
            if(line_index > 0 && line[line_index - 1] == o[o_index]){
                line_index--;
            } else{
                line[line_index] = ch;
                line_index++;
            }
        } else{
            line[line_index] = ch;
            line_index++;
        }
    }

    free(o);
    free(c);
    free(line);
}

