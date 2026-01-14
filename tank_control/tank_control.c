/*
    1) Tank is temporal storage for liquids.
    2) Capacity is 1million ml or 1000 liters.
    3) Use ml
    4) change_tank(c) <-- new tank with capacity c, fills with 
    5) add(c)

*/



#include "tank_control.h"

unsigned int current_capacity = 1000000;
unsigned int current_content = 0;
unsigned int waste = 0;
unsigned int bottle_capacity = 750;


/*
    Resets capacity, content and waste
*/
void clear(){
    current_capacity = 1000000;
    current_content = 0;
    waste = 0;
    bottle_capacity = 750;
}

/*
    Changes capacity of bottle
*/
void change_bottle_capacity(unsigned int c){
    bottle_capacity = c;
}

/*
    Puts new tank with new capacity, content of old tank is transfered to new.
    If exceeds new capacity, then goes to waste.
*/
void change_tank(unsigned int c){
    int new_waste = current_content - c;
    if(new_waste > 0){
        waste += new_waste;
        current_content = c;
    }
    current_capacity = c;
}

/*
    Adds liquid to the tank. If exceed, then goes to waste.
*/
void add(unsigned int c){
    current_content += c;
    if(current_content > current_capacity){
        waste += current_content - current_capacity;
        current_content = current_capacity;
    }
}

unsigned int ship_out_bottles(){
    unsigned int bottles_amount = current_content / bottle_capacity;
    current_content -= (bottles_amount * bottle_capacity);
    return bottles_amount;
}
 
unsigned int get_wastes(){
    return waste;
}

unsigned int get_tank_level(){
    return current_content;
}