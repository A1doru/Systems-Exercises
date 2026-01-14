#include <assert.h>

#include "../tank_control.h"

int main() {
    assert(get_tank_level() == 0);
    assert(get_wastes() == 0);
    return 0;
}
