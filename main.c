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

    /* Check the existence of the arguments */
    if (argc == 3)
    {

        int i = 0;

        while (argv[2][i] != '\0')
        {
            switch (argv[2][i])
            {
            /* display */
            case 'd':
                display = 1;
                break;

            /* sat 3 */
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
        ERREUR_FATALE("Error input file name!");

    fscanf(f, "%d", &dim);

    if ( dim == 0)
        ERREUR_FATALE("DIMENSION 0!");

    fscanf(f, "%d", &nb_territory);

    if (nb_territory > dim * dim)
        ERREUR_FATALE("TOO MANY TERRITORIES!");

    Territory list_territory[nb_territory];

    /* Grid for displaying territories */
    Grid G = init_grid(dim, -1);

    /* Grid A is grid of availability */
    /* Storing information of all territories */
    Grid A = read_input(f, &nb_territory, dim, list_territory, &G);


    /***********************  INTERSECTION BOXES ***********************/

    Linked_list_intersection_box List_intersection = init_list_intersection();

    extract_list_intersection(&List_intersection, list_territory, nb_territory, G,A);



    /***********************  GRID OF AVAILABILITY ***********************/

    extract_list_availability(list_territory, nb_territory, A);

    


    /*********************** NUMBER OF CLAUSES ***********************/

    int number_clauses = nb_clauses(list_territory, nb_territory, &List_intersection);



    /*********************** WRITING OUTPUT FILE ***********************/

    int nb_variable = list_territory[nb_territory-1].I.b;
    g = fopen("output.cnf","w");
    fprintf(g, "p cnf %d %d\n", nb_variable, number_clauses);

    translate_rule1_2(g, list_territory, nb_territory);
    translate_rule3(g, list_territory, nb_territory, &List_intersection);

    fclose(f);
    fclose(g);


    /*********************** GRID OF TERRITORY ***********************/


    printf("Grid of territories\n");

    display_grid_territories(G); 


    /***********************  DISPLAY INFORMATION ***********************/

    if (display == 1)
    {


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

    printf("************************\n\n");
    printf("By Picosat:\n\n");

    Grid R = init_grid(dim,0);
    int result = result_grid(d, list_territory, nb_territory, dim, &R);

    if (result == 1)
    {
        printf("\nInitially:\n");
        display_grid_territories(G);

        printf("\nGRID RESULT:\n");
        display_grid(R);
    }


    fclose(d);

    /*********************** CONVERT TO 3-SAT ***********************/

    // Call the program to translate to 3-SAT
    // the new 3sat file will be "output3sat.cnf"
    if (sat3 == 1 )
    {
        system("./sat3 output.cnf");
    
    

    printf("************************\n\n");
    printf("BY our SAT-SOLVER:\n");

    /*********************** OUR SAT SOLVER ***********************/
     d = popen("./walksat output3sat.cnf","r");



    Grid R3 = init_grid(dim,0);
    result = result_sat3(d, list_territory, nb_territory, dim, &R3,nb_variable );


    if (result == 1)
    {
        printf("\nInitially:\n");
        display_grid_territories(G);

        printf("\nGRID RESULT:\n");
        display_grid(R3);
    } 
}
}