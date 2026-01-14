// These structures and functions are intended to be used to manage boats and excursions in a rowing
// club. The club has a number of boats and a number of members who join the club to participate
// in excursions. Each excursion must be recorded, so that the system can keep track of which boats
// are in use at any given time. The system also keeps track of the number of excursions and the
// total number of kilometers traveled by each member of the club. The detailed specification is as
// follows

#include "rowing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN_CREW 1

struct boat {
    int max_crew;                   // max crew size
    int cur_crew;                   // current amount of people of the crew
    char * name;                    // name of the boat
    int is_busy;                    // is the boat is used in excursion, NULL if not busy
    int distance;                   // distance traveled by this boat
    int exc_count;                  // amount of exc done by boat
};
struct person{
    char * name;                    // name of the person
    struct excursion * exc;     // person is used for the exc, NULL if not busy
    int exc_count;                  // amount of exc done by person
    int distance;                   // distance traveled by this person
};
struct club{
    size_t boats_cap;       // current capacity of the boats array
    size_t boats_count;     // current amount of boats in the array
    struct boat ** boats;   // array of the boats

    size_t mems_cap;        // current capacity of the mems array
    size_t mems_count;      // current amount of people in the array
    struct person ** mems;  // members of the club
};
struct excursion{
    struct boat * sel_boat; // selected boat for the excursion
    struct club * c;        // belongs to this club
};


// creates a club. Return a valid pointer to a new, empty club. Return the null pointer if
// memory is exhausted and therefore the creation of a new club object fails.
struct club * create_club (){
    struct club * new_club = malloc(sizeof(struct club));
    if(new_club == NULL) return NULL;

    new_club->boats_cap = 8;
    new_club->boats_count = 0;
    new_club->boats = malloc(sizeof(struct boat *) * new_club->boats_cap);
    if(new_club->boats == NULL) return NULL;

    new_club->mems_cap = 8;
    new_club->mems_count = 0;
    new_club->mems = malloc(sizeof(struct person *) * new_club->mems_cap);
    if(new_club->mems == NULL) return NULL;

    return new_club;
}
// destroys the given club object and releases all its allocated resources
void destroy_club (struct club * c){
    if(c != NULL){
        for(int i = 0; i < c->boats_count; ++i){
            free(c->boats[i]->name);
            free(c->boats[i]);
        }
        free(c->boats);
        for(int i = 0; i < c->mems_count; ++i){
            free(c->mems[i]->name);
            free(c->mems[i]);
        }
        free(c->mems);
        free(c);
    }
}

struct boat * find_boat(struct club * c, char * boat_name){
    for(int i = 0; i < c->boats_count; ++i){
        if(strcmp(boat_name, c->boats[i]->name) == 0){
            return c->boats[i];
        }
    }
    return NULL;
}

int resize_boats(struct club * c){
    size_t new_cap = c->boats_cap * 2;
    struct boat ** temp = realloc(c->boats, sizeof(struct boat *) * new_cap);

    if(temp == NULL) return 0;
    c->boats = temp;
    c->boats_cap = new_cap;
    return 1;
}

int resize_mems(struct club * c){
    size_t new_cap = c->mems_cap * 2;
    struct person ** temp = realloc(c->mems, sizeof(struct person *) * new_cap);

    if(temp == NULL) return 0;
    c->mems = temp;
    c->mems_cap = new_cap;
    return 1;
}

// adds a boat with the given name and maximum crew size to club c.
// Within a club, boats are uniquely identified by name. A boat with a maximum crew of four can
// take between one and four persons on an excursion. Return 1 on success. Return 0 on error or if
// resources are exhausted. It is an error to add two boats with the same name in the same club. It is
// also an error to have a maximum crew size less than 1
int add_boat (struct club * c, const char * boat_name, unsigned int crew_size){
    if(c == NULL || boat_name == NULL) return 0;
    if(find_boat(c, boat_name) != NULL) return 0;
    if(crew_size < MIN_CREW) return 0;


    struct boat * new_boat = malloc(sizeof(struct boat));
    if(new_boat == NULL) return 0;
    size_t name_len = strlen(boat_name); // HERE MAYBE ADD +1
    new_boat->name = malloc(sizeof(char) * name_len);
    if(new_boat->name == NULL) return 0;
    strcpy(new_boat->name, boat_name);
    new_boat->max_crew = crew_size;
    new_boat->cur_crew = 0;
    new_boat->is_busy = 0;       // initialy is 0, means not busy
    new_boat->distance = 0;
    new_boat->exc_count = 0;

    c->boats[c->boats_count] = new_boat;
    c->boats_count += 1;
    if(c->boats_count >= c->boats_cap){
        int res = resize_boats(c);
        if(res == 0) return 0;
    } 

    return 1;
}

