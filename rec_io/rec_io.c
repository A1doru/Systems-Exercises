#include "rec_io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct rec_io{
    char * separator;
    int sep_len;
    char * record;
    char ** fields;
    size_t * fields_len;
    int fields_size;
    int field_counter;
};

// #define MAX_RECORD_LENGTH      1000

// #define MAX_SEPARATOR_LENGTH     10

/* Constructor
 *
 * Returns a pointer to a valid rec_io object, or NULL in case of
 * error (e.g., insufficient memory)
 */
struct rec_io * rec_io_new(){
    struct rec_io * new_rec = malloc(sizeof(struct rec_io));
    if(new_rec == NULL) return NULL;
    new_rec->record = NULL;
    new_rec->fields_size = 8; // by default I will allocate array for 8 fields
    new_rec->field_counter = 0;
    new_rec->fields = malloc(sizeof(char *) * new_rec->fields_size); 
    new_rec->separator = malloc(1);
    if(new_rec->separator == NULL) return NULL;
    new_rec->separator[0] = ' ';
    new_rec->sep_len = 1;
    new_rec->fields_len = malloc(sizeof(size_t) * new_rec->fields_size);

    return new_rec;
}

/* Destructor
 */
void rec_io_destroy(struct rec_io * this){
    free(this->separator);
    free(this->record);
    free(this);
}

/* Configure this rec_io filter to use the separator string defined by
 * the begin and end pointers.  Notice that a separator can be any
 * sequence of bytes (at most MAX_SEPARATOR_LENGTH).  In particular, a
 * separator may contain the NULL character ('\0', one or more).
 *
 * The default separator is the sequence consisting of a single space
 * character.  Setting a separator determines how the filter reads any
 * successive input record (with rec_io_read_record).
 */
void rec_io_set_separator(struct rec_io * this, const char * begin, const char * end){
    if(this->separator != NULL){
        free(this->separator); // clean old separator
    }
    size_t sep_len = end - begin;
    if(sep_len > MAX_SEPARATOR_LENGTH){
        return;
    }

    this->separator = malloc(sep_len);
    if(this->separator != NULL){
        memcpy(this->separator, begin, sep_len);
        this->sep_len = sep_len;
    } else{
        this->separator = malloc(1);
        if(this->separator == NULL) return;
        this->separator[0] = ' ';
        this->sep_len = 1;
    }
}

void increase_array(struct rec_io * this){
    int new_size = this->fields_size * 2;
    this->fields = realloc(this->fields, sizeof(char *) * new_size);
    this->fields_len = realloc(this->fields_len, sizeof(size_t) * new_size);
    this->fields_size = new_size;
}

void debug_print(struct rec_io * this){
    for(int i = 0; i < this->field_counter; i++){
        putchar('\n');
        putchar('\n');
        for(int j = 0; j < this->fields_len[i]; j++){
            putchar(this->fields[i][j]);
        }
        printf("\nFIELD LEN: %zu\n", this->fields_len[i]);
        putchar('\n');
        putchar('\n');
    }
}

/* Passes an input record to this filter for later processing by the
 * filter.  An input record is any sequence of characters (at most
 * MAX_RECORD_LENGTH) composed of fields separaterd by separator
 * strings.  The beginning of the sequence and the end of the sequence
 * are implicit separators, so an input sequence that does not contain
 * the separator consists of exactly one field equal to the entire
 * sequence.  Fields may be zero-length sequences.
 *
 * This method must return the number of fields read.
 */
int rec_io_read_record(struct rec_io * this, const char * begin, const char * end){
    if(this->record != NULL){
        free(this->record); // clean old record
    }
    size_t rec_len = end - begin + 1;
    if(rec_len > MAX_RECORD_LENGTH){
        return 0;
    }
    this->record = malloc(rec_len);
    if(this->record == NULL) return 0;
    for(int i = 0; i < this->field_counter; i++) free(this->fields[i]);
    memcpy(this->record, begin, rec_len);

    char * pointer = this->record; // point to the beginning of the field, calculate lenght of field by doing match - pointer
    char * field_start = pointer;
    char * rec_end = this->record + rec_len - 1;
    this->field_counter = 0;
    while(pointer <= rec_end){
        char * match = memchr(pointer, this->separator[0], rec_end - pointer + 1);
        if(match == NULL){
            size_t field_len = rec_end - field_start + 1;
            this->fields[this->field_counter] = malloc(field_len);
            memcpy(this->fields[this->field_counter], field_start, field_len);
            this->fields_len[this->field_counter] = field_len - 1;
            this->field_counter++;
            if(this->field_counter >= this->fields_size){
                increase_array(this);
            }
            break;
        } 
        else{
            if(memcmp(match, this->separator, this->sep_len) == 0){
                size_t field_len = match - field_start;
                this->fields[this->field_counter] = malloc(field_len);
                memcpy(this->fields[this->field_counter], field_start, field_len);
                this->fields_len[this->field_counter] = field_len;
                this->fields_len[this->field_counter] = field_len;
                this->field_counter++;
                if(this->field_counter >= this->fields_size){
                    increase_array(this);
                }
                field_start = match + this->sep_len;
                pointer = field_start;
            } else{
                pointer = match + 1;
            }   
        }
    }
    return this->field_counter;
}

/* Outputs the input record previously read with rec_io_read_record
 * using the given format string.  The output is given as a sequence
 * of characters written in the output buffer provided by the
 * application.  This method may not write more than maxlen characters
 * into the output buffer.  The return value is the actual number of
 * characters written into the output.
 *
 * The format string is a C string, meaning it is terminated by '\0'.
 * The format string may contain field indicator consisting of a
 * single percent character ('%') followed by a decimal number.
 * Fields are numbered starting from 0.  So, for example, the format
 * string "%0" should output the first fields.  A field indicator that
 * points to a field that was not read must have no output (for
 * example, "%4" when only four or less fields were read).
 * 
 * Any other character or sequence of characters in the format string
 * must be copied identically into the output.  So, for example, the
 * format string "1: %0\n2: %1\n" should output two lines containing
 * the first and second field, respectively.
 *
 * This method can be called multiple times for the same record,
 * possibly with different format strings.
 */
size_t rec_io_write_record(struct rec_io * this, char * out, size_t maxlen, const char * format){
    if(this == NULL) return 0;
    if(this->separator == NULL || this->record == NULL) return 0;
    size_t length = 0;
    int i = 0;
    int out_i = 0;

    do{
        if(format[i] == '%' && isdigit(format[i+1])){
            int index = format[i+1] - '0';
            if(index >= this->field_counter) continue;
            char * field = this->fields[index];
            for(int j = 0; j < this->fields_len[index]; j++){
                putchar(field[j]);
                length++;
                out[out_i] = field[j];
                out_i++;
            }
            i++;
        } else{
            putchar(format[i]);
            length++;
            out[out_i] = format[i];
            out_i++;
        }
        if(length >= maxlen) return length;
        i++;

    } while(format[i] != '\0');
    return length;
}
