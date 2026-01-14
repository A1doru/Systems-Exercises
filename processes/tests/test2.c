#include <assert.h>
#include <string.h>

#include "basic_testing.h"

#include "../processes.h"

int main() {
    struct processes * p1 = new_processes();
    assert(p1);

    assert(add_from_file(p1, "tests/proc.txt"));

    struct query q;

    q.priority = 0;
    q.rss = 0;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    struct query_result * r2;
    
    int count = 0;

    for (r1 = search(p1, &q); r1 != 0; r1 = next(r1))
	count += 1;

    assert_int_equal(count, 284);

    struct processes * p2 = new_processes();
    assert(p2);

    assert(add_from_file(p2, "tests/proc1.txt"));
    assert(add_from_file(p2, "tests/proc2.txt"));
    
    r1 = search(p1, &q);
    r2 = search(p2, &q);

    count = 0;
    while (r1 && r2) {
	assert(get_pid(r1) == get_pid(r2));
	assert(get_ppid(r1) == get_ppid(r2));
	assert(strcmp(get_user(r1), get_user(r2)) == 0);
	assert(get_priority(r1) == get_priority(r2));
	assert(get_cpu_usage(r1) == get_cpu_usage(r2));
	assert(get_rss(r1) == get_rss(r2));
	assert(get_size(r1) == get_size(r2));
	assert(get_vsize(r1) == get_vsize(r2));
	assert(strcmp(get_command(r1), get_command(r2)) == 0);
	r1 = next(r1);
	r2 = next(r2);
    }
    assert(!r1);
    assert(!r2);

    clear(p1);
    assert(search(p1, &q) == 0);
    
    count = 0;
    for (r2 = search(p2, &q); r2 != 0; r2 = next(r2))
	count += 1;

    assert_int_equal(count, 284);

    clear(p2);
    assert(search(p2, &q) == 0);

    delete(p1);
    delete(p2);
    return 0;
}
