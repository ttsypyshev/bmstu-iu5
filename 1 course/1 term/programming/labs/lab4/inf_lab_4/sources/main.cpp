#include "../include/lab04.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define precision1 7
#define eps1 0.000001

#define precision2 9
#define eps2 0.00000001

double f(double x, double c) {
    return x - c * cos(x);
}

double df(double x, double c) {
    return 1. + c * sin(x);
}

int main() {
    cout << "--- ü1 ---\n";
    pair<double, size_t> t1 = Iteration(0., eps1, f, 1.);
    pair<double, size_t> t2 = Bisection(0., 1.57, eps1, f, 1.);
    pair<double, size_t> t3 = Newton(1.57, eps1, f, df, 1.);
    cout << fixed << setprecision(precision1) << "x = " << t1.first << ", iter - " << t1.second << endl;
    cout << setprecision(precision1) << "x = " << t2.first << ", iter - " << t2.second << endl;
    cout << setprecision(precision1) << "x = " << t3.first << ", iter - " << t3.second << endl;
    cout << "\n\n";

    cout << "--- ü2 ---\n";
    t1 = Iteration(0., eps2, f, 1.);
    t2 = Bisection(0., 1.57, eps2, f, 1.);
    t3 = Newton(1.57, eps2, f, df, 1.);
    cout << fixed << setprecision(precision2) << "x = " << t1.first << ", iter - " << t1.second << endl;
    cout << setprecision(precision2) << "x = " << t2.first << ", iter - " << t2.second << endl;
    cout << setprecision(precision2) << "x = " << t3.first << ", iter - " << t3.second << endl;
    cout << "\n\n";

    cout << "--- ü3 ---\n";
    t1 = Iteration(0., eps1, f, 10.);
    t2 = Bisection(0., 1.57, eps1, f, 10.);
    t3 = Newton(1.57, eps1, f, df, 10.);
    cout << fixed << setprecision(precision1) << "x = " << t1.first << ", iter - " << t1.second << endl;
    cout << setprecision(precision1) << "x = " << t2.first << ", iter - " << t2.second << endl;
    cout << setprecision(precision1) << "x = " << t3.first << ", iter - " << t3.second << endl;
    return 0;
}