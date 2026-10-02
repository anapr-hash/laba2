#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


void task1(void)
{
    printf("ЗАДАНИЕ 1\n");
    printf("Размеры: 100, 200, 400, 1000, 2000, 4000, 10000\n\n");

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num = 7;

    for (int s = 0; s < num; s++)
    {
        int N = sizes[s];
        int i, j, r;

        printf("Массив = %d:\n", N);

        int** a = (int**)malloc(N * sizeof(int*));
        int** b = (int**)malloc(N * sizeof(int*));
        int** c = (int**)malloc(N * sizeof(int*));

        int* data_a = (int*)malloc((size_t)N * N * sizeof(int));
        int* data_b = (int*)malloc((size_t)N * N * sizeof(int));
        int* data_c = (int*)calloc((size_t)N * N, sizeof(int));

        if (!a || !b || !c || !data_a || !data_b || !data_c)
        {
            printf("Не хватило памяти для массива = %d.\n\n", N);
            free(a); free(b); free(c);
            free(data_a); free(data_b); free(data_c);
            continue;
        }

        for (i = 0; i < N; i++)
        {
            a[i] = data_a + i * N;
            b[i] = data_b + i * N;
            c[i] = data_c + i * N;
        }

        clock_t t0 = clock();

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                a[i][j] = rand() % 100 + 1;
                b[i][j] = rand() % 100 + 1;
            }
        }

        clock_t t1 = clock();

        for (i = 0; i < N; i++)
        {
            for (r = 0; r < N; r++)
            {
                int temp = a[i][r];
                for (j = 0; j < N; j++)
                {
                    c[i][j] += temp * b[r][j];
                }
            }
        }

        clock_t t2 = clock();

        double fill = (double)(t1 - t0) / CLOCKS_PER_SEC;
        double mult = (double)(t2 - t1) / CLOCKS_PER_SEC;
        double total = (double)(t2 - t0) / CLOCKS_PER_SEC;

        printf("Массив = %5d , заполнение: %10.4f сек , умножение: %12.4f сек , итого: %12.4f сек\n\n", N, fill, mult, total);

        free(data_a); free(data_b); free(data_c);
        free(a); free(b); free(c);
    }
}

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x;
    int a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++)
    {
        gap = a[k];

        for (i = gap; i < count; ++i)
        {
            x = items[i];

            for (j = i - gap; (j >= 0) && (x < items[j]); j -= gap)
                items[j + gap] = items[j];

            items[j + gap] = x;
        }
    }
}

int compare(const void* a, const void* b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static int partitionHoare(int* arr, int left, int right)
{
    int pivot = arr[left + (right - left) / 2];
    int i = left - 1;
    int j = right + 1;

    for (;;)
    {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j)
            return j;

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

static void qsRecursive(int* arr, int left, int right)
{
    while (left < right)
    {
        int p = partitionHoare(arr, left, right);

        if (p - left < right - (p + 1))
        {
            qsRecursive(arr, left, p);
            left = p + 1;
        }
        else
        {
            qsRecursive(arr, p + 1, right);
            right = p;
        }
    }
}

void qs(int* arr, int n)
{
    if (n > 1)
        qsRecursive(arr, 0, n - 1);
}

void randomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void ascendingArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)


        arr[i] = i;
}

void descendingArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void halfArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n / 2; i++)
        arr[i] = i;
    for (i = n / 2; i < n; i++)
        arr[i] = n - i;
}

void copyArray(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
        b[i] = a[i];
}

void test(const char* name, int source[], int n)
{
    int* arr = (int*)malloc(n * sizeof(int));
    clock_t start, end;
    double t_shell, t_qsort, t_quick;

    if (!arr)
    {
        printf("\n%s (N = %d): не хватило памяти.\n", name, n);
        return;
    }

    printf("\n%s (N = %d)\n", name, n);

    copyArray(source, arr, n);
    start = clock();
    shell(arr, n);
    end = clock();
    t_shell = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  Shell:            %10.6f сек\n", t_shell);

    copyArray(source, arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare);
    end = clock();
    t_qsort = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  qsort():          %10.6f сек\n", t_qsort);

    copyArray(source, arr, n);
    start = clock();
    qs(arr, n);
    end = clock();
    t_quick = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  quickSort (ручн): %10.6f сек\n", t_quick);

    free(arr);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    //task1();

    printf("ЗАДАНИЕ 2.\n");

    int SIZE;
    printf("Введите размер массива: ");
    if (scanf("%d", &SIZE) != 1 || SIZE <= 0)
    {
        printf("Некорректный размер.\n");
        return 1;
    }

    int* arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr)
    {
        printf("Не хватило памяти для массива размера %d.\n", SIZE);
        return 1;
    }

    randomArray(arr, SIZE);
    test("1. Случайный", arr, SIZE);

    ascendingArray(arr, SIZE);
    test("2. Возрастающий", arr, SIZE);

    descendingArray(arr, SIZE);
    test("3. Убывающий", arr, SIZE);

    halfArray(arr, SIZE);
    test("4. Полу-возр/полу-убыв", arr, SIZE);

    free(arr);
    return 0;
}