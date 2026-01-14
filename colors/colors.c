#include "colors.h"
#include <string.h>

int is_hex(char c){
    if(c >= '0' && c <= '9') return 1;
    if(c >= 'A' && c <= 'F') return 1;
    if(c >= 'a' && c <= 'f') return 1;
    return 0;
}

int hex_to_num(char c){
    if(c >= '0' && c <= '9') return c - '0';
    if(c == 'a' || c == 'A') return 10;
    if(c == 'b' || c == 'B') return 11;
    if(c == 'c' || c == 'C') return 12;
    if(c == 'd' || c == 'D') return 13;
    if(c == 'e' || c == 'E') return 14;
    if(c == 'f' || c == 'F') return 15;
}

void string_to_color (struct color * c, const char * ch){
    int term = 0;
    size_t len = strlen(ch);
    int i = 0;
    int v1 = 0;
    int v2 = 0;
    for(int i = 0; i < 3; i++){
        int i1 = i * 2;
        int i2 = i1 + 1;
        if(i1 >= len || term == 1) {
            v1 = 0;
        }
        else if(is_hex(ch[i1]) == 0){
            term = 1;
            v1 = 0;
        }
        else{
            v1 = hex_to_num(ch[i1]);
        }
        if(i2 >= len || term == 1) {
            v2 = 0;
        }
        else if(is_hex(ch[i2]) == 0){
            term = 1;
            v2 = 0;
        }
        else {
            v2 = hex_to_num(ch[i2]);
        }
        int value = 16 * v1 + v2;
        if(i == 0) c->red = value;
        if(i == 1) c->green = value;
        if(i == 2) c->blue = value;
    }
}