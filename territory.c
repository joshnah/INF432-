#include "territory.h"
#include <stdio.h>
#include <stdlib.h>


char buffer[1000];





Rectangle area_territory(Coordinate O, int dim)
{
    Rectangle R;

    R.C1.x = max(1, O.x -1);
    R.C1.y = max(1, O.y -1);
    R.C2.x = min(dim, O.x+1);
    R.C2.y = min(dim, O.y+1);

    return R;
}

int area_rectangle(Rectangle R)
{
    return (R.C2.x - R.C1.x +1) * (R.C2.y - R.C1.y +1);
}

Grid read_input(FILE *f, int *nb_territory,int dim, Territory list_territory[], Grid *G)
{
    int nb_bomb;
    int x;
    int y;
    int count_variable = 1;
    int a;
    int i = 1,k;
    int c,d;
    Grid A = init_grid(dim,0);
    Rectangle r;
    for (k = 1; k <= *nb_territory; k++ )
    {
        fscanf(f, "%d", &nb_bomb);
        fscanf(f, "%d", &x);
        fscanf(f, "%d", &y);
        if (get_box(*G, x,y) != -1)
            ERREUR_FATALE("ERROR INPUT! TWO TERRITORIES AT SAME PLACE");
        set_box(*G, x, y, nb_bomb);

        if (nb_bomb != 0)
        {
            list_territory[i-1].O = (Coordinate){x, y};

            list_territory[i-1].area = area_territory(list_territory[i-1].O, dim); 
            a = area_rectangle(list_territory[i-1].area);
            list_territory[i-1].size = a;
            if (nb_bomb > a)
                ERREUR_FATALE("UNSATIFIABLE (THERE IS A TERRITORY WITH TOO MANY BOMBS)");
            list_territory[i-1].index = i;
    
        
            list_territory[i-1].nb_bomb = nb_bomb; 
            count_variable = count_variable + nb_bomb*a;


            
            i++;
        }

        else 
        {
           r = area_territory((Coordinate){x,y}, dim);   
           for (c = r.C1.x; c <= r.C2.x; c++)
                for(d = r.C1.y; d <= r.C2.y; d++)
                    set_box(A, c, d, -1);
        }
    }
    *nb_territory = i-1;
    return A;
}


void display_all_territories(Territory list[], int nb_territory)
{

    int i;
    cell_coordinate *C;
    for (i = 0; i < nb_territory; i++)
    {
        printf("Territory %d: \n", list[i].index);
        printf("Number of boxes around: %d\n", list[i].size);
        printf("Number of bomb: %d\n", list[i].nb_bomb);
        printf("Interval [a,b]: [%d,%d]\n", list[i].I.a, list[i].I.b);
        printf("Center O (x,y): (%d,%d)\n", list[i].O.x, list[i].O.y);
        printf("Rectangle of territory: (%d, %d) to (%d, %d)\n", list[i].area.C1.x, list[i].area.C1.y, list[i].area.C2.x, list[i].area.C2.y);
        printf("List of %d avaible boxes:\n", list[i].list_box->nb_points);
        C = list[i].list_box->first;
        while (C != NULL)
        {
            printf("(%d, %d)    ", C->C.x, C->C.y);
            C = C->next;
        } 

        printf("\n----------------\n");
    }

}


Grid Extract_Grid(Territory list[], int nb_territory, int dim)
{
    Grid G = init_grid(dim,-1);

    int i;
    for (i = 0; i < nb_territory; i++)
        set_box(G, list[i].O.x, list[i].O.y , list[i].nb_bomb);
    
    return G;


}
/* Check if (x,y) is in territory t or not */
bool check_in_territory(int t, Territory list[], int x, int y)
{
    Rectangle r = list[t-1].area;
    if (r.C1.x <= x && r.C2.x >=x && r.C1.y <= y && r.C2.y >= y)
        return TRUE;
    else
        return FALSE;
    
}

void extract_list_intersection(Linked_list_intersection_box *L, Territory list[], int nb_territory, Grid G, Grid A)
{
    int x,y;
    int t;
    Cell_intersection * i;
    for (y = 1; y <= G.dim; y++)
	{
		for ( x = 1; x <= G.dim; x++)
		{
            if (get_box(A, x, y) == -1)
                continue;
                
            i = new_cell_intersection();
            i->C = (Coordinate){x,y};
            for (t = 1; t <= nb_territory; t++)
            {    
                if (check_in_territory(t, list, x, y ) == TRUE)
                    add_territory(i,t);
            }   
            if (i->nb_territory <= 1)
                free_cell_intersection(i);
            else
                add_cell_intersection(i, L);
		}
	}    
}



