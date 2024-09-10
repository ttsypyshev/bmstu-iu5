/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int GetRandomNumber(int a, int b) {
    return a + (b - a + 1) * rand() / RAND_MAX;
}

int *CreatingArray(int size) {
    int *arr = new int[size];
    srand( (unsigned int) time( NULL ) );
    rand( );
    for (int i = 0; i < size; ++i)
        arr[i] = GetRandomNumber(1, 9);
    return arr;
}

int *CopyArray(int *source, int size) {
    int *newArr = new int[size];
    for (int i = 0; i < size; ++i)
        newArr[i] = source[i];
    return newArr;
}

void ReversArray(int *source, int size) {
    for (int i = 0; i < size / 2; ++i) {
        swap(source[i], source[size - i - 1]);
    }
}

void OutputArray(int *source, int size) {
    for (int i = 0; i < size; i++) {
        cout << source[i] << ' ';
    }
}