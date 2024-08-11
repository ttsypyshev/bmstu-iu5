#include <iostream>

using namespace std;

#define MAX_ITER 100000000

pair<double, std::size_t>
Newton(double x1, double eps, double(f(double x, double c)), double(fd(double x, double c)), double c) {
    double f_results = f(x1, c);
    size_t i;
    for (i = 0; abs(f_results) > eps && i < MAX_ITER; ++i) {
        x1 -= (f_results / fd(x1, c));
        f_results = f(x1, c);
    }

    return std::make_pair(x1, i);
}
