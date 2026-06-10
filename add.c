#include "functions.h"

/* add_list: add magnitudes of two lists into result_head */
int add_list(Dlist *h1, Dlist *h2, Dlist **result_head)
{
    if (result_head == NULL)
    {
        return FAILURE;
    }

    *result_head = NULL;

    Dlist *t1 = get_tail(h1);
    Dlist *t2 = get_tail(h2);

    int carry = 0;

    /* add digits from least significant side */
    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int d1 = 0;
        int d2 = 0;

        if (t1 != NULL) 
        d1 = t1->data;

        if (t2 != NULL) 
        d2 = t2->data;

        int sum = d1 + d2 + carry;

        /* carry is 0 or 1 for decimal addition */
        if (sum >= 10)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        Dlist *node = create_node(sum % 10);

        /* prepend to result to build MSB-first list */
        if (*result_head == NULL)
        {
            *result_head = node;
        }
        else
        {
            node->next = *result_head;
            (*result_head)->prev = node;
            *result_head = node;
        }

        if (t1 != NULL) 
        t1 = t1->prev;

        if (t2 != NULL) 
        t2 = t2->prev;
    }

    remove_leading_zeros(result_head);
    return SUCCESS;
}
