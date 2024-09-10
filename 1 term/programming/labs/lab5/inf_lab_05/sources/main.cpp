/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include "../include/all_functios.h"

using namespace std;

int main() {
    system("chcp 65001");

    int size;
    int *originalArray;
    int *editArray;

    cout << "Введите длину массива: ";
    cin >> size;

    cout << "\n\n\n---Сортировка рандомно заданного массива---\n";
    originalArray = CreatingArray(size);
    cout << "Исходный массив: ";
    OutputArray(originalArray, size);

    cout << "\n\nМетод пузырькового всплытия";
    editArray = CopyArray(originalArray, size);
    SortingBubble(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора максимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMax(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора минимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMin(editArray, size);
    OutputArray(editArray, size);


    cout << "\n\n\n---Сортировка такого же предварительно отсортированного массива---\n";
    originalArray = editArray;
    cout << "Исходный массив: ";
    OutputArray(originalArray, size);

    cout << "\n\nМетод пузырькового всплытия";
    editArray = CopyArray(originalArray, size);
    SortingBubble(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора максимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMax(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора минимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMin(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\n\n---Сортировка такого же предварительно отсортированного в обратном порядке массива---\n";
    ReversArray(originalArray, size);
    cout << "Исходный массив: ";
    OutputArray(originalArray, size);

    cout << "\n\nМетод пузырькового всплытия";
    editArray = CopyArray(originalArray, size);
    SortingBubble(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора максимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMax(editArray, size);
    OutputArray(editArray, size);

    cout << "\n\nМетод выбора минимального элемента";
    editArray = CopyArray(originalArray, size);
    SortingMin(editArray, size);
    OutputArray(editArray, size);

    delete[] originalArray;
    delete[] editArray;
    return 0;
}
