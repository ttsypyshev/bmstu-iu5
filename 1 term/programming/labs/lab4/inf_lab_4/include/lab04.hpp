#ifndef INF_LAB_4_LAB04_H
#define INF_LAB_4_LAB04_H

#include <iostream>

//Iteration
std::pair<double, size_t> Iteration(double x, double eps, double(f(double x, double c)), double c);

//Bisection
std::pair<double, std::size_t> Bisection(double x0, double x1, double eps, double(f(double x, double c)), double c);

//Newton
std::pair<double, std::size_t>
Newton(double x, double eps, double(f(double x, double c)), double(fd(double x, double c)), double c);

#endif //INF_LAB_4_LAB04_H
