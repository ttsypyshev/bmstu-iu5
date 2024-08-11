/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>

int Task1(int *arr, int size) {
    int result = 1; //multiplication
    for (size_t i = 0; i < size; ++i) { //iterate over the elements of an array
        if (arr[i] < 0 && arr[i] % 2 == 0) { //if the element is less than 0 and even, then
            result *= arr[i];
        }
    }
    return result;
}
