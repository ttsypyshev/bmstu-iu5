/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>


#ifndef INF_LAB_05_ALL_FUNCTIOS_H
#define INF_LAB_05_ALL_FUNCTIOS_H

//method bubble
void SortingBubble(int *Array, int size);


//method min/max
void SortingMax(int *Array, int size);

void SortingMin(int *Array, int size);


//other functions (creating, random, revers)
int *CreatingArray(int size);

int *CopyArray(int *source, int size);

void ReversArray(int *source, int size);

void OutputArray(int *source, int size);


#endif //INF_LAB_05_ALL_FUNCTIOS_H
