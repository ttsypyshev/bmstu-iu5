#include "func_Y.h"
#include <cmath>

double Y(double x) {
    return ((x * x) / 4. + x / 2. + 1.) * exp(x / 2.);
}