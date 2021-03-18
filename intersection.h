#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "macros.h"

/*****************************/
//This file is for calculating intersection grid//


typedef struct Cell_intersection
{
    int val;
    struct Cell_intersection* next;
} Cell_intersection;

typedef struct List_intersection_f
{
    int number;
    Cell_intersection *head;
} List_intersection_f;

typedef List_intersection_f* List_intersection;   // pointeur

typedef struct Grid_intersection
{
    int dim;
    List_intersection* tab;
} Grid_intersection;

Grid_intersection init_Grid_intersection(int dim);


/* Return a pointeur to a list of intersection */
List_intersection get_List_intersection(Grid_intersection G, int x, int y);


/* Add a territory to a list in the grid */
void add_territory(Grid_intersection G, int x, int y, int territory);

void display_grid_intersection(Grid_intersection G, int max);



void free_list_intersection(List_intersection *l);



#endif