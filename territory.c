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
