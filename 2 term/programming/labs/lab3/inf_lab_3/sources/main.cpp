/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include "../include/fraction.h"

using namespace std;
int main() {
//ввод дроби с клавиатуры
    cout << "Введите дробь: \n";
    fraction z;
    cin >> z;
    cout << "z=" << z << endl;
//проверка конструкторов
    fraction fr1(10, 14), fr2;
    cout << "fr2=" << fr2 << endl;
    cout << "fr1=" << fr1 << endl;
    fraction fr = "-1 4/8";
    cout << "fr=" << fr << endl;
    fraction x(z), y;
    cout << "x=" << x << endl;
    double dbl = -1.25;
    fraction f = dbl;
    cout << "f=" << f << endl;
//проверка перегруженной операции "+"
    y = x + z;
    cout << "y=" << y << endl;
    y += x;
    f += dbl / 2;
    cout << "f=" << f << endl;
    y = x + dbl;
    cout << "y=" << y << endl;
    y = dbl + y;
    cout << "y=" << y << endl;
    y += dbl;
    cout << "y=" << y << endl;
    int i = 5;
    y += i;
    cout << "y=" << y << endl;
    y = i + x;
    cout << "y=" << y << endl;
    y = x + i;
    cout << "y=" << y << endl;
    y += dbl + i + x;
    cout << "y=" << y << endl;
    return 0;
}

//int main() {
//    fraction z;
//    std::cin >> z;
//    std::cout << "z = " << z << std::endl;

//    fraction fr1(14, 14), fr2(10, 16, true), fr3(15, 10, false, 4), fr4;
//    fraction fr5 = "-1 4/8";
//    fraction fr6 = "2 10/9";
//    fraction fr7 = "2/5";
//    fraction fr8 = "-9/7";
//    fraction fr9 = "-0";
//    double tmp = -1.25;
//    fraction fr10 = tmp;
//    fraction fr11 = 6.221;
//    fraction fr12 = -0.7;
//    fraction fr13 = -0.0;
//    fraction fr14(tmp);
//    fraction fr15(6.7);
//    fraction fr16(fr15);
//
//    std::cout << "fr1=" << fr1 << std::endl;
//    std::cout << "fr2=" << fr2 << std::endl;
//    std::cout << "fr3=" << fr3 << std::endl;
//    std::cout << "fr4=" << fr4 << std::endl;
//    std::cout << "fr5=" << fr5 << std::endl;
//    std::cout << "fr6=" << fr6 << std::endl;
//    std::cout << "fr7=" << fr7 << std::endl;
//    std::cout << "fr8=" << fr8 << std::endl;
//    std::cout << "fr9=" << fr9 << std::endl;
//    std::cout << "fr10=" << fr10 << std::endl;
//    std::cout << "fr11=" << fr11 << std::endl;
//    std::cout << "fr12=" << fr12 << std::endl;
//    std::cout << "fr13=" << fr13 << std::endl;
//    std::cout << "fr14=" << fr14 << std::endl;
//    std::cout << "fr15=" << fr15 << std::endl;
//    std::cout << "fr16=" << fr16 << std::endl;
//
//    fraction x, y, z, l, n, o, p, s;
//    x = "-1 4/7";
//    y = "1 61/64";
//    double decimal = -1.25;
//    int i = -9;
//    y += decimal + i + x;
//    std::cout << "y = " << y << std::endl;
//    fraction x = "-5 4/7";
//    int y = 1;
////    fraction y = -49;
//    fraction z = x + y;
//    std::cout << z << '\n';

//    fraction x = "49 5/7";
//    fraction n= "-49";
////    int n = -49;
////    double n = -49;
//    fraction z = x + n;
////    fraction z = n + x;
//    std::cout << z << '\n';
////    x += n;
////    std::cout << x << '\n';
//}