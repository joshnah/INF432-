#ifndef _RULES_H_
#define _RULES_H_
#include <stdlib.h>
#include <stdio.h>
#include "territory.h"
#include "grid.h"




/* This function will translate rule 1 of all territories into the file f */
void translate_rule1(FILE *f, Territory list[], int nb_territory);

/* This function will translate rule 2 of all territories into the file f */
void translate_rule2(FILE *f, Territory list[], int nb_territory);





#endif
