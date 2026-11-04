#include <stdio.h>
#include <stdlib.h>

/*
 * Алгоритм: Сортировка подсчетом (Counting Sort)
 *
 * Временная сложность:        O(n + m)
 * Пространственная сложность: O(n + m)
 *
 * где:
 *   n — количество элементов в массиве,
 *   m — диапазон входных значений.
 */

void min_max(int *ptr_min, int *ptr_max, int n, int const *A)
{
    if (n <= 0 || A == NULL)
    {
        *ptr_min = 0;
        *ptr_max = 0;
        return;
    }

    *ptr_min = A[0];
    *ptr_max = A[0];
    int i;

    for (i = 0; i < n; ++i)
    {
        if (A[i] < *ptr_min)
        {
            *ptr_min = A[i];
        }
        if (A[i] > *ptr_max)
        {
            *ptr_max = A[i];
        }
    }
}

int *counting_sort(int n, int const *A)
{
    if (n <= 0 || A == NULL)
    {
        return NULL;
    }

    int *B, *C;

    B = malloc(n * sizeof(*B));
    if (B == NULL)
    {
        fprintf(stderr, "Not enough memory for initializing array B\n");
        return NULL;
    }

    int a;
    int b;
    min_max(&a, &b, n, A);

    int C_size = b - a + 1;
    C = calloc(C_size, sizeof(*C));
    if (C == NULL)
    {
        fprintf(stderr, "Not enough memory for initializing array C\n");
        free(B);
        B = NULL;
        return NULL;
    }

    int i;
    for (i = 0; i < n; ++i)
    {
        C[A[i] - a]++;
    }

    for (i = 1; i < C_size; ++i)
    {
        C[i] += C[i - 1];
    }

    for (i = n - 1; i >= 0; --i)
    {
        B[C[A[i] - a] - 1] = A[i];
        C[A[i] - a]--;
    }

    free(C);
    C = NULL;
    return B;
}

int main(void)
{
    int n;
    int *A;

    printf("Input size of array: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid input for size of array\n");
        return 1;
    }

    A = malloc(n * sizeof(*A));
    if (A == NULL)
    {
        fprintf(stderr, "Not enough memory for initializing array A\n");
        return 1;
    }

    printf("Input all %d values of the array separated by spaces: ", n);
    int i;
    for (i = 0; i < n; ++i)
    {
        if (scanf("%d", &A[i]) != 1)
        {
            fprintf(stderr, "Invalid input for array element %d\n", i);
            free(A);
            A = NULL;
            return 1;
        }
    }

    int *B;
    B = counting_sort(n, A);

    if (B == NULL)
    {
        free(A);
        A = NULL;
        return 1;
    }

    for (i = 0; i < n; ++i)
    {
        printf("%d ", B[i]);
    }
    printf("\n");

    free(A);
    A = NULL;
    free(B);
    B = NULL;
    return 0;
}