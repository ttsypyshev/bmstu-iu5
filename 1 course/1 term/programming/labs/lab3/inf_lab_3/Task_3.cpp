#include "Task_3.h"
#include "func_S.h"
#include "func_Y.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printArray(const char *label, double *arr) {
    cout << left << setw(6) << label;
    for (int i = 0; i < 6; i++)
        cout << setw(6) << setprecision(7) << fixed << " " << arr[i];
    cout << endl;
}

void task3() {
    cout << "\n--- №3 ---\n";

    double array_x[6];
    double array_Y[6];
    double array_S[6];
    double array_N[6];

    int i = 0;
    int number ;

    for (double x = 0.0; x <= 1; (x += 0.2, i++)) {
        array_x[i] = x;
        array_Y[i] = Y(x);
        array_S[i] = S(x,number);
        array_N[i] = number;
    }

    printArray("x", array_x);
    printArray("Y(x)", array_Y);
    printArray("S(x)", array_S);
    printArray("N", array_N);
}