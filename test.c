/********************************/
/* This program is used for testing functions */

#include "intersection.h"
#include "grid.h"


int main()
{
    Grid G = init_grid(5);
    set_box(G, 2,2 ,4);
    display_grid(G);
    return 0;
}