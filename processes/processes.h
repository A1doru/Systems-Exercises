#ifndef PROCESSS_H_INCLUDED
#define PROCESSS_H_INCLUDED

struct processes;

extern struct processes * new_processes();
extern void delete(struct processes * p);
extern int add_from_file(struct processes * p, const char * filename);
extern void clear(struct processes * p);

struct query {
    int priority;
    long int rss;
    long int size;
    long int vsize;
    float cpu_usage;
};

struct query_result;

struct query_result * search(struct processes *, const struct query *);

extern int get_pid(struct query_result *r);
extern int get_ppid(struct query_result *r);
extern const char * get_user(struct query_result *r);
extern int get_priority(struct query_result *r);
extern float get_cpu_usage(struct query_result *r);
extern long int get_rss(struct query_result *r);
extern long int get_size(struct query_result *r);
extern long int get_vsize(struct query_result *r);
extern const char * get_command(struct query_result *r);

struct query_result * next(struct query_result *);
void terminate_query(struct query_result *);

#endif
