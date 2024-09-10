#include "func_S.h"

double get_k(double x, int n) {
    return ((x * (n * n + 1)) / (2 * n * (n * n - 2 * n + 2)));
}

double S(double x, int &number) {
    int n = 1;
    double a = 1.0;
    double s = 1.0;

    while (a > 0.000001 && n < 100000) {
        a *= get_k(x, n);
        s += a;
        n++;
    }

    number = n;
    return s;
}