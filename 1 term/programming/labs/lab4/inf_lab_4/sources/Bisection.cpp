#include <iostream>

using namespace std;

#define MAX_ITER 100000000

pair<double, std::size_t> Bisection(double x0, double x1, double eps, double(f(double x, double c)), double c) {
    double mid = (x0 + x1) / 2;
    size_t i;
    for (i = 0; abs(f(mid, c)) > eps && i < MAX_ITER; ++i) {
        mid = (x0 + x1) / 2;
        if (f(mid, c) * f(x1, c) <= 0) { x0 = mid; }
        else { x1 = mid; }
    }

    return std::make_pair((x0 + x1) / 2, i);
}
