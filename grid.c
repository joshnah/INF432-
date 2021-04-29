#include "grid.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Grid init_grid(int dim, int value)
{
    Grid I;
	UINT i;
	
	
	I.tab = (Box *)malloc(sizeof(Box)*dim*dim);
	I.dim = dim;
	
	if (I.tab == (Box *)NULL)
	{
		ERREUR_FATALE("IMPOSSIBLE TO CREATE A GRID");
	}
	
	/* Fill with all initial values */
	for (i=0; i<dim*dim; i++)
		I.tab[i] = value;
		
	return I;
}


/* The function return the value in the box (x,y) */
Box get_box(Grid G, int x, int y)
{
    if (x<1 || x>G.dim || y<1 || y>G.dim)
		return 0;
	
	else
		return G.tab[INDICE(G,x,y)];
}

/* The function set the value in the box (x,y) */
void set_box(Grid G, int x, int y, Box b)
{

    if (x<1 || x>G.dim || y<1 || y>G.dim)
		return ;

    G.tab[INDICE(G,x,y)] = b;
}

void print_dash(int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("—");
}

/* Display the grid in the stdout */
void display_grid(Grid G)
{
    int x,y;
    int dim = G.dim;

	printf("Dimension : %d  %d\n",dim, dim);

	Box b;
	printf(" ");
	print_dash((dim) * 2 + 1);
	printf("\n");
	for (y = 1; y <= dim; y++)
	{
		printf("| ");
		for ( x = 1; x <= dim; x++)
		{

			b = get_box(G, x, y);
			printf("%d ",b);
			
		}
		printf("|");
		printf("\n");

	}
	printf(" ");
	print_dash((dim) * 2+1);
	printf("\n");
}


void display_grid_availability(Grid G)
{
    int x,y;
    int dim = G.dim;

	printf("Dimension : %d  %d\n",dim, dim);
	printf("/ means unavailable\n \n");


	Box b;
	printf(" ");
	print_dash((dim) * 2 + 1);
	printf("\n");
	for (y = 1; y <= dim; y++)
	{
		printf("| ");
		for ( x = 1; x <= dim; x++)
		{

			b = get_box(G, x, y);

			if (b!=-1)
				printf("%d ",0);
			else	
				printf("/ ");
			
			
		}
		printf("|");

		printf("\n");

	}
	printf(" ");

	print_dash((dim) * 2+1);

	printf("\n");
}



void display_grid_territories(Grid G)
{
    int x,y;
    int dim = G.dim;

	printf("Dimension : %d  %d\n",dim, dim);


	Box b;
	printf(" ");
	print_dash((dim) * 2 + 1);
	printf("\n");
	for (y = 1; y <= dim; y++)
	{
		printf("| ");
		for ( x = 1; x <= dim; x++)
		{

			b = get_box(G, x, y);
			
			if (b != -1)
				printf("%d ",b);
			else 
				printf("* ");
			
		}
		printf("|");
		printf("\n");

	}
	printf(" ");
	print_dash((dim) * 2+1);
	printf("\n");
}
