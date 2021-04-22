#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int dim;
    dim = atoi(argv[1]);
    FILE *f = fopen("max_input.txt","w");

    fprintf(f, "%d\n%d\n", dim, dim*dim);

    int x,y,a;
    int xedge = 0,yedge = 0;
    for (y = 1; y <= dim ; y++)
    {   
        if (y == 1 || y == dim)
            yedge = 1;
        else 
            yedge = 0;

        for ( x = 1; x <= dim ; x++)
        {
            if ( x == 1 || x == dim)
                xedge = 1;
            else 
                xedge = 0;

            if (xedge && yedge)
                a = 4;
            else if (xedge || yedge)
                a = 6;
            else 
                a = 9;


            fprintf(f, "%d %d %d\n", a ,x ,y);
        }
    }

    fclose(f);
}