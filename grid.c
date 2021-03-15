#include "grid.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



Grid init_grid(UINT L, UINT H){

        Grid G;
        UINT i;

        G.L = L;
        G.H = H;

        /* alloctaion dynamique d'un tableau de L*H Pixel*/
        G.tab = (Box *)malloc(sizeof(Box)*L*H);

        /* test si le tableau a ete correctement alloue */
        if (G.tab == (Box *)NULL)
        {
            printf("Can't initiate grid");
        }

        /* remplir le tableau avec des pixels blancs */
        for (i=0; i<L*H; i++)
            G.tab[i] = WHITE;

        return G;
}

Box get_box(Grid G, int x, int y){
    Box B = G.tab[x,y];
    return B;
}

void set_box(Grid G, int x, int y, Box b){
    G.tab[x,y] = b;
}

UINT length_grid(Grid G){
    return G.L;
}

UINT height_grid(Grid G){
    return G.H;
}

void display_grid(Grid G)
{
    UINT L,H;
    UINT x,y;

    L = length_grid(G);
    H = height_grid(G);
    printf("length: %d height : %d\n",L,H);

    Box val;
    printf("Grid:\n");
    for (y = 1; y <= H; y++)
    {
        for ( x = 1; x <= L; x++)
        {
            val = get_box(G, x, y);
            printf("%d",val);
        }
        printf("\n");
    }
    printf("\n");
}