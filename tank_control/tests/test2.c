#include "basic_testing.h"
#include "../tank_control.h"

int main() {
    assert_int_equal(ship_out_bottles(), 0);

    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);
    
    add(90300);
    
    assert_int_equal(get_tank_level(), 90300);
    assert_int_equal(get_wastes(), 0);

    clear();

    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);
    
    add(200000);
    assert_int_equal(get_tank_level(), 200000);
    assert_int_equal(get_wastes(), 0);
    
    add(1200000);
    assert_int_equal(get_tank_level(), 1000000);
    assert_int_equal(get_wastes(), 400000);
    
    assert_int_equal(ship_out_bottles(), 1333);
    assert_int_equal(get_tank_level(), 250);
    assert_int_equal(get_wastes(), 400000);

    clear();

    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);
    
    add(200000);
    assert_int_equal(get_tank_level(), 200000);
    assert_int_equal(get_wastes(), 0);
    
    add(900000);
    assert_int_equal(get_tank_level(), 1000000);
    assert_int_equal(get_wastes(), 100000);
    
    assert_int_equal(ship_out_bottles(), 1333);
    assert_int_equal(get_tank_level(), 250);
    assert_int_equal(get_wastes(), 100000);

    clear();

    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 0);

    return 0;
}
