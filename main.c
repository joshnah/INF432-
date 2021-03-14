#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territory.h"

#define ERREUR_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}



int main(int argc, char *argv[])
{
    int dim;
    int nb_territory;
    FILE *f;


    /*********************** READING INPUT ***********************/
    f = fopen(argv[1], "r");
    if (f == NULL)
        ERREUR_FATALE("Error argument!");

    fscanf(f, "%d", &dim);
    fscanf(f, "%d", &nb_territory);

    Territory list_territory[nb_territory];
    read_input(f, nb_territory, dim, list_territory);
    
    display_all_territories(list_territory, nb_territory);



}
