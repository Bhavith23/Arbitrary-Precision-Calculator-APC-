/*******************************************
* Name        :  Bhavith M Gowda
* Title       : Arbitrary Prcision Calculator(APC)
* Date        :  11-11-2025
* Description :  An Arbitrary Precision Calculator (APC) project in C aims to implement mathematical operations for very large numbers,
                 exceeding the standard data type limits. 
*********************************************/

#include "functions.h"

/* main: parse args, convert to lists, dispatch to operation */
int main(int argc, char *argv[])
{
    char op = 0;

    if (!validate_CLA(argc, argv, &op))
    {
        fprintf(stderr, "Usage : %s <num1> <operator> <num2>\n""Operators supported: +  -  x  /\n",argv[0]);
        return EXIT_FAILURE;
    }

    Dlist *h1 = NULL;
    Dlist *h2 = NULL;
    int s1 = 1;
    int s2 = 1;

    if (string_to_dlist(argv[1], &h1, &s1) != SUCCESS)
    {
        fprintf(stderr, "ERROR : Invalid number '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (string_to_dlist(argv[3], &h2, &s2) != SUCCESS)
    {
        free_list(&h1);
        fprintf(stderr, "ERROR : Invalid number '%s'\n", argv[3]);
        return EXIT_FAILURE;
    }

    remove_leading_zeros(&h1);
    remove_leading_zeros(&h2);

    switch (op)
    {
        case '+':
        {
            Dlist *res = NULL;
            int res_sign = 1;

            if (s1 == s2)
            {
                add_list(h1, h2, &res);
                res_sign = s1;
            }
            else
            {
                int cmp = compare_list(h1, h2);

                if (cmp == 0)
                {
                    res = create_node(0);
                    res_sign = 1;
                }
                else if (cmp > 0)
                {
                    subt_list(h1, h2, &res);
                    res_sign = s1;
                }
                else
                {
                    subt_list(h2, h1, &res);
                    res_sign = s2;
                }
            }

            remove_leading_zeros(&res);
            printf("Result : ");
            print_list(res, res_sign);
            free_list(&res);
            break;
        }

        case '-':
        {
            Dlist *res = NULL;
            int res_sign = 1;
            int s2neg = -s2;

            if (s1 == s2neg)
            {
                add_list(h1, h2, &res);
                res_sign = s1;
            }
            else
            {
                int cmp = compare_list(h1, h2);
                if (cmp == 0)
                {
                    res = create_node(0);
                    res_sign = 1;
                }
                else if (cmp > 0)
                {
                    subt_list(h1, h2, &res);
                    res_sign = s1;
                }
                else
                {
                    subt_list(h2, h1, &res);
                    res_sign = -s1;
                }
            }

            remove_leading_zeros(&res);
            printf("Result : ");
            print_list(res, res_sign);
            free_list(&res);
            break;
        }

        case 'x':
        {
            Dlist *res = NULL;

            if (multiply_lists(h1, h2, &res) != SUCCESS)
            {
                fprintf(stderr, "ERROR : Multiplication failed\n");
                free_list(&h1);
                free_list(&h2);
                return EXIT_FAILURE;
            }

            int res_sign = 1;

            if (s1 != s2)
            {
                res_sign = -1;
            }

            remove_leading_zeros(&res);
            printf("Result : ");
            print_list(res, res_sign);
            free_list(&res);
            break;
        }

        case '/':
        {
            if (division_modulus(h1, h2, s1, s2, op) != SUCCESS)
            {
                free_list(&h1);
                free_list(&h2);
                return EXIT_FAILURE;
            }
            break;
        }

        default:
        {
            fprintf(stderr, "ERROR : Unknown operator '%c'\n", op);
            break;
        }
    }

    free_list(&h1);
    free_list(&h2);
    return EXIT_SUCCESS;
}
