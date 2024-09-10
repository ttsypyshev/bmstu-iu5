/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include "../include/All_functios.h"
#include <math.h>

double IntegrationRectangle(TPF function, double a, double b, double eps, double &n) {
    static double S0 = 0, S1 = 0; //global s0 s1 for function IntegrationRectangle
    double dx = (b - a) / n;
    for (int i = 0; i < n; ++i) {
        S1 += function(a + i * dx);
    }
    S1 *= dx;

    if ((abs(S1 - S0)) < eps) {
        return S1;
    } else {
        n *= 2;
        S0 = S1;
        S1 = 0;
        return IntegrationRectangle(function, a, b, eps, n);
    }
}
