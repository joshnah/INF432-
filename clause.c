#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "clause.h"

#define abs(N) ((N<0)?(-N):(N))


clause init_buffer(int size)
{
    clause B;

    B.index = 0;

    B.tab = (int*)malloc(sizeof(int) * size);

    return B;
}

tab_clause init_tab_clause(int size)
{
    tab_clause T;

    T.size = 0;

    T.tab = (clause*)malloc(sizeof(clause) * size);

    return T;
}

occurence init_occurence()
{
    occurence O;

    O.negative = 0;

    O.positive = 0;

    return O;
}



void fill_tab_occurence_inverse(occurence tab_occurence[], int tab_inverse[],int nb_variable, tab_clause T)
{

    int c,var,i;
    clause C;
    occurence O;

    for (var = 0; var < nb_variable; var ++ ) // for each variable
    {

        tab_inverse[var] = 0;

        O = init_occurence();

        for (c = 0; c < T.size; c++)    // For each clause
        {

            C = T.tab[c];

            for ( i = 0; i < 3; i++)    // For each literal
            {

                if (C.tab[i] == var + 1)  // var starts from 0 in array
                    O.positive++;

                if (-C.tab[i] == var + 1)
                    O.negative++;
            }
        }

        tab_occurence[var] = O;
    }
}
/* All variables in this list have value 1, the rest have 0 */
void random_assignment(int assign[], int nb_variable)
{
    int i;

    srand48(time(0));

    for (i = 0; i < nb_variable; i ++)
    {

        if (drand48() < 0.5)
            assign[i] = 0;

        else 
            assign[i] = 1 ;

    }
}

/* random from 0 to n-1 */
int uniform_distribution(int n) {
       int limit;
       int r;
  
       limit = RAND_MAX - (RAND_MAX % n);
   
       while((r = rand()) >= limit);
   
       return r % n;
}

void print_assignment(int assign[], int nb_variable)
{
    int i;

    for (i = 0; i < nb_variable; i++)
        printf("%d ", assign[i]);

    printf("\n");
}

void print_clause(clause C)
{
    int i;

    for (i = 0; i < C.index; i++)
        printf("%d ", C.tab[i]);

    printf("\n");
}


/* Return 0 false, 1 true */
int check_assignment_clause(int assign[], clause C)
{
    int i;

    for (i = 0; i < C.index; i++)
    {
        if (C.tab[i] < 0 && assign[abs(C.tab[i])-1] == 0)
            return 1;

        if (C.tab[i] > 0 && assign[abs(C.tab[i])-1] == 1)
            return 1;
    }

    return 0;
}

int check_model(int assign[], tab_clause T)
{
    int clause_index = 0;

    for (clause_index = 0; clause_index < T.size; clause_index ++)
    {

        if (check_assignment_clause(assign, T.tab[clause_index]) == 0)
            return 0;

    }

    return 1;
}

clause random_false_clause(int assign[], tab_clause T)
{
    int i = 0;

    clause C = T.tab[i];

    while (i < T.size && (check_assignment_clause(assign, C) == 1))
    {
        C = T.tab[i++];
    }  
    return C;

}

int pickvar_flip(int tab_inverse[], int nb_variable)
{
    int i,min = tab_inverse[0];
    int save;

    for (i = 0; i < nb_variable; i ++)
    {
        if (tab_inverse[i] == 0)
            return i;

        if (tab_inverse[i] <= min)
        {
            min = tab_inverse[i];
            save = i;
        }

    }
    return save; 
}

int pickvar_occ(occurence tab_occurence[], int nb_variable, int assignment[], tab_clause T)
{
    int var, calcul, save;
    int max;

    /* Assume that the maximum belongs to the first variable */
    var = uniform_distribution(nb_variable);
    if (assignment[var] == 0)
        calcul = tab_occurence[var].positive - tab_occurence[var].negative;
    else    
        calcul = tab_occurence[var].negative - tab_occurence[var].positive;

    max = calcul;
    save = var;

    /* Choose a direction for the loop increasing or decreasing */
    int direction = uniform_distribution(2);

    /* Choose a random variable to start the loop */
    var = uniform_distribution(nb_variable);

    /* Direction increasing */
    if (direction == 1)
    {

        for (  ; var < nb_variable ; var ++ )
        {
            if (assignment[var] == 0)
                calcul = tab_occurence[var].positive - tab_occurence[var].negative;

            else    
                calcul = tab_occurence[var].negative - tab_occurence[var].positive;

            if (calcul > max )
            {
                max = calcul;
                save = var;
            }
        }

    }
    else 
    /* Direction decreasing */
    {
    for (  ; var >= 0; var -- )
    {
        if (assignment[var] == 0)
            calcul = tab_occurence[var].positive - tab_occurence[var].negative;

        else    
            calcul = tab_occurence[var].negative - tab_occurence[var].positive;

        if (calcul > max )
        {
            max = calcul;
            save = var;
        }
    }
    }

    return save;
}

void inverse_variable(int assign[],int tab_inverse[], int index, occurence tab_occurence[])
{
    if (assign[index] == 0)
        assign[index] = 1;
        
    else 
        assign[index]= 0;

    tab_inverse[index]++;

}