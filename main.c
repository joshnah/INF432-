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
    extract_list_intersection(&List_intersection, list_territory, nb_territory, G,A);
    print_list_intersection(&List_intersection);


    printf("************************\n\n");
  
    extract_list_availability(list_territory, nb_territory, A);
    display_all_territories(list_territory, nb_territory);


    int number_clauses = nb_clauses(list_territory, nb_territory, &List_intersection);
    printf("Number of clauses : %d \n", number_clauses);

    g = fopen("output.cnf","w");
    fprintf(g, "p cnf %d %d\n", list_territory[nb_territory-1].I.b, number_clauses);


    translate_rule1_2(g, list_territory, nb_territory);
    translate_rule3(g, list_territory, nb_territory, &List_intersection);

    fclose(f);
    fclose(g);


    Grid R = init_grid(dim);
    //system("./picosat output.cnf");
    d = popen("./picosat output.cnf","r");

    printf("\n");
    char *p;
    char c;
    fscanf(d, "%*c %c", &c);
    if (c == 'U')
    {
        printf("Program is unsatifiable!!\n");
        return 0;
    }

    printf("Program is satifiable!!\n");
    fscanf(d,"%*s \n");
    int a;
    cell_coordinate *temp;

    while (fgets(buffer, 100, d) != NULL)
    {
        p = strstr(buffer, " ") + 1;
        while (p!= NULL)
        { 
            a = atoi(p);
            if (a > 0 )
            {
                temp = Mark_bomb(R, a, list_territory, nb_territory);
                set_box(R, temp->C.x, temp->C.y,1);
            }
            p = strstr(p+1, " " );
        }
    }


    printf("************************\n\n");
    printf("GRID RESULT:\n");
    display_grid(R);
}
