#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

/* node for doubly linked decimal list */
typedef struct Dlist
{
    int data;
    struct Dlist *prev;
    struct Dlist *next;
} Dlist;

/* construction / destruction */
Dlist *create_node(int digit);
void   free_list(Dlist **head);

/* helpers */
Dlist *get_tail(Dlist *head);
void   remove_leading_zeros(Dlist **head);
void   print_list_plain(Dlist *head);
void   print_list(Dlist *head, int sign);
int    string_to_dlist(const char *s, Dlist **head, int *sign);

/* compare and arithmetic */
int    compare_list(Dlist *h1, Dlist *h2);
int    add_list(Dlist *h1, Dlist *h2, Dlist **result_head);
int    subt_list(Dlist *h1, Dlist *h2, Dlist **result_head);
int    multiply_lists(Dlist *h1, Dlist *h2, Dlist **result_head);

/* division helpers */
int    multiply_by_digit(Dlist *src, int digit, Dlist **result_head);
int    division_modulus(Dlist *head1, Dlist *head2, int sign1, int sign2, char op);

/* CLI validation */
int    validate_CLA(int argc, char *argv[], char *op);

#endif /* FUNCTIONS_H */
