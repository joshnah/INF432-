#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territory.h"
#include "grid.h"
#include "intersection.h"
#include "macros.h"
#include "rules.h"




int main(int argc, char *argv[])
{
    int dim;
    int nb_territory;
    FILE *f,*g;


    /*********************** READING INPUT ***********************/
    f = fopen(argv[1], "r");
    if (f == NULL)
        ERREUR_FATALE("Error argument!");

    fscanf(f, "%d", &dim);
    fscanf(f, "%d", &nb_territory);


    Territory list_territory[nb_territory];
    /* Grid of availability */
    Grid A = read_input(f, &nb_territory, dim, list_territory);

    printf("************************\n\n");
    
    // Print out a normal grid with territories
    Grid G = Extract_Grid(list_territory, nb_territory, dim);
    printf("Grid of territories\n");
    printf("We dont show the territory 0 in this grid \n\n");

    display_grid(G);


    printf("************************\n\n");
    printf("Grid of availability\n");
    display_grid_availability(A);


    printf("************************\n\n");

    Linked_list_intersection_box List_intersection = init_list_intersection();
    extract_list_intersection(&List_intersection, list_territory, nb_territory, G);
    print_list_intersection(&List_intersection);


    printf("************************\n\n");
  
    extract_list_availability(list_territory, nb_territory, A);
    display_all_territories(list_territory, nb_territory);

    printf("Number of clauses : %d \n", nb_clauses(list_territory, nb_territory, &List_intersection));

    /****************** RULE 1 ****************/

    g = fopen("output.txt","w");
    translate_rule3(g, list_territory, nb_territory, &List_intersection);
}
