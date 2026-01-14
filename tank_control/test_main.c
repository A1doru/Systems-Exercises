#include "tank_control.h"
#include <stdio.h>

int	main()
{
    add(90300);
	int amount = ship_out_bottles();
    printf("%d\n", amount);
    printf("%d\n", get_tank_level());
}

