#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* A buffer of integers */
typedef struct buffer
{
    int index;
    int *tab;
} buffer;


buffer init_buffer(int size)
{
    buffer B;
    B.index = 0;
    B.tab = (int*)malloc(sizeof(int) * size);
    return B;
}


/* int main(int argc, char **argv)
{
    FILE *f, *g;
    f = fopen(argv[1], "r");

    g = fopen("output3sat.cnf", "w");


    int nb_clause, nb_variable;

    fscanf(f,"p cnf %d %d\n", &nb_variable, &nb_clause);

    int new_var = nb_variable + 1;
    int i,a,k, temp1, temp2;;
    buffer B = init_buffer(nb_variable);


    for ( i = 0; i < nb_clause; i++ )
    {
        fscanf(f, "%d ", &a);
        while (a != 0)
        {
            B.tab[B.index++] = a;
            fscanf(f, "%d", &a);
        }

        switch (B.index)
        {
        case 1:
            temp1 = new_var++;
            temp2 = new_var++;
            fprintf(g,"%d %d %d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d %d -%d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d -%d %d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d -%d -%d 0\n",B.tab[0], temp1 , temp2);

            break;


        case 2:
            temp1 = new_var++;
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], new_var );
            fprintf(g,"%d %d -%d 0\n", B.tab[0], B.tab[1], new_var );

            break;


        case 3: 
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], B.tab[2]);
            break;


        default:
            temp1 = new_var++;
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], temp1);
            temp2 = new_var++;
            for ( k = 2; k < B.index - 2; k++)
            {
                fprintf(g,"%d -%d %d 0\n", B.tab[k], temp1, temp2);
                temp1 = temp2;
                temp2 = new_var++;
            }
            fprintf(g,"%d %d -%d 0\n", B.tab[B.index -2 ], B.tab[B.index -1], temp1 );
            break;
        }


        B.index = 0;
    }
    fclose(f);
    fclose(g);


}

 */


int main(int argc, char **argv)
{
    FILE *f, *g,*d;
    f = fopen(argv[1], "r");

    g = fopen("temp.output3sat.cnf", "w");


    int nb_clause, nb_variable;
    int nb_new_clause = 0;


    char buff_char[100000];

    fscanf(f,"p cnf %d %d\n", &nb_variable, &nb_clause);

    int new_var = nb_variable + 1 ;
    int i,a,k, temp1, temp2;;
    buffer B = init_buffer(nb_variable);


    for ( i = 0; i < nb_clause; i++ )
    {
        fscanf(f, "%d ", &a);
        while (a != 0)
        {
            B.tab[B.index++] = a;
            fscanf(f, "%d", &a);
        }

        switch (B.index)
        {
        case 1:
            temp1 = new_var++;
            temp2 = new_var++;
            fprintf(g,"%d %d %d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d %d -%d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d -%d %d 0\n",B.tab[0], temp1 , temp2);
            fprintf(g,"%d -%d -%d 0\n",B.tab[0], temp1 , temp2);
            nb_new_clause += 4;
            break;  


        case 2:
            temp1 = new_var++;
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], new_var );
            fprintf(g,"%d %d -%d 0\n", B.tab[0], B.tab[1], new_var );
            nb_new_clause += 2;

            break;


        case 3: 
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], B.tab[2]);    
            nb_new_clause += 1;

            break;


        default:
            temp1 = new_var;
            fprintf(g,"%d %d %d 0\n", B.tab[0], B.tab[1], temp1);
            temp2 = temp1 + 1;
            for ( k = 2; k < B.index - 2; k++)
            {
                fprintf(g,"%d -%d %d 0\n", B.tab[k], temp1, temp2);
                temp1++;
                temp2++;
            }
            fprintf(g,"%d %d -%d 0\n", B.tab[B.index -2 ], B.tab[B.index -1], temp1);
            new_var = new_var + B.index -3;
            nb_new_clause += (B.index -2);

            break;
        }


        B.index = 0;
    }
    fclose(f);
    fclose(g);



    d = fopen("output3sat.cnf", "w");

    fprintf(g, "p cnf %d %d\n", new_var, nb_new_clause);

    f = fopen("temp.output3sat.cnf","r");

    fscanf(f,"p cnf %d %d\n", &nb_variable, &nb_clause);


    while (fgets(buff_char,100000, f) != NULL)
    {
        fprintf(g, "%s",buff_char);
    }

    fclose(f);
    fclose(d);
    
}
