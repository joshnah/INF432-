#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "macros.h"
#include "grid.h"

/*****************************/
//This file is for calculating intersection grid//


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

typedef struct Linked_list_intersection_box
{
    int nb_box;
    Cell_intersection *first;
}Linked_list_intersection_box;


void add_territory(Cell_intersection* l, int territory);

Cell_intersection* new_cell_intersection();
void print_list_intersection(Linked_list_intersection_box *L);

void add_cell_intersection(Cell_intersection *Ci, Linked_list_intersection_box *L);

Linked_list_intersection_box init_list_intersection();

void free_cell_intersection(Cell_intersection *C);


#endif