#ifdef debug


#define FUNC_CALL_INFO     PRED printf("\n\nВызвана функция Qsort\n"); PRED PrintArray(array, array_len); DEF_COL printf("\n");

#define SHOW_ARRAY        PGREEN PrintArray(&array[0], array_len); DEF_COL

#define SHOW_LEFT_SEP      printf("\nРазделение ЛЕВОГО массива с 0 по %d; Длина = %d;\n", right_pointer-1, right_pointer); PrintArray(&array[0], right_pointer);

#define SHOW_RIGHT_SEP     printf("\nРазделение ПРАВОГО массива с %d по %d; Длина = %d\n", right_pointer, array_len - 1, array_len - right_pointer); PrintArray(Raddress, array_len - right_pointer);

#define SHOW_BASE          PRED printf("base = %d\n", base); DEF_COL

#define SHOW_START_INFO    printf("start: l = %zu(%d), r = %zu(%d)\n", l, array[l], r, array[r]); PrintSortingArray(array, array_len, l, r, iter_counter); printf("\n");

#define SHOW_SORT_STEP     PrintSortingArray(array, array_len, l, r, iter_counter);

#define SHOW_RETURN        printf("return: %d\n", l);

#define SHOW_IS_CORRECT    IsCorrect(array, array_len, l, r, base);

#define GETCHAR            getchar();

#define SHOW_SWAP          printf("swap(%d, %d)\n", array[l], array[r]);

#define SEPARATE           PYELLOW printf("-------------------------------------------------------------\n"); DEF_COL

#define SHOW_INDEXES       

#endif