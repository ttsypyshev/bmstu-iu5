/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#define EPS 0.0001

double get_k(double x, int n) { // An = k * An-1
    return (x + n) / (x * x + n * x - x); //calculate the coefficient
}

double Task3(double x) {
    double sum = 0, current = (x + 1) / (x * x); //current - the first value of the sum
    int n = 1;

    sum += current;

    //it will multiply the previous value by a factor until the value is less than eps
    while (current > EPS && n < 100000) { //limitation on eps and number of iterations
        current *= get_k(x, n); //multiply the previous value by a factor
        sum += current;
        ++n;
    }

    return sum;
}

