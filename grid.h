#ifndef _GRID_H_
#define _GRID_H_

/* positive numbers */
typedef unsigned int UINT;

/* Black box is a box with bomb, otherwise white box */
typedef enum {BLACK=1, WHITE=0} Box;

/* Coordinate of a box */
typedef struct Coordinate
{
    int x;
    int y;
} Coordinate;
 
/* Information of a grid */
typedef struct Grid
{
    UINT L,H;
    Box *tab;
} Grid;

/* Rectangle of boxes */
typedef struct Rectangle
{
    Coordinate C1;
    Coordinate C2;
} Rectangle;

/* Initialize a grid with all cases white */
Grid init_grid(UINT L, UINT H);


/* The function return the value in the box (x,y) */
Box get_box(Grid G, int x, int y);

/* The function set the value in the box (x,y) */
void set_box(Grid G, int x, int y, Box b);

/* Return the length of grid */
UINT length_grid(Grid G);

/* return the height of the grid */
UINT height_grid(Grid G);

/* Display the grid in the stdout */
void display_grid(Grid G);







#endif