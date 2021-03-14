#ifndef _TERRITORY_H_
#define _TERRITORY_H_
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct interval
{
    int a;
    int b;
} Interval;

typedef struct territory
{
    int index;    /* the n-th marked box in the grid */
    int nb_bomb;
    Interval I;        /* intervall I = [a,b] when naming the variables */
    Coordinate O;   /* Coordinate of the center box */
    int size;       /* Number of boxes in the territory */  
    Rectangle area;  /* Area of the terriory */

} Territory;

/* Read the input of the file into a list of territories */
void read_input(FILE *f, int nb_territory, int dim, Territory list_territory[]);

/* Display the information of all territories */
void display_all_territories(Territory list[], int nb_territory);

/* Return a rectangle of area of a territory */
Rectangle area_territory(Coordinate O, int dim);


#endif
