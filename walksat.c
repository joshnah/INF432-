#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define abs(N) ((N<0)?(-N):(N))


/* A buffer of integers */
typedef struct clause
{
    int index;
    int *tab;
} clause;

typedef struct tab_clause
{
    int size;
    clause *tab;
} tab_clause;

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


typedef struct occurence
{
    int positive;
    int negative;
} occurence;

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
        //print_clause(T.tab[clause_index]);
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

/* int pickvar(int tab_inverse[], int nb_variable)
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
} */

int pickvar(int tab_inverse[], int nb_variable, int assignment[], tab_clause T)
{
    int max = 0;
    int c,var,save,i;
    int pos,neg;
    clause C;
    for (var = 0; var < nb_variable; var ++ )
    {
        pos = neg = 0;
        for (c = 0; c < T.size; c++)
        {
            C = T.tab[c];
            for ( i = 0; i < 3; i++)
            {
                if (T[i] == 0)
            }
        }
    }

}

void inverse_variable(int assign[],int tab_inverse[], int index)
{
    if (assign[index] == 0)
        assign[index] = 1;
    else 
        assign[index]= 0;
    tab_inverse[index]++;
}
int main(int argc, char **argv)
{
    FILE *f;
    f = fopen(argv[1], "r");

    int nb_clause, nb_variable;

    fscanf(f,"p cnf %d %d\n", &nb_variable, &nb_clause);

    int i,a;
    clause B;
    tab_clause T = init_tab_clause(nb_clause);

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


/*     for ( i = 0; i < T.size; i++)
    {
        printf("line %d: ",i);
        for (a = 0; a < T.tab->index; a++)
        {
            printf("%d ", T.tab[i].tab[a]);
        }
        printf("\n");
    } */




    int assignment[nb_variable];
    int tab_inverse[nb_variable];

    for (i = 0; i < nb_variable; i++)
    {
        tab_inverse[i] = 0;
    }

    random_assignment(assignment, nb_variable);
    clause C = init_buffer(3);
    int step = 0;
    int maxstep = 1000000;
    int var,uni_ran;
    double x;

    while ( step++ < maxstep && (check_model(assignment, T) == 0))
    {
   //         print_assignment(assignment, nb_variable);

        C = random_false_clause(assignment, T);



        x = drand48();
        if (x < 0.5)
        {
            uni_ran = uniform_distribution(3);
            var = abs(C.tab[uni_ran]) - 1;
        }
        else
        {
            var = pickvar(tab_inverse, nb_variable);
        } 

        inverse_variable(assignment, tab_inverse, var);


  /*       for ( i = 0 ; i < nb_variable; i++)
        {
            printf("%d ", tab_inverse[i]);
        }
        printf("\n"); */
    


    }
    if (step == maxstep+1)
    {
        printf("s UNSATIFIABLE");
        return(-1);
    }
    printf("s SATIFIABLE\n");
    for (i = 0; i < nb_variable; i++)
    {
        if (assignment[i] == 1)
            printf("%d ", i+1);
        else   
            printf("-%d ",i+1 );
    }
    printf("0\n");

}
