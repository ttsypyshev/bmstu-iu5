/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <fstream>
#include <cmath>
#include "Header.h"

using namespace std;

void Clear(double **A, int N) {
    for (int i = 1; i < N; i++)
        delete[] A[i];
    delete[] A;
}

double **CreateIdentityMatrix(int N) {
    double **E = new double *[N + 1];
    for (int i = 0; i < N; ++i) {
        E[i] = new double[N + 1];
        for (int j = 0; j < N; ++j) {
            E[i][j] = 0;
        }
        E[i][i] = 1;
    }
    return E;
}

double **CreateZeroMatrix(int N) {
    double **E = new double *[N + 1];
    for (int i = 0; i < N; ++i) {
        E[i] = new double[N + 1];
        for (int j = 0; j < N; ++j) {
            E[i][j] = 0;
        }
    }
    return E;
}

double **CloneMatrix(double **A, int N) {
    double **B = new double *[N];
    for (int i = 0; i < N; i++) {
        B[i] = new double[N];
        for (int j = 0; j < N; j++)
            B[i][j] = A[i][j];
    }
    return B;
}

void PrintMatrix(double **arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3f\t", arr[i][j]);
        }
        cout << endl;
    }
    return;
}

double **GenerateRandomMatrix(int N) {
    double **A = new double *[N + 1];
    for (int i = 0; i < N; i++) {
        A[i] = new double[N + 1];
        for (int j = 0; j < N; j++)
            A[i][j] = rand() % 10;
    }
    return A;
}

double **ReadMatrix(const char *filename, int N) {
    double **A = CreateZeroMatrix(N);
    ifstream file(filename, ios_base::in);
    if (!file) cout << "\nError of file1 opening.\n";

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            file >> A[i][j];

    file.close();
    return A;
}
