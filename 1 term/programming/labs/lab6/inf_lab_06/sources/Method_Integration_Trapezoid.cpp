/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include "../include/All_functios.h"
#include <math.h>

double IntegrationTrapezoidal(TPF function, double a, double b, double eps, double &n) {
    static double S0 = 0, S1 = 0;
    double dx = (b - a) / n;
    for (int i = 0; i < n; i++) {
        S1 += (function(a + i * dx) + function(a + (i + 1) * dx));
    }
    S1 *= dx / 2;

    if ((abs(S1 - S0)) < eps) {
        return S1;
    } else {
        n *= 2;
        S0 = S1;
        S1 = 0;
        return IntegrationTrapezoidal(function, a, b, eps, n);
    }
}
