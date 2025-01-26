#include <stdio.h>

int main ()
{
    int n = 0;
    printf ("Введите число n:\n");
    scanf ("%d", &n);

    int result = 1;
    for (int i = 1; i < n; i++)
    {
        result = result * (i + 1);
    }

    printf ("%d! = %d\n", n, result);
}