#include <cstdio>
#include <cstring>

#include "basic_testing.h"

#include "../colors.h"

TEST (empty) {
    color c;
    string_to_color (&c, "");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit) {
    color c;
    string_to_color (&c, "1");
    CHECK_CMP(c.red,==,16);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_1) {
    color c;
    string_to_color (&c, "1");
    CHECK_CMP(c.red,==,16);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_0) {
    color c;
    string_to_color (&c, "0");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_a) {
    color c;
    string_to_color (&c, "a");
    CHECK_CMP(c.red,==,160);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_A) {
    color c;
    string_to_color (&c, "A");
    CHECK_CMP(c.red,==,160);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_F) {
    color c;
    string_to_color (&c, "F");
    CHECK_CMP(c.red,==,240);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (one_digit_f) {
    color c;
    string_to_color (&c, "f");
    CHECK_CMP(c.red,==,240);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
