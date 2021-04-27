#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

Linked_list_intersection_box init_list_intersection()
{
    Linked_list_intersection_box L;

    L.first =NULL;

    L.nb_box = 0;

    return L;
}

Cell_territory* new_cell_territory(int territory)
{
    Cell_territory* new = malloc(sizeof(Cell_territory));

    new->val = territory;

    new->next = NULL;

    return new;
};  

Cell_intersection* new_cell_intersection()
{
    Cell_intersection *new_list = malloc(sizeof(Cell_intersection));

    new_list->list_of_territory = NULL;

    new_list->next = NULL;

    new_list->nb_territory = 0;

    return new_list;
};

void add_territory(Cell_intersection* l, int territory)
{
    Cell_territory* elem = new_cell_territory(territory);

    if (l->list_of_territory == NULL)
    {
        l->list_of_territory = elem;
    }

    else
    {
        elem->next = l->list_of_territory;
        l->list_of_territory = elem;
    }

    l->nb_territory++;
}

void add_cell_intersection(Cell_intersection *Ci, Linked_list_intersection_box *L)
{
    if ( L->first == NULL)
        L->first = Ci;

    else
    {
        Ci->next = L->first;
        L->first = Ci;
    }

    L->nb_box++;

    
}

void print_list_intersection(Linked_list_intersection_box *L)
{
    printf("List of intersection boxes:\n\n");

    Cell_intersection *temp = L->first;
    Cell_territory *temp_Territory;
    int i;

    for (i = 0; i < L->nb_box; i++)
    {
        temp_Territory = temp ->list_of_territory;

        printf("Box %d ---- Coordinate: (%d, %d) ---- Territories: ", i, temp->C.x, temp->C.y);
        
        while (temp_Territory != NULL)
        {
            printf("%d", temp_Territory->val);

            temp_Territory = temp_Territory->next;
        }

        temp = temp->next;

        printf("\n");
    }

    printf("\n");
    
}

void free_cell_intersection(Cell_intersection *C)
{
    Cell_territory * ct = C->list_of_territory;
    Cell_territory *next;
    
    while (ct != NULL)
    {
        next = ct->next;
        free(ct);
        ct = next;
    }
    free(C);
}