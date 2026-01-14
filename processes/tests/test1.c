#include <assert.h>

#include "../processes.h"

int main() {
    struct processes * p = new_processes();
    assert(p);
    assert(add_from_file(p, "tests/proc.txt"));
    clear(p);
    delete(p);
    return 0;
}
