#include <pthread.h>
#include <stdio.h>

unsigned long long int func(int m, int n);

int MAX_THREADS = 4;

void *proceso(void *);

int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
int lenV = sizeof(V) / sizeof(V[0]);
unsigned long long int VR[2];

void main()
{

    pthread_t threads[MAX_THREADS];
    int rango[MAX_THREADS][2];
    int intervalo = lenV / MAX_THREADS;

    for (int i = 0; i < MAX_THREADS; i++)
    {
        rango[i][0] = i * intervalo;
        rango[i][1] = (i + 1) * intervalo;
        pthread_create(&threads[i], NULL, proceso, (void *)rango[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Impresion de los resultados
    printf("V: [");
    for (int i = 0; i < lenV; i++)
    {
        printf("%llu ", VR[i]);
    }
    printf("]\n");
}

void *proceso(void *arg)
{
    int *rango = (int *)arg;
    int inicio = rango[0];
    int fin = rango[1];

    for (int i = inicio; i < fin; i++)
    {
        VR[i] = func(3, V[i]);
    }
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