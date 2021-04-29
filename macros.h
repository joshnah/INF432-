/* MACROS FOR BINOMIAL AND GCD */
#ifndef _MACROS_H
#define _MACROS_H
#include <stdio.h>
#define ERREUR_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

#define INDICE(_I,_x,_y) ((_x)-1)+(_I).dim*((_y)-1)



typedef char bool;
#define FALSE 0
#define TRUE  1

/* return the binomial (n,k) */
unsigned int binomial(unsigned int n, unsigned int k);


#endif