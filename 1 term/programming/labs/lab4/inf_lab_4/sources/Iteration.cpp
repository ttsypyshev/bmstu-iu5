#include <cmath>

using namespace std;

#define MAX_ITER 100000000

pair<double, std::size_t> Iteration(double x, double eps, double(f(double x, double c)), double c) {
    double f_result = f(x, c);
    size_t i;
    for (i = 0; abs(f_result) > eps && i < MAX_ITER; ++i) {
        x -= f_result;
        f_result = f(x, c);
    }

    return std::make_pair(x, i);
}
