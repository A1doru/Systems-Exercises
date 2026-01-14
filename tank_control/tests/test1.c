#include "basic_testing.h"

#include "../tank_control.h"

int main() {
    assert_int_equal(ship_out_bottles(), 0);

    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);
    
    add(90300);
    
    assert_int_equal(get_tank_level(), 90300);
    assert_int_equal(get_wastes(), 0);

    assert_int_equal(ship_out_bottles(), 120);
    assert_int_equal(get_tank_level(), 300);
    assert_int_equal(get_wastes(), 0);

    add(90300);
    
    assert_int_equal(ship_out_bottles(), 120);
    assert_int_equal(get_tank_level(), 600);
    assert_int_equal(get_wastes(), 0);

    add(5400);
    assert_int_equal(ship_out_bottles(), 8);
    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);

    return 0;
}
