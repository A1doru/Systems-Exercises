#include <assert.h>

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
    struct query_result * r2;
    
    int count = 0;

    for (r1 = search(p1, &q); r1 != 0; r1 = next(r1))
	count += 1;

    assert_int_equal(count, 8);


    r1 = search(p1, &q);
    q.priority = 19;
    r2 = search(p1, &q);

    count = 0;
    for (; r1 != 0; r1 = next(r1))
	count += 1;

    assert_int_equal(count, 8);

    count = 0;
    for (; r2 != 0; r2 = next(r2))
	count += 1;
    assert_int_equal(count, 218);

    delete(p1);
    return 0;
}
