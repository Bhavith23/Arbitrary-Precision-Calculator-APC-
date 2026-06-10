#include "functions.h"

/* multiply_by_digit: helper to multiply a list by 0..9 */
int multiply_by_digit(Dlist *src, int digit, Dlist **result_head)
{
    if (result_head == NULL)
    {
        return FAILURE;
    }

    *result_head = NULL;

    if (digit < 0)
    {
        return FAILURE;
    }

    if (digit == 0)
    {
        *result_head = create_node(0);
        return SUCCESS;
    }

    Dlist *dlist = create_node(digit);
    int rc = multiply_lists(src, dlist, result_head);
    free_list(&dlist);

    if (rc != SUCCESS)
    {
        if (*result_head) 
        free_list(result_head);
        return FAILURE;
    }

    remove_leading_zeros(result_head);
    return SUCCESS;
}

/* division_modulus: multiplication-based long division producing quotient only */
int division_modulus(Dlist *head1, Dlist *head2, int sign1, int sign2, char op)
{
    /* only '/' supported */
    if (op != '/')
    {
        printf("ERROR : Only division '/' is supported.\n");
        return FAILURE;
    }

    remove_leading_zeros(&head1);
    remove_leading_zeros(&head2);

    /* divisor zero check — print the requested message if divisor is zero */
    if (head2 == NULL || (head2->next == NULL && head2->data == 0))
    {
        /* print exactly as you requested */
        printf("0 should not be divisible by any other\n");
        return FAILURE;
    }

    int cmp = compare_list(head1, head2);

    /* equal magnitudes -> quotient 1 or -1 */
    if (cmp == 0)
    {
        if (sign1 == sign2)
         printf("Result : 1\n");
        else                
        printf("Result : -1\n");
        return SUCCESS;
    }

    /* dividend smaller than divisor -> quotient 0 */
    if (cmp < 0)
    {
        printf("Result : 0\n");
        return SUCCESS;
    }

    Dlist *partial = NULL;
    Dlist *partial_tail = NULL;
    Dlist *quot_head = NULL;
    Dlist *quot_tail = NULL;

    /* long division: bring digits and compute quotient digits */
    for (Dlist *d = head1; d != NULL; d = d->next)
    {
        /* bring next digit down into partial */
        Dlist *nd = create_node(d->data);

        if (partial == NULL)
        {
            partial = nd;
            partial_tail = nd;
        }
        else
        {
            partial_tail->next = nd;
            nd->prev = partial_tail;
            partial_tail = nd;
        }

        remove_leading_zeros(&partial);

        /* find largest qdigit in 9..0 such that head2 * qdigit <= partial */
        int qdigit = 0;
        int candidate;

        for (candidate = 9; candidate >= 0; candidate--)
        {
            Dlist *prod = NULL;

            if (multiply_by_digit(head2, candidate, &prod) != SUCCESS)
            {
                free_list(&prod);
                if (quot_head) free_list(&quot_head);
                if (partial)   free_list(&partial);
                return FAILURE;
            }

            int c = compare_list(prod, partial);
            free_list(&prod);

            if (c <= 0)
            {
                qdigit = candidate;
                break;
            }
        }

        /* append qdigit to quotient list */
        Dlist *qnode = create_node(qdigit);

        if (quot_head == NULL)
        {
            quot_head = quot_tail = qnode;
        }
        else
        {
            quot_tail->next = qnode;
            qnode->prev = quot_tail;
            quot_tail = qnode;
        }

        /* partial = partial - (head2 * qdigit) */
        Dlist *mulq = NULL;
        if (multiply_by_digit(head2, qdigit, &mulq) != SUCCESS)
        {
            if (quot_head) free_list(&quot_head);
            if (partial)   free_list(&partial);
            return FAILURE;
        }

        Dlist *new_partial = NULL;
        subt_list(partial, mulq, &new_partial);

        free_list(&partial);
        free_list(&mulq);

        partial = new_partial;
        partial_tail = get_tail(partial);
    }

    remove_leading_zeros(&quot_head);

    /* determine sign for quotient */
    int res_sign = 1;

    if (sign1 != sign2)
    {
        res_sign = -1;
    }

    /* print quotient as list */
    printf("Result : ");
    print_list(quot_head, res_sign);

    if (quot_head) 
    free_list(&quot_head);
    if (partial)   
    free_list(&partial);

    return SUCCESS;
}