struct person * find_pers(struct club * c, char * pers_name){
    for(int i = 0; i < c->mems_count; ++i){
        if(strcmp(pers_name, c->mems[i]->name) == 0){
            return c->mems[i];
        }
    }
    return NULL;
}

// adds a person to club c. Persons are also identified uniquely by name within
// a club. It is therefore an error to add two persons with the same name in the same club. Return 1 on success or 0 on error
int add_person (struct club * c, const char * pers_name){
    if(c == NULL || pers_name == NULL) return 0;
    if(find_pers(c, pers_name) != NULL) return 0;

    struct person * new_pers = malloc(sizeof(struct person));
    if(new_pers == NULL) return 0;
    size_t name_len = strlen(pers_name);
    new_pers->name = malloc(sizeof(char) * name_len); // MAYBE +1
    strcpy(new_pers->name, pers_name);
    if(new_pers->name == NULL) return 0;
    new_pers->exc = NULL;   // initially is NULL, means is not busy
    new_pers->exc_count = 0;
    new_pers->distance = 0;

    c->mems[c->mems_count] = new_pers;
    c->mems_count += 1;
    if(c->mems_count >= c->mems_cap){
        int res = resize_mems(c);
        if(res == 0) return 0;
    }
    return 1;
}

// create an excursion object to prepare an excursion within club c. Return a valid
// pointer to a new excursion object. Return the null pointer if memory is exhausted and therefore
// the creation of a new excursion object fails.
struct excursion * create_excursion (struct club * c){
    if(c == NULL) return NULL;
    struct excursion * new_exc = malloc(sizeof(struct excursion));
    if(new_exc == NULL) return NULL;
    new_exc->c = c;
    new_exc->sel_boat = NULL;
    return new_exc;
}

// assigns the named boat to the excursion e. Return 1 on success. In this case, the
// boat remains assigned to the excursion until the excursion is closed or canceled. Return 0 if the
// boat does not exist or is not available because it is currently assigned to another excursion.
int use_boat (struct excursion * exc, const char * boat_name){
    if(exc == NULL || boat_name == NULL) return 0;

    // CHECK IF EXC ALREADY HAS A BOAT
    struct boat * b_found = exc->sel_boat;
    if(b_found != NULL) return 0;     // if exc already has a boat

    // // CHECK IF BOAT EXISTS IN THE CLUB AND IS NOT BUSY
    struct boat * b = find_boat(exc->c, boat_name);
    if(b == NULL) return 0;             // means boat does not exist
    if(b->is_busy == 1) return 0;        // means boat is busy

    // // ASSIGN BOAT TO EXC AND MARK BOAT AS BUSY
    b->is_busy = 1; 
    exc->sel_boat = b;
    
    return 1;
}

// assigns the named person as a crew member for the excursion e. Return 1 on
// success. In this case, the person is assigned and remains assigned to the given excursion until
// that excursion is canceled or closed. Return 0 if the excursion does not yet have an assigned boat,
// or if the maximum crew capacity of the boat has already been reached, or if the named person
// does not belong to the club, or if the named person has already been added to the crew of another
// excursion
int add_crew(struct excursion * exc, const char * pers_name){
    if(exc == NULL || pers_name == NULL) return 0;

    // CHECK IF EXC HAS A BOAT
    struct boat * b_found = exc->sel_boat;
    if(b_found == NULL) return 0;      // if exc does not have a boat

    //CHECK IF PERSON EXISTS IN THE CLUB AND IS NOT BUSY
    struct person * p = find_pers(exc->c, pers_name);
    if(p == NULL) return 0;         // person is not a member
    if(p->exc != NULL) return 0;    // means it has an exc

    // NEED TO INCREASE CURRENT CREW FOR THE BOAT, CHECK IF MORE THAN MAX_CREW
    b_found->cur_crew += 1;
    if(b_found->cur_crew > b_found->max_crew) return 0;

    // SET EXC FOR THE PERSON
    p->exc = exc;
    return 1;
}

