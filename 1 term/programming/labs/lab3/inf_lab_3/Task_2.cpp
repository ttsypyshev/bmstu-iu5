#include <iostream>
#include <iomanip>
#include "Task_2.h"

using namespace std;

double get_S(double a) {
    double s = 1.0;
    if (a >= 0) {
        for (int i = 2; i < 9; i += 2)
            s *= i * i;
        s -= a;
    } else {
        for (int i = 3; i < 10; i += 3)
            s *= i - 2;
    }
    return s;
}

void task2() {
    cout << "\n--- №2 ---\n";
    cout << fixed << setprecision(8) << "a = 5.7, S(5.7) = " << get_S(5.7) << "\n\n";

    double a;
    cout << "Введите a:\n";
    cin >> a;
    cout << fixed << setprecision(2) << "a = " << a << ", S(" << a << ") = " << get_S(a);
}
