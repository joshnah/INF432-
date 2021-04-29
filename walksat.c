#include "clause.h"

#define MAX_ITERATION 1000000

int main(int argc, char **argv)
{
    FILE *f;
    f = fopen(argv[1], "r");

    int nb_clause, nb_variable;

    fscanf(f,"p cnf %d %d\n", &nb_variable, &nb_clause);

    int i,a;
    clause B;
    tab_clause T = init_tab_clause(nb_clause);

    /* READING INPUT DIMACS FILE */
    /* STORING ALL CLAUSES INTO AN ARRAY */

    for ( i = 0; i < nb_clause; i++ )
    {
        B = init_buffer(3);
        fscanf(f, "%d ", &a);
        while (a != 0)
        {
            B.tab[B.index++] = a;
            fscanf(f, "%d", &a);
        }
        T.tab[T.size++] = B;
        
    }
    fclose(f);


    /* Choose randomly an assignment */
    int assignment[nb_variable];
    
    random_assignment(assignment, nb_variable);


    /* Initialization of array of times flipping and occurences of each variable*/
    int tab_inverse[nb_variable];

    occurence tab_occurence[nb_variable];

    fill_tab_occurence_inverse(tab_occurence, tab_inverse, nb_variable, T);


    clause C = init_buffer(3);
    
    int step = 0;

    int var,uni_ran;

    double x;




    while ( step++ < MAX_ITERATION && (check_model(assignment, T) == 0))
    {

        /* Choose randomly a false clause */
        C = random_false_clause(assignment, T);

        /* Choose uniformaly a value between 0 and 1 */
        x = drand48();

        /* 50% choosing randomly a variable */
        if (x < 0.6)
        {
            uni_ran = uniform_distribution(3);
            var = abs(C.tab[uni_ran]) - 1;
        }

        /* 20% choosing a variable with least flip times */
        else if (x < 1)
            var = pickvar_flip(tab_inverse,nb_variable);


        /* 30% choosing a variable based on number of occurences */
        else 
        {
            var = pickvar_occ(tab_occurence, nb_variable, assignment, T);
        } 

        inverse_variable(assignment, tab_inverse, var,tab_occurence);


    }

    /* The program could not find the solution */
    if (step == MAX_ITERATION + 1)
    {
        printf("s UNSATIFIABLE");
        return(-1);
    }

    /* The program is able to find a solution */

    printf("s SATIFIABLE\n");

    /* Print out all the variables */

    for (i = 0; i < nb_variable; i++)
    {
        if (assignment[i] == 1)
            printf("%d ", i+1);
        else   
            printf("-%d ",i+1 );
    }

    printf("0\n");

}
