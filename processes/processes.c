#include "processes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct proc {
    int pid;
    int ppid;
    char user[9];
    int priority;
    float cpu_usage;
    long int rss;
    long int size;
    long int vsize;
    char command[16];
    struct proc * next;
};

struct processes{
    struct proc * first;
    struct proc * last;
};

struct processes * new_processes(){
    struct processes * res = malloc(sizeof(struct processes));
    if(!res){
        return NULL;
    }
    res->first = 0;
    res->last = 0;
    return res;
}

void delete(struct processes * p){
    free(p);
}

int add_from_file(struct processes * p, const char * filename){
    FILE * file = fopen(filename, "r");
    if(!file){
        return 0;
    }
    struct proc t;
    while(fscanf(file, "%d %d %8s %d %f %ld %ld %ld %15s", 
                &t.pid, &t.ppid, t.user, &t.priority, &t.cpu_usage,
                &t.rss, &t.size, &t.vsize, t.command) == 9){
        struct proc * new_proc = malloc(sizeof(struct proc));
        if(!new_proc){
            return 0;
        }
        //dereference
        *new_proc = t;
        new_proc->next = 0;
        if(p->first == 0){
            p->first = new_proc;
            p->last = new_proc;
        } else {
            p->last->next = new_proc;
            p->last = new_proc;
        }
    }

    fclose(file);
    return 1;
}

void clear(struct processes * p){
    struct proc * current_p = p->first;
    while(current_p != 0){
        p->first = p->first->next;
        free(current_p);
        current_p = p->first;
    }
    p->first = 0;
    p->last = 0;
}

struct query_match{
    struct proc * self;
    struct query_match * next;
};

struct query_result{
    struct query_match * pointer;
    struct query_match * first;
    struct query_match * last;
};

struct query_result * search(struct processes * p, const struct query * q){
    if(!p || !q){
        return NULL;
    }
    struct query_result * res = malloc(sizeof(struct query_result));
    res->pointer = 0;
    res->first = 0;
    res->last = 0;

    struct proc * current = p->first;
    int match;
    while(current != 0){
        match = 1;
        if(q->priority != 0){
            if(q->priority > 0){
                if(current->priority != q->priority) match = 0;
            } else{
                if( !(current->priority > abs(q->priority)) ) match = 0;
            }
        }
        if(match && q->rss != 0){
            if(q->rss > 0){
                if(current->rss != q->rss) match = 0;
            } else{
                if( !(current->rss > labs(q->rss)) ) match = 0;
            }
        }
        if(match && q->size != 0){
            if(q->size > 0){
                if(current->size != q->size) match = 0;
            } else{
                if( !(current->size > labs(q->size)) ) match = 0;
            }
        }
        if(match && q->vsize != 0){
            if(q->vsize > 0){
                if(current->vsize != q->vsize) match = 0;
            } else{
                if( !(current->vsize > labs(q->vsize)) ) match = 0;
            }
        }
        if(match && q->cpu_usage != 0){
            if(q->cpu_usage > 0){
                if(current->cpu_usage != q->cpu_usage) match = 0;
            } else{
                if( !(current->cpu_usage > fabs(q->cpu_usage)) ) match = 0;
            }
        }
        if(match == 1){
            struct query_match * match_item = malloc(sizeof(struct query_match));
            match_item->self = current;
            match_item->next = 0;
            if(res->first == 0){
                res->first = match_item;
                res->pointer = res->first;
                res->last = match_item;
            } else{
                res->last->next = match_item;
                res->last = match_item;
            }
        }
        current = current->next;
    }

    if(res->first == 0){
        free(res);
        return NULL;
    }

    return res;
}

int get_pid(struct query_result * r){
    return r->first->self->pid;
}

int get_ppid(struct query_result *r){
    return r->first->self->ppid;
}

const char * get_user(struct query_result *r){
    return r->first->self->user;
}

int get_priority(struct query_result *r){
    return r->first->self->priority;
}

float get_cpu_usage(struct query_result *r){
    return r->first->self->cpu_usage;
}

long int get_rss(struct query_result *r){
    return r->first->self->rss;
}

long int get_size(struct query_result *r){
    return r->first->self->size;
}

long int get_vsize(struct query_result *r){
    return r->first->self->vsize;
}

const char * get_command(struct query_result *r){
    return r->first->self->command;
}


struct query_result * next(struct query_result * q){
    if(!q){
        terminate_query(q);
        return 0;
    }
    q->pointer = q->pointer->next;
    if(q->pointer == 0){
        terminate_query(q);
        return 0;
    }
    return q;
}

void terminate_query(struct query_result * q){
    free(q);
}

/*
    Each line:
        - process-id(int)
        - parent-id(int)
        - user(string up to 8 chars)
        - priority(int)
        - cpu-usage(float)
        - resident-size(large int)
        - size (large int)
        - virtual-size (large int)
        - command (string up to 15 char)


    Processes:
        First proc -> next -> next -> next -> last -> 0

    When adding:
        0 -> 0
        First proc -> 0
*/
