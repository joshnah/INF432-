#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "macros.h"
#include "grid.h"


/* A structure to store information of territories*/
typedef struct Cell_territory
{
    int val;
    struct Cell_territory* next;
} Cell_territory;

typedef struct Cell_intersection
{
    int nb_territory;
    Cell_territory *list_of_territory;
    Coordinate C;
    struct Cell_intersection *next;
} Cell_intersection;


/* A linked list of intersection boxes */
typedef struct Linked_list_intersection_box
{
    
    int nb_box;
    Cell_intersection *first;

}   Linked_list_intersection_box;



/* Add a territory into the list */
void add_territory(Cell_intersection* l, int territory);

/* Initialize a new element in the list of intersection */
Cell_intersection* new_cell_intersection();

/* Display information about the list of intersection boxes */
void print_list_intersection(Linked_list_intersection_box *L);

/* Add an element to the list of intersection boxes */
void add_cell_intersection(Cell_intersection *Ci, Linked_list_intersection_box *L);

/* Initialize a new list of intersection boxes */
Linked_list_intersection_box init_list_intersection();

/* Free memory of a list of intersection boxes */
void free_cell_intersection(Cell_intersection *C);


#endif