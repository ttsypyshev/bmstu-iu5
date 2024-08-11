/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/Header.h"


int task1() {
    printf("\n---Task N1---\n");
    int size = 0;
    double x = 0;
    double *arr = malloc(size * sizeof(double));
    printf("Enter real numbers:\n");
    // recreate the array and add elements until the user enters a negative number
    while (1) {
        scanf("%lf", &x);
        if (x < 0) break;
        arr[size++] = x;
        arr = realloc(arr, size * (sizeof(double)));

    }
    // finding the minimum element
    double min = DBL_MAX; // min is equal to the maximum possible number
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            index = i;
        }
    }
    // output the array to the console
    printf("\nArray:\n");
    for (int i = 0; i < size; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("\n");
    // output the index of the minimum element to the console
    if (index > -1) printf("\nIndex of the smallest element of the array: %d\n\n\n", index + 1);
    else printf("\nThere are no elements in the array\n\n\n");

    free(arr);
    return 0;
}