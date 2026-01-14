// These structures and functions are intended to be used to manage boats and excursions in a rowing
// club. The club has a number of boats and a number of members who join the club to participate
// in excursions. Each excursion must be recorded, so that the system can keep track of which boats
// are in use at any given time. The system also keeps track of the number of excursions and the
// total number of kilometers traveled by each member of the club. The detailed specification is as
// follows

#include "rowing.h"


struct club * create_club (){

}
void destroy_club (struct club *){

}

int add_boat (struct club * c, const char * ch, unsigned int amount){

}
int add_person (struct club * c, const char *){

}

struct excursion * create_excursion (struct club *){

}
int use_boat (struct excursion *, const char *);
int add_crew (struct excursion *, const char *);

int close_excursion (struct excursion *, unsigned int);
void cancel_excursion (struct excursion *);

int get_crew_excursions (struct club *, const char *);
int get_crew_kilometers (struct club *, const char *);

int boat_available (struct club *, const char *);
int get_boat_excursions (struct club *, const char *);
int get_boat_kilometers (struct club *, const char *);