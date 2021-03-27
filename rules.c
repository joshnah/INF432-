#include "rules.h"
#include <string.h>

char tab_char[82];
char buff[10];

void translate_rule1(FILE *f, Territory list[], int nb_territory)
{
    int t, s, bomb, box, i, k;
    Territory T;
    for (t = 0; t < nb_territory; t++)
    {
        T = list[t];
        s = T.I.a;

        for (bomb = 0;  bomb < T.nb_bomb; bomb++)
        {
            for ( box = 0;  box < T.list_box->nb_points; box++)
            {
                fprintf(f, "%d ", s + box *T.nb_bomb);
            }
            s = s+1;
            fprintf(f, "\n");
        }

        fprintf(f,"######\n");
        for (bomb = 0; bomb < T.nb_bomb; bomb++)
        {
            for ( i = T.I.a+bomb; i < T.I.b; i = i + T.nb_bomb)
            {
                for ( k = i + T.nb_bomb; k <= T.I.b ; k= k + T.nb_bomb)
                    fprintf(f, "-%d -%d \n", i, k);  
            }
        }
        fprintf(f,"######");
    }
}


void translate_rule2(FILE *f, Territory list[], int nb_territory)
{
    int t, bomb,i, k;
    Territory T;
    for (t = 0; t < nb_territory; t++)
    {
        T = list[t];
        for (i = T.I.a; i < T.I.b ; i = i + T.nb_bomb)
        {
            for ( bomb = i; bomb <= i + T.nb_bomb -2; bomb++)
            {
                for (k = bomb + 1; k <= i + T.nb_bomb -1; k++)
                    fprintf(f, "-%d -%d \n", bomb, k);  
            }
        }
    }
}


void translate_rule1_2(FILE *f, Territory list[], int nb_territory)
{
    int t, s, bomb, box, i, k;
    Territory T;
    for (t = 0; t < nb_territory; t++)
    {
        T = list[t];
        s = T.I.a;

        fprintf(f,"Territory %d: \n", t);
        fprintf(f,"Rule1 :\n");
        for (bomb = 0;  bomb < T.nb_bomb; bomb++)
        {
            for ( box = 0;  box < T.list_box->nb_points; box++)
            {
                fprintf(f, "%d ", s + box *T.nb_bomb);
            }
            s = s+1;
            fprintf(f, "\n");
        }

        fprintf(f,"##########\n");
        for (bomb = 0; bomb < T.nb_bomb; bomb++)
        {
            for ( i = T.I.a+bomb; i < T.I.b; i = i + T.nb_bomb)
            {
                for ( k = i + T.nb_bomb; k <= T.I.b ; k= k + T.nb_bomb)
                    fprintf(f, "-%d -%d \n", i, k);  
            }
        }
        fprintf(f,"Rule 2:\n");
        
        for (i = T.I.a; i < T.I.b ; i = i + T.nb_bomb)
        {
            for ( bomb = i; bomb <= i + T.nb_bomb -2; bomb++)
            {
                for (k = bomb + 1; k <= i + T.nb_bomb -1; k++)
                    fprintf(f, "-%d -%d \n", bomb, k);  
            }
        }
    }
}


int find_starting_var(Territory list[], int nb_territory, Cell_intersection *box, int index_territory)
{
    cell_coordinate *temp_box = list[index_territory].list_box->first;
    int i = 0;
    while (temp_box->C.x != box->C.x || temp_box->C.y != box->C.y )
    {
        temp_box = temp_box->next;
        i++;
    }

    return i * list[index_territory].nb_bomb + list[index_territory].I.a;
}


void generate_char(char tab_char[], int index_territory, Territory list[], int nb_territory, Cell_intersection *box)
{
    tab_char[0] = '\0';
    int i = 0;
    int starting_var;

    starting_var =find_starting_var(list, nb_territory, box, index_territory);

    for (i = starting_var; i < starting_var + list[index_territory].nb_bomb; i++)
    {
        sprintf(buff, "%d", i);
        strcat(tab_char, buff);
        strcat(tab_char," ");
    }

}

void translate_rule3(FILE *f, Territory list[], int nb_territory, Linked_list_intersection_box *l_intersec)
{
    Cell_intersection * box = l_intersec->first;
    Cell_territory * current;
    Cell_territory *temp;
    int i,k,g,t, starting;

    for (i = 0; i < l_intersec->nb_box; i++)
    {
        current = box->list_of_territory;
        for (k = 0; k < box->nb_territory; k++)
        {
            generate_char(tab_char, current->val-1,list, nb_territory, box);
            temp = box->list_of_territory; 
            for (g = 0; g < box->nb_territory; g++)
            {
                if (g != k)
                {
                    starting = find_starting_var(list, nb_territory, box, temp->val-1);
                    for (t = starting; t < starting + list[temp->val-1].nb_bomb; t++)
                    {
                        fprintf(f, "%s ", tab_char);
                        fprintf(f, "-%d ", t);
                        fprintf(f, "\n");

                    }
                    fprintf(f, "\n");
                }
                temp =temp->next;
            }

            current = current->next;
        }

        
        box = box->next;
    }


}
