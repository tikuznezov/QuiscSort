#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

// #include "degub.h"
#include "no_debug.h"

//! Задает красный цвет текста
#define PRED printf("\x1b[31m");
//! Задает синий цвет текста
#define PBLUE printf("\033[34m");
//! Задает фиолетовый цвет текста
#define PVIOLET printf("\033[35m");
//! Задает желтый цвет текста
#define PYELLOW printf("\x1b[33m");
//! Задает зеленый цвет текста
#define PGREEN printf("\x1b[32m");
//! Задает белый цвет текста на черном фоне (по умолчанию)
#define DEF_COL printf("\x1b[0m");
//! Задает черный текст на белом фоне
#define BLACKonWHITE printf("\x1b[30;47m");

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

int *CrateRandomArray(size_t len);

void Qsort(int *array, size_t array_len, int (*CompareFunc)(int a, int b));

size_t Part(int *array, size_t array_len, int (*CompareFunc)(int a, int b));

int Compare(int a, int b);

void Swap(int *a, int *b);

void PrintSortingArray(const int *array, const size_t len , size_t L, size_t R, int base, int iter_counter);

void PrintArray(const int *array, const size_t len);

void IsCorrect(int *array, size_t array_len, size_t l, size_t r, int base);

void IsRightCorrect(int *array, size_t array_len, size_t r, int base);

void IsLeftCorrect(int *array, size_t array_len, size_t l, int base);

int IsSortedArray(int *array, size_t array_len);





int main()
{
    printf("\n");
    size_t len = 0;
    scanf("%zu", &len);

    while (len != 0)
    {
        int *a = CrateRandomArray(len);
        // PrintArray(a, len);
        // printf("\n");

        Qsort(a, len, Compare);

        // printf("\n\n");
        // PrintArray(a, len);
        IsSortedArray(a, len);
        printf("---------------------------------------------------------\n");

        scanf("%zu", &len);
    }

    return 0;
}



// создает массив со случайными числами длины len
int *CrateRandomArray(size_t len)
{
    srand((unsigned int)time(NULL));

    int *array = NULL;
    array = (int *)calloc(len, sizeof(int));
    assert(array);

    for (int i = 0; i < len; i++)
        array[i] = rand() * pow(-1, rand());

    return array;
}

void PrintSortingArray(const int *array, const size_t len , size_t L, size_t R, int base, int iter_counter)
{
    assert(array);
    // PGREEN printf("\nbase = %d\n", base); DEF_COL
    printf("Step %2d: ", iter_counter);
    for (size_t i = 0; i < len; i++)
    {
        if (i == L)
            PBLUE
        if (i == R)
            PRED
        if ((i == R) && (R == L))
            PVIOLET
        printf("[%3d] ", array[i]);
        DEF_COL;
    }
    printf("\n");
    return;
}

void PrintArray(const int *array, const size_t len)
{
    assert(array);
    for (size_t i = 0; i < len; i++)
    {
        printf("|%3zu| ", i);
    }
    printf("\n");
    for (size_t i = 0; i < len; i++)
    {
        printf("[%3d] ", array[i]);
    }
    printf("\n");
    return;
}


int Compare(int a, int b)
{
    return (a < b) ? 1 : 0;
}

void Qsort(int *array, size_t array_len, int (*CompareFunc)(int a, int b))
{
    FUNC_CALL_INFO

    assert(array);

    if (array_len == 2)
    {
        if (array[0] > array[1])
            Swap(&array[0], &array[1]);
        SHOW_ARRAY2
        return;
    }
    else if (array_len == 1)
    {
        SHOW_ARRAY1
        return;
    }
    else if (array_len > 0)
    {
        size_t right_pointer = Part(array, array_len, CompareFunc);

        if (right_pointer == -1)
            return;

        else if (right_pointer > 0)
        {
            SHOW_LEFT_SEP
            Qsort(&array[0], right_pointer, CompareFunc);
        }

        size_t Rlen = array_len - right_pointer;
        int * Raddress = &array[right_pointer];
        SHOW_RIGHT_SEP
        Qsort(Raddress, Rlen, CompareFunc); // Сам опорный элемент гарантированно стоит на нужном месте, так что его пропускаем
    }
    else
        return;
}

size_t Part(int *array, size_t array_len, int (*CompareFunc)(int a, int b))
{
    assert(array);
    if (array_len <= 1)
        return NULL;
    size_t base_index = rand() % array_len;

    int base = array[base_index];
    SHOW_BASE
    int iter_counter = 0;

    size_t l = 0;
    size_t r = array_len-1;

    SHOW_START_INFO

    while ((l < r) && (l < array_len) && (l >= 0) &&  (r < array_len) && (r >= 0))
    {
        if (Compare(array[l], base))  // если array[l] < base
        {
            iter_counter++;
            l++;
            SHOW_SORT_STEP
        }
        else // если array[l] >= base
        {
            while ((!Compare(array[r], base)) && (r >= 0) && (r < array_len) && (l < r))
            {
                // пока array[r] <= base
                iter_counter++;
                r--; 
                SHOW_SORT_STEP
            }

            SHOW_SWAP
            Swap(&array[l], &array[r]);
            iter_counter++;
            SHOW_SORT_STEP
        }
    }
    // SHOW_SORT_STEP
    SHOW_BASE
    SHOW_RETURN
    SHOW_IS_CORRECT
    GETCHAR

    if ((l == 0) && (array[l] == base))
    {
        for (int i = 1; i < array_len; i++)
            if (array[i] != base)
                return l;
        return -1;
    }

    return l;
}

int IsSortedArray(int *array, size_t array_len)
{
    int error = 0;
    for (int i = 0; i < array_len-1; i++)
        if (array[i] > array[i+1])
            error++;
    if (error == 0)
    {
        PGREEN
        printf("It's sorted array\n");
        DEF_COL
    }
    else
    {
        PRED
        printf("INCORRECT ARRAY!!!\n");
        DEF_COL
    }
    return error;
}


void Swap(int *a, int *b)
{
    assert(a);
    assert(b);
    int temp = *a;
    *a = *b;
    *b = temp;
}

void IsLeftCorrect(int *array, size_t array_len, size_t l, int base)
{
    assert(array);
    int is_correct = true;
    for (int i = 0; ((i < l) && (i < array_len)); i++)
    {
        if (array[i] >= base)
            is_correct = false;
        // PrintSortingArray(array, array_len, i, l, base, i);
    }
    if (is_correct == true)
    {
        PGREEN printf("left side is sorted\n"); DEF_COL
    }
    else 
    {
        PRED printf("incorrect left side\n"); DEF_COL
    }
}

void IsRightCorrect(int *array, size_t array_len, size_t r, int base)
{
    assert(array);
    int is_correct = true;
    for (int i = r; (i < array_len); i++)
    {
        if (array[i] < base)
            is_correct = false;
    }
    if (is_correct == true)
    {
        PGREEN printf("right side is sorted\n"); DEF_COL
    }
    else 
    {
        PRED printf("incorrect right side\n"); DEF_COL
    }
}

void IsCorrect(int *array, size_t array_len, size_t l, size_t r, int base)
{
    assert(array);
    IsLeftCorrect(array, array_len, r, base);
    IsRightCorrect(array, array_len, l, base);
}