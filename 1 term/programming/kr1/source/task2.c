/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <math.h>

void Task2_1(int *x, int *y, int *z, int a, int b) { //we pass x, y, z in such a way that the function can change them
    int flagX = 0, flagY = 0, flagZ = 0; //indicator that the element is on the segment
    for (int i = a; i < b + 1; ++i) {
        if (*x == i) { flagX = 1; } //if x is equal to an element from the segment, then
        if (*y == i) { flagY = 1; }
        if (*z == i) { flagZ = 1; }
    }
    *x = flagX ? 1 : 0; //if the indicator shows that the element was on the segment, then 1, otherwise 0
    *y = flagY ? 1 : 0;
    *z = flagZ ? 1 : 0;
}

double Task2_2(int x, int y, int z) { //just counting according to the formula ¯\(•_• )/¯
    return (((2 * z) - (x * x * x)) / ((x * x) - (y * z * z * z) - 2 * y)) + (10 * 10 * 10 * 10);
}

int Task2_3(int x) {
    int result = (int) (sin((3 * x * x) + 1) + 20) % 7; //convert to int to take full division
    return result;
}
