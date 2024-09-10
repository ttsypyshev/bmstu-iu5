#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

double Factorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    else return n * Factorial(n - 1);
}

void Clear(double **A, int N) {
    for (int i = 1; i < N; i++)
        delete[] A[i];
    delete[] A;
}

double **CreateDinamicMatrix(int N) {
    double **A = new double *[N];
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
        }
    }
    return A;
}

void FillDinamicMatrix(double **A, int N, int x) {
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            if (i == j) { A[i][j] = 1; }
            else if (i < j) { A[i][j] = pow(x, i) / pow(Factorial(j), i); }
            else if (i > j) { A[i][j] = pow(-x, i) / pow(Factorial(j), i); }
        }
    }
}

void PrintDinamicMatrix(double **A, int N) {
    int width = 100;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int K = floor(width / N) - 1;
            if (A[i][j] > 0.01)
                cout << left << fixed << setw(K) << setprecision(K - 3) << A[i][j] << " ";
            else
                cout << left << fixed << setw(K) << setprecision(K - 7) << scientific << A[i][j] << " ";
        }
        cout << "\n";
    }
}

void LoggingDinamicMatrix(double **A, int N) {
    ofstream log_file("../log.txt", ios_base::app);
    if (!(log_file)) { log_file.open("../log.txt"); }
    log_file << "\n\n\n";
    int width = 100;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int K = floor(width / N) - 1;
            if (A[i][j] > 0.01)
                log_file << left << fixed << setw(K) << setprecision(K - 3) << A[i][j] << " ";
            else
                log_file << left << fixed << setw(K) << setprecision(K - 7) << scientific << A[i][j] << " ";
        }
        log_file << "\n";
    }
}

void FillStaticMatrix(double ( &B)[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            B[i][j] = 10 * i + j;
}

void PrintStaticMatrix(double B[10][10]) {
    double **tmp = new double *[10];
    for (int i = 0; i < 10; i++) {
        tmp[i] = new double[10];
        for (int j = 0; j < 10; j++) {
            tmp[i][j] = B[i][j];
        }
    }
    PrintDinamicMatrix(tmp, 10);
    Clear(tmp, 10);
}

void LoggingStaticMatrix(double B[10][10]) {
    double **tmp = new double *[10];
    for (int i = 0; i < 10; i++) {
        tmp[i] = new double[10];
        for (int j = 0; j < 10; j++) {
            tmp[i][j] = B[i][j];
        }
    }
    LoggingDinamicMatrix(tmp, 10);
    Clear(tmp, 10);
}

int main() {
    int N, x;
    cout << "Enter the value of N and X: ";
    cin >> N >> x;
    ++N;

    cout << "\n----- The matrix A -----\n";

    double **A = CreateDinamicMatrix(N);
    FillDinamicMatrix(A, N, x);
    PrintDinamicMatrix(A, N);
    LoggingDinamicMatrix(A, N);
    Clear(A, N);

    cout << "\n----- The matrix B -----\n";

    double B[10][10];
    FillStaticMatrix(B);
    PrintStaticMatrix(B);
    LoggingStaticMatrix(B);

    cout << "\n----- Additional calculations -----\n";

    cout << "(1) - " << B << "  " << B[0] << "  " << B[2] << endl;
    cout << "(2) - " << B[0][0] << "  " << **B << "  " << *B[0] << endl;
    cout << "(3) - " << *(*(B + 1)) << "  " << *B[1] << endl;
    cout << "(4) - " << *(B[0] + 1) << "  " << *(*B + 1) << endl;
    cout << "(5) - " << B[0][20] << "  " << *(B[0] + 20) << "  " << *B[2] << endl;
}