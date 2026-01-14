#include <cstdio>
#include <cstring>

#include "basic_testing.h"

#include "../colors.h"

TEST (all_zero) {
    color c;
    string_to_color (&c, "00x");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (all_f) {
    color c;
    string_to_color (&c, "ffffxff");
    CHECK_CMP(c.red,==,255);
    CHECK_CMP(c.green,==,255);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (mix_fF) {
    color c;
    string_to_color (&c, "fFfxfF");
    CHECK_CMP(c.red,==,255);
    CHECK_CMP(c.green,==,240);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (misc_012345) {
    color c;
    string_to_color (&c, "y12345");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (misc_ABCDEF) {
    color c;
    string_to_color (&c, "ABzCDEF");
    CHECK_CMP(c.red,==,171);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (misc_abcdef) {
    color c;
    string_to_color (&c, "31211I1");
    CHECK_CMP(c.red,==,49);
    CHECK_CMP(c.green,==,33);
    CHECK_CMP(c.blue,==,16);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
