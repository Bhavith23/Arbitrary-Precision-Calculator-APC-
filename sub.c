#include "functions.h"

/* subt_list: subtract magnitudes h1 - h2, assuming |h1| >= |h2| */
int subt_list(Dlist *h1, Dlist *h2, Dlist **result_head)
{
    if (result_head == NULL)
    {
        return FAILURE;
    }

    *result_head = NULL;

    Dlist *t1 = get_tail(h1);
    Dlist *t2 = get_tail(h2);

    int borrow = 0;

    /* subtract digits from least significant side */
    while (t1 != NULL)
    {
        int a = t1->data - borrow;
        int b = 0;

        if (t2 != NULL)
         b = t2->data;

        /* borrow handling: if a < b, add 10 and set borrow */
        if (a < b)
        {
            a = a + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        Dlist *node = create_node(a - b);

        /* prepend to result */
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

        t1 = t1->prev;
        if (t2 != NULL)
         t2 = t2->prev;
    }

    remove_leading_zeros(result_head);
    return SUCCESS;
}
