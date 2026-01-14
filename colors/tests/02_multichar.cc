#include <cstdio>
#include <cstring>

#include "basic_testing.h"

#include "../colors.h"

TEST (two_digits_11) {
    color c;
    string_to_color (&c, "11");
    CHECK_CMP(c.red,==,17);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (two_digit_01) {
    color c;
    string_to_color (&c, "01");
    CHECK_CMP(c.red,==,1);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (two_digit_a1) {
    color c;
    string_to_color (&c, "a1");
    CHECK_CMP(c.red,==,161);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (two_digit_A1) {
    color c;
    string_to_color (&c, "A1");
    CHECK_CMP(c.red,==,161);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (two_digit_F1) {
    color c;
    string_to_color (&c, "F1");
    CHECK_CMP(c.red,==,241);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (two_digit_f1) {
    color c;
    string_to_color (&c, "f1");
    CHECK_CMP(c.red,==,241);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (three_digits_001) {
    color c;
    string_to_color (&c, "001");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,16);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (three_digit_000) {
    color c;
    string_to_color (&c, "000");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,0);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (three_digit_00a) {
    color c;
    string_to_color (&c, "00a");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,160);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (three_digit_00f) {
    color c;
    string_to_color (&c, "00f");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,240);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (four_digits_0011) {
    color c;
    string_to_color (&c, "0011");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,17);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (four_digit_0001) {
    color c;
    string_to_color (&c, "0001");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,1);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (four_digit_00a1) {
    color c;
    string_to_color (&c, "00a1");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,161);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (four_digit_00f1) {
    color c;
    string_to_color (&c, "00f1");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,241);
    CHECK_CMP(c.blue,==,0);
    TEST_PASSED;
}

TEST (five_digits_00111) {
    color c;
    string_to_color (&c, "00111");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,17);
    CHECK_CMP(c.blue,==,16);
    TEST_PASSED;
}

TEST (five_digit_00011) {
    color c;
    string_to_color (&c, "00011");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,1);
    CHECK_CMP(c.blue,==,16);
    TEST_PASSED;
}

TEST (five_digit_00a11) {
    color c;
    string_to_color (&c, "00a11");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,161);
    CHECK_CMP(c.blue,==,16);
    TEST_PASSED;
}

TEST (five_digit_00f11) {
    color c;
    string_to_color (&c, "00f11");
    CHECK_CMP(c.red,==,0);
    CHECK_CMP(c.green,==,241);
    CHECK_CMP(c.blue,==,16);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