int nb_clauses(Territory list[], int nb_territory, Linked_list_intersection_box *L)
{
    int nb = 0;
    int i = 0;
    for (i = 0; i < nb_territory; i ++)
    {
        nb = nb + list[i].nb_bomb;
        nb = nb + list[i].list_box->nb_points * binomial(list[i].nb_bomb, 2);
        nb = nb + list[i].nb_bomb * binomial( list[i].list_box->nb_points, 2);
    }

    int a= 0;
    /* Rule 3 */
    Cell_intersection *C = L->first;
    Cell_territory *C_t;
    while (C != NULL)
    {
        C_t = C->list_of_territory;
        a = 0;
        while (C_t != NULL)
        {
            a = a + list[C_t->val-1].nb_bomb;
            C_t = C_t->next;
        }
        a = a * (C->nb_territory - 1);
        nb = nb + a;
        C = C->next; 
    }
    

    return nb;
}

list_coordinate* init_list_coordinate()
{
    list_coordinate *l = malloc(sizeof(list_coordinate));
    l->first = NULL;
    l->nb_points = 0;
    return l;
}

void add_coordinate(Coordinate C, list_coordinate *l)
{
    cell_coordinate *new = malloc(sizeof(cell_coordinate));
    new->next = NULL;
    new->C = C;

    if (l->first == NULL)
        l->first = new;
    else 
    {
        new->next = l->first;
        l->first = new;
    }
    l->nb_points++;
}


void extract_list_availability(Territory list[], int nb_territory, Grid Avai)
{
    int t = 0;
    list_coordinate *newlist;
    int x,y;
    Box b;
    int count_variable = 1;
    for (t = 0; t < nb_territory; t++)
    {
        newlist = init_list_coordinate();
        for (y = list[t].area.C2.y; y >= list[t].area.C1.y; y--)
        {
            for (x = list[t].area.C2.x; x >= list[t].area.C1.x ; x--)
            {
                if ( (b = get_box(Avai,x,y) )!= -1)
                    add_coordinate((Coordinate){x, y}, newlist);
            }
        }
        list[t].list_box = newlist;
        list[t].I.a = count_variable;
        list[t].I.b = count_variable + list[t].nb_bomb * newlist->nb_points - 1;
        count_variable = count_variable + list[t].nb_bomb * newlist->nb_points;

    }
}


cell_coordinate* Mark_bomb(Grid G, int var, Territory list[], int nb_territory)
{
    int i,a;
    for (i = 0; i < nb_territory; i++)
    {
        if (list[i].I.a <= var && var <= list[i].I.b)
            break;
    }

    var = (var - list[i].I.a) / (list[i].nb_bomb );
    cell_coordinate *cell = list[i].list_box->first;
    for ( a = 0 ; a < var; a++ )
    {
        cell = cell->next;
    }

    return cell;

}


int result_grid(FILE * d, Territory list[], int nb_territory, int dim, Grid* R)
{
    char *p;
    char c;
    fscanf(d, "%*c %c", &c);
    if (c == 'U')  // check the line unsatifiable
    {
        printf("Program is unsatifiable!!\n");
        return 0;
    }

    printf("Program is satifiable!!\n");
    fscanf(d,"%*s \n");
    int a;
    cell_coordinate *temp;

    while (fgets(buffer, 1000, d) != NULL)
    {
        p = strstr(buffer, " ") + 1;
        while (p!= NULL)
        { 
            a = atoi(p);
            if (a > 0 )
            {
                temp = Mark_bomb((*R), a, list, nb_territory);
                set_box((*R), temp->C.x, temp->C.y,1);
            }
            p = strstr(p+1, " " );
        }
    }

    return 1;
}



int result_sat3(FILE * d, Territory list[], int nb_territory, int dim, Grid* R, int nb_variable)
{
    char *p;
    char c;
    fscanf(d, "%*c %c", &c);
    if (c == 'U')  // check the line unsatifiable
    {
        printf("Program is unsatifiable!!\n");
        return 0;
    }

    printf("Program is satifiable!!\n");
    fscanf(d,"%*s \n");
    int a = 1;
    cell_coordinate *temp;

    while (fgets(buffer, 1000, d) != NULL && a <= nb_variable)
    {
        printf("%s\n",buffer);

        p = strstr(buffer, " ") + 1;
        while (p!= NULL)
        { 
            a = atoi(p);
            if (a > nb_variable)
                break;
            if (a > 0 )
            {
                temp = Mark_bomb((*R), a, list, nb_territory);
                set_box((*R), temp->C.x, temp->C.y,1);
            }
            p = strstr(p+1, " " );
        }
    }

    return 1;
}