struct person * exc_find_pers(struct excursion * exc){
    struct club * c = exc->c;
    for(int i = 0; i < c->mems_count; ++i){
        if(c->mems[i]->exc == exc){
            return c->mems[i];
        }
    }
    return NULL;
}

// confirms that the given excursion has ended successfully with the given distance k traveled (in kilometers). 
// The excursion object e is also destroyed and all its allocated
// resources are properly released. Return 1 on success. Return 0 when the given excursion has not
// been set up properly, with a valid boat and a crew of at least one person. In this case, the excursion
// object remains valid.
int close_excursion (struct excursion * exc, unsigned int distance){
    if(exc == NULL) return 0;

    // CHECK IF HAS VALID BOAT AND AT LEAST ONE CREW MEMBER
    struct boat * sel_boat = exc->sel_boat;
    if(sel_boat == NULL) return 0;
    if(sel_boat->cur_crew < 1) return 0;

    // MAKE BOAT NOT BUSY AND INCREASE STATS, REFRESH CREW COUNT
    sel_boat->is_busy = 0;
    sel_boat->cur_crew = 0;
    sel_boat->distance += distance;
    sel_boat->exc_count += 1;

    // FIND ALL CREW MEMBERS, MAKE THEM NOT BUSY AND INCREASE STATS
    struct person * pers = exc_find_pers(exc);
    while(pers != NULL){
        pers->exc = NULL;
        pers->distance += distance;
        pers->exc_count += 1;
        pers = exc_find_pers(exc);
    }

    return 1;
}

// the given excursion is canceled. The excursion object e is properly destroyed;
// all its allocated resources are released
void cancel_excursion (struct excursion * exc){
    struct boat * sel_boat = exc->sel_boat;
    if(sel_boat == NULL) return;
    sel_boat->is_busy = 0;
    sel_boat->cur_crew = 0;

    struct person * pers = exc_find_pers(exc);
    while(pers != NULL){
        pers->exc = NULL;
        pers = exc_find_pers(exc);
    }

    //free(exc);
}

// return the number of excursions made by the given member of the
// club. Return −1 in case of error, for example if the given person does not belong to the club.
int get_crew_excursions (struct club * c, const char * pers_name){
    if(c == NULL || pers_name == NULL) return -1;

    struct person * p = find_pers(c, pers_name);
    if(p == NULL) return -1;
    return p->exc_count;
}

// return the total number of kilometers traveled in completed excursions made by the given member of club c.
//  Return −1 in case of error, for example if the given
// person does not belong to the club.
int get_crew_kilometers (struct club * c, const char * pers_name){
    if(c == NULL || pers_name == NULL) return -1;

    struct person * p = find_pers(c, pers_name);
    if(p == NULL) return -1;
    return p->distance;
}

//  return 1 if the boat is available, or 0 if it is not available. Return −1 in case
// of error, if the given named boat does not exist in club c.
int boat_available (struct club * c, const char * boat_name){
    if(c == NULL || boat_name == NULL) return -1;

    struct boat * b = find_boat(c, boat_name);
    if(b == NULL) return -1;
    if(b->is_busy == 0) return 1;
    else return 0;
}
// return the number of excursions made with the given boat of club c.
// Return −1 in case of error, if club c does not have the given boat.
int get_boat_excursions (struct club * c, const char * boat_name){
    if(c == NULL || boat_name == NULL) return -1;

    struct boat * b = find_boat(c, boat_name);
    if(b == NULL) return -1;
    return b->exc_count;
}
// return the number of kilometers traveled with the given boat of club
// c. Return −1 in case of error, if club c does not have the given boat.
int get_boat_kilometers (struct club * c, const char * boat_name){
    if(c == NULL || boat_name == NULL) return -1;

    struct boat * b = find_boat(c, boat_name);
    if(b == NULL) return -1;
    return b->distance;
}