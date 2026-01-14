#include "processes.h"
#include <stdio.h>

int main(){
    struct processes * p1 = new_processes();
    add_from_file(p1, "./tests/proc.txt");

    struct query q;

    q.priority = 0;
    q.rss = 0;
    q.size = 0;
    q.vsize = 0;
    q.cpu_usage = 0;
    
    struct query_result * r1;
    struct query_result * r2;
    
    int count = 0;
    r1 = search(p1, &q);

if (r1 == NULL) {
        printf("No matching processes found.\n");
    } else {
        printf("Found matching processes:\n");
        
        // Loop through the query_result list (r1)
        struct query_match *current_match = r1->first;
        while (current_match != 0) {
            
            // 1. Get the process from the match node
            struct proc *matching_proc = current_match->self;
            
            // 2. Print its details (e.g., pid and command)
            printf("  -> PID: %u, Command: %s\n", 
                   matching_proc->pid, 
                   matching_proc->command);
            
            // 3. Move to the next match
            current_match = current_match->next;
        }
    }
}