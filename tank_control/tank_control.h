#ifndef TANK_CONTROL_H_INCLUDED
#define TANK_CONTROL_H_INCLUDED

extern void clear();

extern void change_bottle_capacity(unsigned int c);
extern void change_tank(unsigned int c);

extern void add(unsigned int c);
extern unsigned int ship_out_bottles();

extern unsigned int get_wastes();
extern unsigned int get_tank_level();

#endif
