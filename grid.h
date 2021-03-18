#ifndef _GRID_H_
#define _GRID_H_
#include "macros.h"

/* positive numbers */
typedef unsigned int UINT;

/* The value is from 0 to 9 */
typedef unsigned int Box;

/* Coordinate of a box */
typedef struct Coordinate
{
    int x;
    int y;
} Coordinate;
 
/* Information of a grid with only boxes of bomb or non-bomb */
typedef struct Grid
{
    int dim;
    Box *tab;
} Grid;

/* Rectangle of boxes in a territory */
typedef struct Rectangle
{
    Coordinate C1;
    Coordinate C2;
} Rectangle;

/* Initialize a grid with all cases white */
Grid init_grid(int dim);


/* The function return the value in the box (x,y) */
Box get_box(Grid G, int x, int y);

/* The function set the value in the box (x,y) */
void set_box(Grid G, int x, int y, Box b);

/* Display the grid in the stdout */
void display_grid(Grid G);







#endif