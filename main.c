#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territory.h"
#include "grid.h"
#include "intersection.h"
#include "macros.h"
#include "rules.h"


char buffer[100];


int main(int argc, char *argv[])
{
    int dim;
    int nb_territory;
    FILE *f,*g,*d;


    /*********************** READING INPUT ***********************/

    f = fopen(argv[1], "r");
    if (f == NULL)
        ERREUR_FATALE("Error argument!");

    fscanf(f, "%d", &dim);
    fscanf(f, "%d", &nb_territory);


    Territory list_territory[nb_territory];
    Grid A = read_input(f, &nb_territory, dim, list_territory);



    printf("************************\n\n");
    
    /*********************** GRID OF TERRITORY ***********************/

    Grid G = Extract_Grid(list_territory, nb_territory, dim);
    printf("Grid of territories\n");
    printf("We dont show the territory 0 in this grid \n\n");

    display_grid(G);

    


    /***********************  GRID OF AVAILABILITY ***********************/

    printf("************************\n\n");
    printf("Grid of availability\n");
    display_grid_availability(A);


    printf("************************\n\n");




    /***********************  INTERSECTION BOXES ***********************/

    Linked_list_intersection_box List_intersection = init_list_intersection();
    extract_list_intersection(&List_intersection, list_territory, nb_territory, G,A);
    print_list_intersection(&List_intersection);


    printf("************************\n\n");
  
    extract_list_availability(list_territory, nb_territory, A);
    display_all_territories(list_territory, nb_territory);

    



    /*********************** NUMBER OF CLAUSES ***********************/

    int number_clauses = nb_clauses(list_territory, nb_territory, &List_intersection);
    printf("Number of clauses : %d \n\n", number_clauses);




    /*********************** WRITING OUTPUT FILE ***********************/


    g = fopen("output.cnf","w");
    fprintf(g, "p cnf %d %d\n", list_territory[nb_territory-1].I.b, number_clauses);

    translate_rule1_2(g, list_territory, nb_territory);
    translate_rule3(g, list_territory, nb_territory, &List_intersection);

    fclose(f);
    fclose(g);



    /*********************** DISPLAY RESULT ***********************/

    // popen is a function of call another program C (here we will call the sat solver)
    // d is a FILE pointer to the output of the call
    d = popen("./picosat output.cnf","r");

    Grid R = init_grid(dim);
    int result = result_grid(d, list_territory, nb_territory, dim, &R);

    if (result == 1)
    {
        printf("************************\n\n");
        printf("GRID RESULT:\n");
        display_grid(R);
    }


    fclose(d);

    /*********************** CONVERT TO 3-SAT ***********************/

    // Call the program to translate to 3-SAT
    // the new 3sat file will be "output3sat.cnf"
    system("./sat3 output.cnf");


}
