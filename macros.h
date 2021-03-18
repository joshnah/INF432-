#ifndef _MACROS_H
#define _MACROS_H

#define ERREUR_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}

#define INDICE(_I,_x,_y) ((_x)-1)+(_I).dim*((_y)-1)


typedef char bool;
#define FALSE 0
#define TRUE  1

#endif