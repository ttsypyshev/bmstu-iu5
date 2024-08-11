/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include "../include/All_functios.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main() {
    double a = -1, b = 3, n = 1;
    double EPS[]{0.01, 0.001, 0.0001, 0.00001, 0.000001};
    TPF functions[4] = {f1, f2, f3, f4};
    double exact_values[] = {
            (b * b - a * a) / 2.0,
            (cos(a * 22.0) - cos(b * 22.0)) / 22.0,
            (b * b * b * b * b - a * a * a * a * a) / 5.0,
            b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / 2.0};
    char *name_function[] = {
            "y = x",
            "y = sin(22x)",
            "y = x^4",
            "y = acrtg(x)"};


    cout << "===Rectangle method===\n";
    for (int epsilon_case = 0; epsilon_case < 5; epsilon_case++) {
        cout << setw(6) << "\nCalculation ccuracy = " << EPS[epsilon_case] << endl;
        struct I_print arr[4];
        for (int line = 0; line < 4; line++) {
            n = 1.;
            double S = IntegrationRectangle(functions[line], a, b, EPS[epsilon_case], n);
            arr[line].name = name_function[line];
            arr[line].i_sum = S;
            arr[line].i_toch = exact_values[line];
            arr[line].n = n;
        }
        PrintTabl(arr, 4);
    }

    cout << "\n\n\n===Trapezoid method===\n";
    for (int epsilon_case = 0; epsilon_case < 5; epsilon_case++) {
        cout << setw(6) << "\nCalculation ccuracy = " << EPS[epsilon_case] << endl;
        struct I_print arr[4];
        for (int line = 0; line < 4; line++) {
            n = 1.;
            double S = IntegrationTrapezoidal(functions[line], a, b, EPS[epsilon_case], n);
            arr[line].name = name_function[line];
            arr[line].i_sum = S;
            arr[line].i_toch = exact_values[line];
            arr[line].n = n;
        }
        PrintTabl(arr, 4);
    }
}
