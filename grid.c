#include "grid.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Grid init_grid(int dim)
{
    Grid I;
	UINT i;
	
	/* alloctaion dynamique d'un tableau de L*H Pixel*/
	I.tab = (Box *)malloc(sizeof(Box)*dim*dim);
	I.dim = dim;
	/* test si le tableau a ete correctement alloue */
	if (I.tab == (Box *)NULL)
	{
		ERREUR_FATALE("IMPOSSIBLE TO CREATE A GRID");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<dim*dim; i++)
		I.tab[i] = 0;
		
	return I;
}


/* The function return the value in the box (x,y) */
Box get_box(Grid G, int x, int y)
{
    if (x<1 || x>G.dim || y<1 || y>G.dim)
		return 0;
	return G.tab[INDICE(G,x,y)];
}

/* The function set the value in the box (x,y) */
void set_box(Grid G, int x, int y, Box b)
{
    if (x<1 || x>G.dim || y<1 || y>G.dim)
		return ;
    G.tab[INDICE(G,x,y)] = b;
}

/* Display the grid in the stdout */
void display_grid(Grid G)
{
    int x,y;
    int dim = G.dim;
	printf("Dimension : %d  %d\n",dim, dim);
	Box b;
	printf("Grid:\n");
	for (y = 1; y <= dim; y++)
	{
		for ( x = 1; x <= dim; x++)
		{
			b = get_box(G, x, y);
			printf("%d",b);
		}
		printf("\n");
	}
	printf("\n");
}


