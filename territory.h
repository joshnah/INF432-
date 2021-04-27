#ifndef _TERRITORY_H_
#define _TERRITORY_H_
#include "grid.h"
#include "intersection.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* An interval [a,b] */
typedef struct interval
{
    int a;
    int b;
} Interval;

/* Structure of a list of coordinates */
typedef struct cell_coordinate
{
    Coordinate C;
    struct cell_coordinate *next;
} cell_coordinate;

typedef struct list_coordinate
{
    cell_coordinate* first;
    int nb_points;
}
 list_coordinate;



/* Structure to store information of territories */
typedef struct territory
{
    int index;                  /* the n-th marked box in the grid */
    int nb_bomb;
    Interval I;                 /* intervall I = [a,b] when naming the variables */
    Coordinate O;               /* Coordinate of the center box */
    int size;                   /* Number of boxes in the territory */  
    Rectangle area;             /* Area of the terriory */
    list_coordinate *list_box;          /* list of avaliable boxes */   

} Territory;




/* Read the input of the file into a list of territories and a grid of territories G and return a grid of availability */
Grid read_input(FILE *f, int *nb_territory,int dim, Territory list_territory[], Grid *G);

/* Display the information of all territories */
void display_all_territories(Territory list[], int nb_territory);

/* Return a rectangle of area of a territory */
Rectangle area_territory(Coordinate O, int dim);

/* Create a grid with the information from a list of territory */
Grid Extract_Grid(Territory list[], int nb_territory, int dim);

/* Create a list of intersection */
void extract_list_intersection(Linked_list_intersection_box *L, Territory list[], int nb_territory, Grid G, Grid A);

/* Calculate the number of clauses */
int nb_clauses(Territory list[], int nb_territory, Linked_list_intersection_box *L);

/* Extract a list of all the boxes availables (not in the area of territory 0 bombs) */
void extract_list_availability(Territory list[], int nb_territory, Grid Avai);

/* Set bomb in a box in the grid of result */
cell_coordinate* Mark_bomb(Grid G, int var, Territory list[], int nb_territory);

/* Read the output of sat_solver and return 0 if the program is unsatisfiable, 1 else */
int result_grid(FILE * d, Territory list[], int nb_territory, int dim, Grid* R);

/* Read the output of our sat_sover. Return 0 if the program is unsatifiable, 1 else */
int result_sat3(FILE * d, Territory list[], int nb_territory, int dim, Grid* R, int nb_variable);



#endif
