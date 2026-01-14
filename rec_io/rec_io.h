#ifndef REC_IO_H_INCLUDED
#define REC_IO_H_INCLUDED

#include <stddef.h>

struct rec_io;

/* This is the maximal size for an input record.  The module must
 * support input records up to this size.
 */
#define MAX_RECORD_LENGTH      1000

/* This is the maximal size for a record separator.  The module must
 * support separators up to this size.
 */
#define MAX_SEPARATOR_LENGTH     10

/* Constructor
 *
 * Returns a pointer to a valid rec_io object, or NULL in case of
 * error (e.g., insufficient memory)
 */
extern struct rec_io * rec_io_new();

/* Destructor
 */
extern void rec_io_destroy(struct rec_io *);

/* Configure this rec_io filter to use the separator string defined by
 * the begin and end pointers.  Notice that a separator can be any
 * sequence of bytes (at most MAX_SEPARATOR_LENGTH).  In particular, a
 * separator may contain the NULL character ('\0', one or more).
 *
 * The default separator is the sequence consisting of a single space
 * character.  Setting a separator determines how the filter reads any
 * successive input record (with rec_io_read_record).
 */
extern void rec_io_set_separator(struct rec_io * this, const char * begin, const char * end);

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
extern int rec_io_read_record(struct rec_io * this, const char * begin, const char * end);

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
extern size_t rec_io_write_record(struct rec_io * this,
				  char * out, size_t maxlen, const char * format);

#endif
