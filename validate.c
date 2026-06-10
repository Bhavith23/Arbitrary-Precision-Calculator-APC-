#include "functions.h"

/* is_numeric_str: check optional sign then digits */
int is_numeric_str(const char *s)
{
    if (s == NULL || *s == '\0')
    {
        return 0;
    }

    const char *p = s;

    if (*p == '+' || *p == '-')
    {
        p++;
    }

    if (*p == '\0')
    {
        return 0; /* only sign is not a number */
    }

    while (*p != '\0')
    {
        if (!isdigit((unsigned char)*p))
        {
            return 0;
        }
        p++;
    }

    return 1;
}

/* validate_CLA: ensure three args and operator valid (do not reject divisor==0 here) */
int validate_CLA(int argc, char *argv[], char *op)
{
    if (argc != 4)
    {
        return 0;
    }

    if (!is_numeric_str(argv[1])) 
    return 0;
    if (!is_numeric_str(argv[3])) 
    return 0;

    if (argv[2] == NULL) 
    return 0;
    if (strlen(argv[2]) != 1)
     return 0;

    char c = argv[2][0];

    if (c != '+' && c != '-' && c != '*' && c != '/') 
    return 0;
    
    *op = c;
    return 1;
}
