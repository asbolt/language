#include <stdio.h>
#include <math.h>

int main ()
{
    int a = 0, b = 0, c = 0;
    printf ("Введите коэффициенты:\n");
    scanf ("%d %d %d", &a, &b, &c);

    int D = b*b - 4*a*c; 

    if (D < 0)
    {
        printf ("Нет корней\n");
        return 0;
    }

    int d = sqrt(D);
    int x1 = (-b - d)/(2*a);
    int x2 = (-b + d)/(2*a);
    printf ("Корни: x1 = %d, x2 = %d\n", x1, x2);
    
    return 0;
}