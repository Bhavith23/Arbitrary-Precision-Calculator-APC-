#include "functions.h"

/* allocate a single digit node */
Dlist *create_node(int digit)
{
    Dlist *node = malloc(sizeof(Dlist));
    if (node == NULL)
    {
        fprintf(stderr, "ERROR : memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->data = digit;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

/* free the entire list and set head to NULL */
void free_list(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    Dlist *cur = *head;
    while (cur != NULL)
    {
        Dlist *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    *head = NULL;
}

/* return tail pointer of a list */
Dlist *get_tail(Dlist *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    Dlist *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }

    return p;
}

/* remove leading zeros and keep at least one node */
void remove_leading_zeros(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    while (*head != NULL && (*head)->next != NULL && (*head)->data == 0)
    {
        Dlist *tmp = *head;
        *head = tmp->next;
        (*head)->prev = NULL;
        free(tmp);
    }
}

/* print digits only (no sign, no newline) */
void print_list_plain(Dlist *head)
{
    if (head == NULL)
    {
        putchar('0');
        return;
    }

    Dlist *p = head;
    while (p != NULL)
    {
        putchar('0' + p->data);
        p = p->next;
    }
}

/* print sign and digits with newline */
void print_list(Dlist *head, int sign)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    /* don't print '-' for exact zero */
    if (head->next == NULL && head->data == 0)
    {
        printf("0\n");
        return;
    }

    if (sign < 0)
    {
        putchar('-');
    }

    print_list_plain(head);
    putchar('\n');
}

/* convert string to list and return sign; returns SUCCESS/FAILURE */
int string_to_dlist(const char *s, Dlist **head, int *sign)
{
    if (s == NULL || head == NULL || sign == NULL)
    {
        return FAILURE;
    }

    *head = NULL;
    *sign = 1;


    /* optional sign */
    if (*s == '+')
    {
        *sign = 1;
        s++;
    }
    else if (*s == '-')
    {
        *sign = -1;
        s++;
    }

    /* skip leading zeros but keep one if number is zero */
    while (*s == '0' && isdigit((unsigned char)*(s + 1)))
    {
        s++;
    }

    int found = 0;
    while (*s != '\0' && isdigit((unsigned char)*s))
    {
        Dlist *n = create_node(*s - '0');

        if (*head == NULL)
        {
            *head = n;
        }
        else
        {
            Dlist *t = get_tail(*head);
            t->next = n;
            n->prev = t;
        }

        found = 1;
        s++;
    }

    if (!found)
    {
        if (*head) free_list(head);
        return FAILURE;
    }

    remove_leading_zeros(head);

    /* normalize sign if value is zero */
    if (*head != NULL && (*head)->next == NULL && (*head)->data == 0)
    {
        *sign = 1;
    }

    return SUCCESS;
}

/* compare magnitudes: return 1 if h1>h2, 0 if equal, -1 if h1<h2 */
int compare_list(Dlist *h1, Dlist *h2)
{
    if (h1 == NULL && h2 == NULL)
    {
        return 0;
    }

    if (h1 == NULL)
    {
        return -1;
    }

    if (h2 == NULL)
    {
        return 1;
    }

    int l1 = 0;
    int l2 = 0;
    Dlist *p;

    for (p = h1; p != NULL; p = p->next)
    {
        l1++;
    }

    for (p = h2; p != NULL; p = p->next)
    {
        l2++;
    }

    if (l1 > l2)
     return 1;
    if (l1 < l2) 
    return -1;

    while (h1 != NULL && h2 != NULL)
    {
        if (h1->data > h2->data)
         return 1;

        if (h1->data < h2->data)
         return -1;
         
        h1 = h1->next;
        h2 = h2->next;
    }

    return 0;
}
