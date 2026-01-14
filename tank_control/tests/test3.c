#include "basic_testing.h"
#include "../tank_control.h"

int main() {
    add(100000);
    
    assert_int_equal(get_tank_level(), 100000);
    assert_int_equal(get_wastes(), 0);

    change_tank(80000);

    assert_int_equal(get_tank_level(), 80000);
    assert_int_equal(get_wastes(), 20000);

    change_bottle_capacity(800);
    
    assert_int_equal(get_tank_level(), 80000);
    assert_int_equal(get_wastes(), 20000);

    add(10000);
    assert_int_equal(get_tank_level(), 80000);
    assert_int_equal(get_wastes(), 30000);

    assert_int_equal(ship_out_bottles(), 100);
    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 30000);

    change_tank(50000);

    add(10000);
    change_bottle_capacity(500);
    assert_int_equal(ship_out_bottles(), 20);
    assert_int_equal(get_tank_level(), 0);
    assert_int_equal(get_wastes(), 30000);

    return 0;
}
