#include <stdio.h>

int fact (int n);

int main ()
{
    int n = 0;
    printf ("Введите число n:\n");
    scanf ("%d", &n);

    int result = fact (n);

    printf ("%d! = %d\n", n, result);
}

int fact (int n)
{
    if (n > 0)
        return n * fact(n-1);
    
    return 1;
}