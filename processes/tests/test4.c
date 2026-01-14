#include <assert.h>
#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    assert(p1);

    assert(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 139;
    q.rss = 0;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    
    assert((r1 = search(p1, &q)));
    assert(strcmp(get_command(r1), "migration/0")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "watchdog/0")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "watchdog/1")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "migration/1")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "watchdog/2")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "migration/2")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "watchdog/3")==0);
    assert((r1 = next(r1)));
    assert(strcmp(get_command(r1), "migration/3")==0);
    assert(!(r1 = next(r1)));

    q.vsize = 1;

    assert(!(r1 = search(p1, &q)));

    q.vsize = -1;

    assert(!(r1 = search(p1, &q)));

    delete(p1);
    return 0;
}
