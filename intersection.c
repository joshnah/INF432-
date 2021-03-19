#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"


Grid_intersection init_Grid_intersection(int dim)
{
    Grid_intersection G;
    G.dim = dim;
    G.tab = (List_intersection*)malloc(sizeof(List_intersection) * dim * dim );

    int i;
    for (i=0; i < dim*dim; i++)
    {
        G.tab[i] = NULL;
    }
    return G;
};

List_intersection get_List_intersection(Grid_intersection G, int x, int y)
{
 	if (x<1 || x>G.dim || y<1 || y>G.dim)
		return NULL;
	return G.tab[INDICE(G,x,y)];   
};

void set_List_intersection(Grid_intersection G, int x, int y, List_intersection l)
{
    if (x<1 || x>G.dim || y<1 || y>G.dim)
		return;
    G.tab[INDICE(G,x,y)] = l;  
};

Cell_intersection* new_cell(int val)
{
    Cell_intersection* new = malloc(sizeof(Cell_intersection));
    new->val = val;
    new->next = NULL;
    return new;
};

List_intersection new_list_intersection()
{
    List_intersection new_list = malloc(sizeof(List_intersection_f));
    new_list->number = 0;
    new_list->head = NULL;
    return new_list;
};

void add_to_the_head(List_intersection l, int territory)
{
    Cell_intersection* elem = new_cell(territory);
    if (l->head == NULL)
    {
        l->head = elem;
    }
    else
    {
        elem->next = l->head;
        l->head = elem;
    }
    l->number++;
}

void add_territory(Grid_intersection G, int x, int y, int territory)
{
    List_intersection list_intersec = get_List_intersection(G, x,y);
    if (list_intersec == NULL)
    {       
        List_intersection new_list_intersec = new_list_intersection();
        add_to_the_head(new_list_intersec, territory);
        set_List_intersection(G, x,y, new_list_intersec);
    }
    else
        add_to_the_head(list_intersec, territory);
    
}

/* Print nb number spaces */
void print_space(int nb)
{
    int i;
    for (i = 0; i < nb; i++)
        printf(" ");
}

/* Print out a list of intersection */
void print_list_intersection(List_intersection l, int max)
{
    Cell_intersection *cell = l->head;
    while (cell != NULL)
{
        printf("%d", cell->val);
        cell= cell->next;
}
    print_space(max - l->number + 1);
}

void display_grid_intersection(Grid_intersection G, int max)
{
    List_intersection l;
    int x,y;
    for (y = 1; y <= G.dim; y++)
	{
		for ( x = 1; x <= G.dim; x++)
		{
            l = get_List_intersection(G,x,y);
            if (l == NULL)
            {
                printf("0");
                print_space(max );
            }
            else 
                print_list_intersection(l, max);
		}
		printf("\n");
	}   
}


void free_list_intersect_r(Cell_intersection *n)
{
    if (n == NULL)
        return;
    free_list_intersect_r(n->next);
    free(n);
}

void free_list_intersection(List_intersection *l)
{
    if (*l == NULL)
        return;
    free_list_intersect_r((*l)->head);
    free(*l);
    *l = NULL;
}



