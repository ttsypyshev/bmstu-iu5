/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>

using namespace std;

void SortingMax(int *Array, int size) {
    int permutations = 0, comparisons = 0, min_index, i, j;
    for (i = 0; i < size - 1; ++i) {
        min_index = 0;
        for (j = 0; j < size - i; ++j) {
            if (Array[j] > Array[min_index])
                min_index = j;
            ++comparisons;
        }

        if (min_index != size - i - 1) {
            ++permutations;
            swap(Array[size - i - 1], Array[min_index]);
        }
    }
    cout << "\nКоличество перестановок - " << permutations << ", количество сравнений - " << comparisons << "\n";
}

void SortingMin(int *Array, int size) {
    int permutations = 0, comparisons = 0, max_index, i, j;
    for (i = 0; i < size - 1; ++i) {
        max_index = i;
        for (j = i + 1; j < size; ++j) {
            if (Array[j] < Array[max_index])
                max_index = j;
            ++comparisons;
        }

        if (max_index != i) {
            ++permutations;
            swap(Array[i], Array[max_index]);
        }
    }
    cout << "\nКоличество перестановок - " << permutations << ", количество сравнений - " << comparisons << "\n";
}