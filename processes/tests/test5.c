#include <assert.h>
#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    assert(p1);

    assert(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 19;
    q.rss = -1;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    
    assert((r1 = search(p1, &q)));
    assert(strcmp(get_user(r1), "root") == 0);
    assert((r1 = next(r1)));
    assert(strcmp(get_user(r1), "root") == 0);
    assert((r1 = next(r1)));
    assert(strcmp(get_user(r1), "systemd+") == 0);
    assert((r1 = next(r1)));
    assert(strcmp(get_user(r1), "systemd+") == 0);
    assert((r1 = next(r1)));
    terminate_query(r1);

    q.priority = 19;
    q.rss = 0;
    q.size = 0;
    q.vsize = -2000000;
    q.cpu_usage = -1.0;
    
    assert((r1 = search(p1, &q)));

    assert(get_pid(r1) == 2331);
    assert(strcmp(get_command(r1), "firefox") == 0);
    assert((r1 = next(r1)));
    assert(get_pid(r1) == 2986);
    assert(strcmp(get_command(r1), "WebContent") == 0);
    assert(!(r1 = next(r1)));

    delete(p1);
    return 0;
}
