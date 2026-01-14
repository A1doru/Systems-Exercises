// In a source file called alpha.c or alpha.cc write a C or C++ program to encode
// and decode data according to the “alpha” coding scheme defined below. Without command-line
// arguments, the program works in encoding mode, reading data from its standard input and writing
// the corresponding code onto the standard output. Vice-versa, with the -d command-line argument,
// the program works in decoding mode, reading a code from the standard input, and writing the
// corresponding data to the standard output.

// The alpha encoding works as follows. The input is a stream of bytes. The output (or “code”) is a
// stream of the 26 lowercase and 26 uppercase letters of the English language:
// abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ
// As specified later, the code may contain other characters. However, those must be ignored for the
// purpose of decoding. The encoding rules are as follows:

// • An input byte corresponding to a letter other than the letter Q is encoded by an identical output byte. For example, 
// the sequence of characters “quack” is encoded as the same sequence
// of characters “quack”.

// • The input byte representing the letter Q is encoded by two identical bytes representing the
// letter Q. For example, the input characters “Quote” are encoded as “QQuote”.

// • An input byte b that is not a letter is encoded by the character Q followed by two letters c1c2
// that encode b as follows: c1 and c2 encode numbers between 0 and 15 that are the most
// and least significant four bits of b, respectively. In particular, the values 0, 1, 2, . . . , 15 are
// encoded as a,b, c,. . . ,p, respectively. For example a byte b = 0 is encoded as Qaa; a byte b = 1
// is encoded as Qab; a byte b = 16 is encoded as Qba; a byte b = 33 representing the character
// ‘!’ is encoded as Qcb. Recall that, in general, the most and least significant 4 bits of a byte b
// can be computed (in C/C++) as b / 16 and b % 16, respectively.

// • You may assume the ASCII code. In particular, a letter (a. . . z, A. . . Z) corresponds to a single
// byte, and the numeric codes (byte values) of the letters in alphabetical order are consecutive
// numbers. That is, the code for b is one plus the code for a, and so on.

// stdin -> encode
// argument -> decode

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void encode();
int decode();

int main(int argc, char * argv[]){
    // printf("LOL\n");
    if(argc == 2){
        if(strcmp(argv[1], "-d") == 0){
            int res = decode();
            if(res == 0) return EXIT_FAILURE;
        } else{
            return EXIT_FAILURE;
        }
    } else if(argc == 1){
        encode();
        return EXIT_SUCCESS;
    } else{
        return EXIT_FAILURE;
    }
}


int is_letter(char c){
    if(c >= 'a' && c <= 'z') return 1;
    if(c >= 'A' && c <= 'Z') return 1;
    return 0;
}

void put_code(int c, int * counter){
    int ms = c / 16;
    putchar('a' + ms);
    ++(*counter);
    if(*counter == 80){
        putchar('\n');
        *counter = 0;
    }
    int ls = c % 16;
    putchar('a' + ls);
    ++(*counter);
    if(*counter == 80){
        putchar('\n');
        *counter = 0;
    }
}

void encode(){
    int c;
    int counter = 0;
    int is_empty = 1;
    while((c = getchar()) != EOF){
        is_empty = 0;
        if(c == 'Q'){ 
            putchar('Q');
            counter++;
            if(counter == 80){ 
                putchar('\n');
                counter = 0;
            }
            putchar('Q');
            counter++;
        }
        else if(is_letter(c) == 1){
            putchar(c);
            ++counter;
        } 
        else{
            putchar('Q');
            ++counter;
            if(counter == 80){ 
                putchar('\n');
                counter = 0;
            }
            put_code(c, &counter);
        }
        if(counter == 80){
            putchar('\n');
            counter = 0;
        }
    }
    if(is_empty) return;
    putchar('\n');
}

// return 0 on failure
int print_char(){
    char c1 = getchar();
    while(c1 != EOF){
        if(is_letter(c1) == 1) break;
        c1 = getchar();
    }
    if(c1 == EOF) return 0;
    if(c1 == 'Q'){
        putchar('Q');
        return 1;
    }
    if(c1 < 'a' || c1 > 'p') return 0;
    int ms = c1 - 'a';
    char c2 = getchar(); 
    while(c2 != EOF){
        if(is_letter(c2) == 1) break;
        c2 = getchar();
    }
    if(c2 == EOF) return 0;
    if(c2 < 'a' || c2 > 'p') return 0;
    int ls = c2 - 'a';

    int sym = (ms * 16) + ls;
    putchar(sym);
    return 1;
}

int decode(){
    char c;
    int counter = 0;
    while((c = getchar()) != EOF){
        if(c == 'Q'){
            int res = print_char();
            if(res == 0) return 0;
            counter++;
        } else if(is_letter(c) == 1){
            putchar(c);
            counter++;
        } else{
            continue;
        }

    }

    return 1;
}
