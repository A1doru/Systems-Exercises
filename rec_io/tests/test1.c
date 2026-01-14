#include <assert.h>
#include <string.h>

#include "../rec_io.h"

static char buf[2000];

int main() {
    struct rec_io * r = rec_io_new();
    assert(r);
    rec_io_destroy(r);

    r = rec_io_new();
    assert(r);

    const char s1[] = "ciao mamma, come stai?";
    size_t s1_len = sizeof(s1) - 1;

    const char s2[] = "ciao";

    assert(rec_io_read_record(r, s2, s2 + 4) == 1);
    assert(rec_io_write_record(r, buf, 2000, "_%0_") == 6);
    assert(memcmp(buf, "_ciao_", 6) == 0);

    assert(rec_io_read_record(r, s1, s1 + s1_len) == 4);
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    assert(memcmp(buf, "ciao ciao!", 10) == 0);

    assert(rec_io_write_record(r, buf, 2000, "%1") == 6);
    assert(memcmp(buf, "mamma,", 6) == 0);

    assert(rec_io_write_record(r, buf, 2000, "%3") == 5);
    assert(memcmp(buf, "stai?", 5) == 0);

    assert(rec_io_write_record(r, buf, 2000, "ciao %1 come %3") == 22);
    assert(memcmp(buf, s1, 22) == 0);

    const char * sep = "-|-"; 
    rec_io_set_separator(r, sep, sep + 3);

    const char s3[] = "ciao-|-mamma, come stai?-|-aaa";
    size_t s3_len = sizeof(s3) - 1;

    assert(rec_io_read_record(r, s3, s3 + s3_len) == 3);
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    assert(memcmp(buf, "ciao ciao!", 10) == 0);

    assert(rec_io_write_record(r, buf, 2000, "%2%1") == 20);
    assert(memcmp(buf, "aaamamma, come stai?", 6) == 0);

    sep = "\0\0"; 
    rec_io_set_separator(r, sep, sep + 2);

    const char s4[] = "ciao\0\0mamma, come stai?\0\0aaa";
    size_t s4_len = sizeof(s4) - 1;

    assert(rec_io_read_record(r, s4, s4 + s4_len) == 3);
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    assert(memcmp(buf, "ciao ciao!", 10) == 0);

    assert(rec_io_write_record(r, buf, 2000, "%2%1") == 20);
    assert(memcmp(buf, "aaamamma, come stai?", 6) == 0);

    struct rec_io * r2 = rec_io_new();
    assert(r2);

    const char sep2[] = "come";
    rec_io_set_separator(r2, sep2, sep2 + 4);

    assert(rec_io_read_record(r2, s4, s4 + s4_len) == 2);
    assert(rec_io_write_record(r2, buf, 2000, "%1") == 11);
    assert(memcmp(buf, " stai?\0\0aaa", 11) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "%0") == 13);
    assert(memcmp(buf, "ciao\0\0mamma, ", 13) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "%1-%0-") == 26);
    assert(memcmp(buf, " stai?\0\0aaa-ciao\0\0mamma, -", 26) == 0);

    const char sep3[] = "\0";
    rec_io_set_separator(r2, sep3, sep3 + 1);

    assert(rec_io_read_record(r2, s4, s4 + s4_len) == 5);
    assert(rec_io_write_record(r2, buf, 2000, "-%1-") == 2);
    assert(memcmp(buf, "--", 2) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "+%1+%3+") == 3);
    assert(memcmp(buf, "+++", 3) == 0);

    rec_io_destroy(r2);
    rec_io_destroy(r);

    return 0;
}
