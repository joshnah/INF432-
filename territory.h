#ifndef _TERRITORY_H_
#define _TERRITORY_H_
#include "grid.h"


typedef struct territory
{
    int index;    /* the n-th marked box in the grid */
    int nb_bomb;
    int a;
    int b;          /* intervall [a,b] when naming the variables */
    Coordinate O;   /* Coordinate of the center box */
    int size;       /* Number of boxes in the territory */  
} Territory;



    


#endif
