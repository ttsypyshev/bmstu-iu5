/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include "../include/All_functios.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <math.h>

using namespace std;

double f1(double x) {
    return x;
}

double f2(double x) {
    return sin(22 * x);
}

double f3(double x) {
    return x * x * x * x;
}

double f4(double x) {
    return atan(x);
}

void PrintTabl(I_print i_prn[], int k) {
    const int m = 4;             //число столбцов таблицы
    int wn[m] = {16, 18, 18, 18}; //ширина столбцов таблицы
    const char *title[m] = {"Function", "Integral", "IntSum", "N "};
    int size[m];
    for (int i = 0; i < m; i++)
        size[i] = strlen(title[i]);

    //шапка таблицы
    cout << char(218) << setfill(char(196));
    for (int j = 0; j < m - 1; j++)
        cout << setw(wn[j]) << char(194);
    cout << setw(wn[m - 1]) << char(191) << endl;

    cout << char(179);
    for (int j = 0; j < m; j++)
        cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
             << setw((wn[j] - size[j]) / 2) << char(179);
    cout << endl;

    //заполнение таблицы
    for (int i = 0; i < k; i++) {
        cout << char(195) << fixed;
        for (int j = 0; j < m - 1; j++)
            cout << setfill(char(196)) << setw(wn[j]) << char(197);
        cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;
        cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name
             << setw(((wn[0] - strlen(i_prn[i].name)) / 2) + (strlen(i_prn[i].name) % 2)) << char(179);
        cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
             << setw(wn[2] - 1) << i_prn[i].i_sum << setprecision(6) << char(179)
             << setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
    }

    //низ таблицы
    cout << char(192) << setfill(char(196));
    for (int j = 0; j < m - 1; j++)
        cout << setw(wn[j]) << char(193);
    cout << setw(wn[m - 1]) << char(217) << setfill(' ') << endl;
}
