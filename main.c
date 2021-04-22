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
    int display = 0, sat3 = 0; // flags for displaying information and conversion to sat3


    /*********************** ERROR INPUT ***********************/

    if (argc != 3 && argc != 2)
        ERREUR_FATALE("Usage: ./main <input_file> <arguments>\n");

    if (argc == 3)
    {
        int i = 0;
        while (argv[2][i] != '\0')
        {
            switch (argv[2][i])
            {
            case 'd':
                display = 1;
                break;
            case 's':
                sat3 = 1;
                break;
            default:
                ERREUR_FATALE("Erreur arguments! 'd' : display, 's' : convert sat3\n")
                break;
            }
            i++;
        }
    }

    /*********************** READING INPUT ***********************/

    f = fopen(argv[1], "r");
    if (f == NULL)
        ERREUR_FATALE("Error input file!");

    fscanf(f, "%d", &dim);
    fscanf(f, "%d", &nb_territory);


    Territory list_territory[nb_territory];
    Grid A = read_input(f, &nb_territory, dim, list_territory);



    printf("************************\n\n");
    
    /*********************** GRID OF TERRITORY ***********************/


    Grid G = Extract_Grid(list_territory, nb_territory, dim);


    /***********************  INTERSECTION BOXES ***********************/

    Linked_list_intersection_box List_intersection = init_list_intersection();
    extract_list_intersection(&List_intersection, list_territory, nb_territory, G,A);



    /***********************  GRID OF AVAILABILITY ***********************/

    extract_list_availability(list_territory, nb_territory, A);

    



    /*********************** NUMBER OF CLAUSES ***********************/

    int number_clauses = nb_clauses(list_territory, nb_territory, &List_intersection);



    /*********************** WRITING OUTPUT FILE ***********************/


    g = fopen("output.cnf","w");
    fprintf(g, "p cnf %d %d\n", list_territory[nb_territory-1].I.b, number_clauses);

    translate_rule1_2(g, list_territory, nb_territory);
    translate_rule3(g, list_territory, nb_territory, &List_intersection);

    fclose(f);
    fclose(g);



    /***********************  DISPLAY INFORMATION ***********************/

    if (display == 1)
    {
        /*********************** GRID OF TERRITORY ***********************/

    
        printf("Grid of territories\n");
        printf("We dont show the territory 0 in this grid \n\n");

        display_grid_territories(G);


        /***********************  GRID OF AVAILABILITY ***********************/

        printf("************************\n\n");
        printf("Grid of availability\n");
        display_grid_availability(A);


        printf("************************\n\n");



        /***********************  INTERSECTION BOXES ***********************/

        print_list_intersection(&List_intersection);


        printf("************************\n\n");
  

        /***********************  ALL TERRITORIES ***********************/

        display_all_territories(list_territory, nb_territory);


        /*********************** NUMBER OF CLAUSES ***********************/

        printf("Number of clauses : %d \n\n", number_clauses);

        
    }



    /*********************** DISPLAY RESULT ***********************/

    // popen is a function of call another program C (here we will call the sat solver)
    // d is a FILE pointer to the output of the call
    d = popen("./picosat output.cnf","r");

    Grid R = init_grid(dim,0);
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
    if (sat3 == 1 )
    {
        system("./sat3 output.cnf");
    }
    


}
