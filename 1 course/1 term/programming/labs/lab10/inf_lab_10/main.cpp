/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <cmath>
#include "Header.h"

using namespace std;


double **FragmentMatrix(double **A, int N, int i, int j) { // i and j - row and column to be excluded from the new matrix
    double **B = CreateZeroMatrix(N);
    for (int ki = 0, di = 0; ki < N - 1; ki++) {
        if (ki == i)di = 1; // if the number is equal to the number of the row to be excluded, we shift it by 1 to ignore it
        for (int kj = 0, dj = 0; kj < N - 1; kj++) {
            if (kj == j) dj = 1; // similar to the lines
            B[ki][kj] = A[ki + di][kj + dj];
        }
    }
    return B;
}

double Determinant(double **arr, int N) {
    int det = 0, k = 1; //det - determinant, k - (-1)^i

    if (N < 1) cout << "\nThe determinant cannot be calculated!\n";
    else if (N == 1) det = arr[0][0]; // matrix 1x1
    else if (N == 2) det = arr[0][0] * arr[1][1] - (arr[1][0] * arr[0][1]); // matrix 2x2
    else { // matrix nxn, where n>=3
        for (int i = 0; i < N; i++) { // calculation of the determinant by the method of line decomposition
            /*   det B = a31 * (-1)^(3+1) * det arr(without 3 row and 1 columns) + ...   */
            det += k * arr[i][0] * Determinant(FragmentMatrix(arr, N, i, 0), N - 1);
            k = -k;
        }
    }

    return det;
}

double **Inverse(double **A, int N) {
    double temp;
    double **E = CreateIdentityMatrix(N); // E - identity matrix
    double **B = CloneMatrix(A, N); // B - copy of matrix A

    for (int i = 0; i < N - 1; ++i) { // swapping the lines
        if (B[i][0] < B[i + 1][0]) {
            swap(B[i], B[i + 1]); // in the matrix A
            swap(E[i], E[i + 1]); // in the unit matrix E
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j != i) {
                temp = B[j][i] / B[i][i];
                for (int k = 0; k < N; ++k) {
                    B[j][k] -= B[i][k] * temp;
                    E[j][k] -= E[i][k] * temp;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        temp = B[i][i];
        for (int j = 0; j < N; j++) {
            B[i][j] /= temp;
            E[i][j] /= temp;
        }
    }

    return E;
}

double **Multiple(double **A, double **B, int N) {
    double **C = CreateZeroMatrix(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

int main() {
    srand((unsigned int) time(NULL));

    int N = 3;

//    double **A = GenerateRandomMatrix(N);
    double **A = ReadMatrix("../matrix.txt", N);
    cout << "\nMatrix A\n";
    PrintMatrix(A, N);

    double det = Determinant(A, N);
    cout << "\nDeterminant: " << det << "\n\n\n";

    if (det == 0) cout << "The matrix does not have an inverse matrix\n";
    else {
        double **A_inverse = Inverse(A, N);
        cout << "Inverse matrix A^(-1)\n";
        PrintMatrix(A_inverse, N);

        cout << "\n\nCheck: A * A^(-1) = E" << "\n";
        PrintMatrix(Multiple(A, A_inverse, N), N);

        Clear(A_inverse, N);
    }

    Clear(A, N);
    return 0;
}
