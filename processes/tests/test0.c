#include <assert.h>

#include "../processes.h"

int main() {
    struct processes * p = new_processes();
    assert(p);
    delete(p);
    return 0;
}
