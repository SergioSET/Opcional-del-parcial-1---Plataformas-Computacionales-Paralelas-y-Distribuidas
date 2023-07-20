
#include <stdio.h>
#include <omp.h>

unsigned long long int
func(int m, int n);

int MAX_THREADS = 2;

void main()
{
    int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int lenV = sizeof(V) / sizeof(V[0]);

    unsigned long long int VR[lenV];

#pragma omp parallel num_threads(MAX_THREADS)
    {
#pragma omp for schedule(static)
        for (int i = 0; i < lenV; i++)
        {
            VR[i] = func(3, V[i]);
        }
    }
    // Impresion de los resultados
    printf("V: [");
    for (int i = 0; i < lenV; i++)
    {
        printf("%llu ", VR[i]);
    }
    printf("]\n");
}

unsigned long long int func(int m, int n)
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return func(m - 1, 1);
    else
        return func(m - 1, func(m, n - 1));
}
