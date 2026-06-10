#include "functions.h"

/* multiply_lists: multiplication head1 * head2 */
int multiply_lists(Dlist *h1, Dlist *h2, Dlist **result_head)
{
    if (result_head == NULL)
    {
        return FAILURE;
    }

    *result_head = NULL;

    if (h1 == NULL || h2 == NULL)
    {
        *result_head = create_node(0);
        return SUCCESS;
    }

    /* measure lengths */
    int len1 = 0;
    int len2 = 0;
    Dlist *p;

    for (p = h1; p != NULL; p = p->next) 
    len1++;

    for (p = h2; p != NULL; p = p->next) 
    len2++;

    int size = len1 + len2 + 2;
    int *A = calloc(len1, sizeof(int));
    int *B = calloc(len2, sizeof(int));
    int *P = calloc(size, sizeof(int));

    if (A == NULL || B == NULL || P == NULL)
    {
        free(A);
        free(B);
        free(P);
        return FAILURE;
    }

    /* fill A and B LSB-first */
    int idx = 0;

    for (p = get_tail(h1); p != NULL; p = p->prev)
    {
        A[idx++] = p->data;
    }

    idx = 0;

    for (p = get_tail(h2); p != NULL; p = p->prev)
    {
        B[idx++] = p->data;
    }

    /* perform multiplication with carry */
    int i, j;

    for (i = 0; i < len1; i++)
    {
        int carry = 0;

        for (j = 0; j < len2; j++)
        {
            int pos = i + j;
            int tmp = P[pos] + A[i] * B[j] + carry;
            P[pos] = tmp % 10;
            carry = tmp / 10;
        }

        int pos = i + j;
        while (carry != 0)
        {
            int tmp = P[pos] + carry;
            P[pos] = tmp % 10;
            carry = tmp / 10;
            pos++;
        }
    }

    /* convert P (LSB-first) to list MSB-first */
    int k = size - 1;

    while (k > 0 && P[k] == 0)
    {
        k--;
    }

    for (; k >= 0; k--)
    {
        Dlist *n = create_node(P[k]);

        if (*result_head == NULL)
        {
            *result_head = n;
        }
        else
        {
            Dlist *t = get_tail(*result_head);
            t->next = n;
            n->prev = t;
        }
    }

    remove_leading_zeros(result_head);
    free(A);
    free(B);
    free(P);
    return SUCCESS;
}
