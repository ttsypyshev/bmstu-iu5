/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#ifndef INF_LAB_06_ALL_FUNCTIOS_H
#define INF_LAB_06_ALL_FUNCTIOS_H

typedef double (*TPF)(double);

struct I_print {
    char *name;
    double i_sum;
    double i_toch;
    double n;
};

//method rectangle integration
double IntegrationRectangle(TPF f, double a, double b, double eps, double &n);

//method trapezoidal integration
double IntegrationTrapezoidal(TPF f, double a, double b, double eps, double &n);

//other functions (print table)
void PrintTabl(struct I_print i_prn[], int k);

double f1(double x);

double f2(double x);

double f3(double x);

double f4(double x);


#endif //INF_LAB_06_ALL_FUNCTIOS_H
