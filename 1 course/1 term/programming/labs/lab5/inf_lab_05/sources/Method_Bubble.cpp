/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>

using namespace std;

void SortingBubble(int *Array, int size) {
    int permutations = 0, comparisons = 0, i, j, tmp;
    for (i = 0; i < size - 1; ++i) {
        for (j = 0; j < size - i - 1; ++j) {
            if (Array[j] > Array[j + 1]) {
                tmp = Array[j];
                Array[j] = Array[j + 1];
                Array[j + 1] = tmp;
                ++permutations;
            }
            ++comparisons;
        }
    }
    cout << "\nКоличество перестановок - " << permutations << ", количество сравнений - " << comparisons << "\n";
}