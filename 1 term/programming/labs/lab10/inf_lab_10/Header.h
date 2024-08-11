/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#ifndef INF_LAB_10_HEADER_H
#define INF_LAB_10_HEADER_H

void Clear(double **A, int N);

double **CreateIdentityMatrix(int N);

double **CreateZeroMatrix(int N);

double **CloneMatrix(double **A, int N);

void PrintMatrix(double **arr, int N);

double **GenerateRandomMatrix(int N);

double **ReadMatrix(const char *filename, int N);

#endif //INF_LAB_10_HEADER_H
