#include "territory.h"
#include <stdio.h>
#include <stdlib.h>

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))



Rectangle area_territory(Coordinate O, int dim)
{
    Rectangle R;
    R.C1.x = max(1, O.x -1);
    R.C1.y = max(1, O.y -1);
    R.C2.x = min(dim, O.x+1);
    R.C2.y = min(dim, O.y+1);

    return R;
}

void read_input(FILE *f, int nb_territory,int dim, Territory list_territory[])
{
    int nb_bomb;
    int x;
    int y;
    int i;
    int count_variable = 1;
    for (i = 1; i <= nb_territory; i++ )
    {
        fscanf(f, "%d", &nb_bomb);
        fscanf(f, "%d", &x);
        fscanf(f, "%d", &y);
        list_territory[i-1].index = i;
        list_territory[i-1].I.a = count_variable;
        list_territory[i-1].I.b = count_variable + nb_bomb - 1;
        list_territory[i-1].O = (Coordinate){x, y};
        list_territory[i-1].nb_bomb = nb_bomb; 
        list_territory[i-1].area = area_territory(list_territory[i-1].O, dim); 
        count_variable = count_variable + nb_bomb;
    }
}


void display_all_territories(Territory list[], int nb_territory)
{

    int i;
    for (i = 0; i < nb_territory; i++)
    {
        printf("Territory %d: \n", list[i].index);
        printf("Number of boxes around: %d\n", list[i].size);
        printf("Number of bomb: %d\n", list[i].nb_bomb);
        printf("Interval [a,b]: [%d,%d]\n", list[i].I.a, list[i].I.b);
        printf("Center O (x,y): (%d,%d)\n", list[i].O.x, list[i].O.y);
        printf("Rectangle of territory: (%d, %d) to (%d, %d)\n\n", list[i].area.C1.x, list[i].area.C1.y, list[i].area.C2.x, list[i].area.C2.y);
    }

}


Grid Extract_Grid(Territory list[], int nb_territory, int dim)
{
    Grid G = init_grid(dim);

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
Grid_intersection Extract_Grid_Intersection(Grid G, Territory list[], int nb_territory)
{
    int x,y;
    Grid_intersection I = init_Grid_intersection(G.dim);
    int t;
    List_intersection l;
    for (y = 1; y <= G.dim; y++)
	{
		for ( x = 1; x <= G.dim; x++)
		{
            for (t = 1; t <= nb_territory; t++)
            {    
                if (check_in_territory(t, list, x, y ) == TRUE)
                    add_territory(I, x, y, t);
                l = get_List_intersection(I, x, y);

            }   
            if ( l != NULL && l->number == 1)
            {   
                free_list_intersection(&l);
                I.tab[INDICE(I,x,y)] = NULL;  
            } 
		}
	}

    return I;
}