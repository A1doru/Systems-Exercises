#include <cstdio>
#include <cstring>

#include "basic_testing.h"

#include "../colors.h"

TEST (all_zero) {
    color c;
    string_to_color (&c, "000000");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (all_f) {
    color c;
    string_to_color (&c, "ffffff");
    CHECK_CMP(c.red,==,255);
    CHECK_CMP(c.green,==,255);
    CHECK_CMP(c.blue,==,255);
    TEST_PASSED;
}

TEST (mix_fF) {
    color c;
    string_to_color (&c, "fFfFfF");
    CHECK_CMP(c.red,==,255);
    CHECK_CMP(c.green,==,255);
    CHECK_CMP(c.blue,==,255);
    TEST_PASSED;
}

TEST (misc_012345) {
    color c;
    string_to_color (&c, "012345");
    CHECK_CMP(c.red,==,1);
    CHECK_CMP(c.green,==,35);
    CHECK_CMP(c.blue,==,69);
    TEST_PASSED;
}

TEST (misc_ABCDEF) {
    color c;
    string_to_color (&c, "ABCDEF");
    CHECK_CMP(c.red,==,171);
    CHECK_CMP(c.green,==,205);
    CHECK_CMP(c.blue,==,239);
    TEST_PASSED;
}

TEST (misc_abcdef) {
    color c;
    string_to_color (&c, "abcdef");
    CHECK_CMP(c.red,==,171);
    CHECK_CMP(c.green,==,205);
    CHECK_CMP(c.blue,==,239);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
