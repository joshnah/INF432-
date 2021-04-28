
#ifndef _CLAUSE_H_
#define _CLAUSE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>


#define abs(N) ((N<0)?(-N):(N))


/* A buffer of integers representing a clause */
typedef struct clause
{
    int index;
    int *tab;
} clause;

/* An array of clauses */
typedef struct tab_clause
{
    int size;
    clause *tab;
} tab_clause;

/* Initialization of a clause */
clause init_buffer(int size);

/* Initialization of an array of clauses */
tab_clause init_tab_clause(int size);


/* A struct of number of occurences positive and negative of a variable */
typedef struct occurence
{
    int positive;
    int negative;
} occurence;

occurence init_occurence();


/* This function will calculate the occurences positive and negative of all variables */
/* It also fills the array of the number of flips of a variable with 0 (At first, none of the variable is flipped) */
void fill_tab_occurence_inverse(occurence tab_occurence[], int tab_inverse[],int nb_variable, tab_clause T);


/* An array representing a random assignment */
/* 1 means true and 0 means false */
void random_assignment(int assign[], int nb_variable);

/* Take uniformly an integer between 0 and n-1 */
int uniform_distribution(int n);

/* Print out an assignment */
void print_assignment(int assign[], int nb_variable);

/* Print out a clause */
void print_clause(clause C);

/* Check if the clause is true or false for an assignment */
/* Return 0 false, 1 true */
int check_assignment_clause(int assign[], clause C);

/* Check if the model is true or false for an assignment */
/* Return 0 false, 1 true */
int check_model(int assign[], tab_clause T);

/* Randomly choose a false clause */
clause random_false_clause(int assign[], tab_clause T);

/* This function choose a variable with the least times "flip" */
int pickvar_flip(int tab_inverse[], int nb_variable);

/* This function choose a variable based on the difference between the positive and negative occurences of variables */
int pickvar_occ(occurence tab_occurence[], int nb_variable, int assignment[], tab_clause T);

/* Flip a variable in an assignment */
void inverse_variable(int assign[],int tab_inverse[], int index, occurence tab_occurence[]);



#endif 