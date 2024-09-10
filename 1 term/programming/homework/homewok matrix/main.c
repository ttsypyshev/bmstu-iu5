#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double **GenerateRandomMatrix(int N, int M) { // create a dynamic matrix and fill it with random numbers
    double **A = malloc(sizeof(double *) * N);
    for (size_t i = 0; i < N; i++) {
        A[i] = malloc(sizeof(double) * M);
        for (size_t j = 0; j < M; j++)
            A[i][j] = ((float) rand() / (float) (RAND_MAX)) * 10;
    }
    return A;
}

double **CreateZeroMatrix(int N, int M) { // creating a matrix consisting of 0
    double **E = malloc(sizeof(double *) * N);
    for (size_t i = 0; i < N; ++i) {
        E[i] = malloc(sizeof(double) * M);
        for (size_t j = 0; j < M; ++j) {
            E[i][j] = 0;
        }
    }
    return E;
}

double **FragmentMatrix(double **A, int N, int M, int i, int j) { // i and j - row and column to be excluded from the new matrix
    double **B = CreateZeroMatrix(N, M);
    for (int ki = 0, di = 0; ki < N - 1; ki++) {
        if (ki == i)
            di = 1; // if the number is equal to the number of the row to be excluded, we shift it by 1 to ignore it
        for (int kj = 0, dj = 0; kj < M - 1; kj++) {
            if (kj == j) dj = 1; // similar to the lines
            B[ki][kj] = A[ki + di][kj + dj];
        }
    }
    return B;
}

void PrintMatrix(double **arr, int N, int M) { // we display the matrix on the screen
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            printf("%.3f\t", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand((unsigned int) time(NULL));

    printf("\nEnter the size of the matrix (N, M)\n");
    int N = 3, M = 4; // N - count row, M - count column
    scanf("%d %d", &N, &M);

    printf("\nEnter the row and column to delete (i, j)\n");
    int i = 1, j = 4; // i - row, j - column
    scanf("%d %d", &i, &j);

    double **A = GenerateRandomMatrix(N, M); // create a random matrix
    printf("\nOriginal matrix:\n");
    PrintMatrix(A, N, M);

    double **B = FragmentMatrix(A, N, M, i - 1, j - 1); // creating a copy of matrix A without i row and j column
    printf("\nCropped Matrix:\n");
    PrintMatrix(B, N - 1, M - 1);

    free(A);
    free(B);
    return 0;
}
