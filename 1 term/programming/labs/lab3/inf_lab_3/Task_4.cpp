#include "Task_4.h"
#include <iostream>
#include <cmath>

using namespace std;

float y(int n, int i) {
    if (i<=n)
        return sqrt(2*i+y(n,i+1));
    else
        return 0;
}

void task4() {
    cout << "\n--- №4 ---\n";
    cout << "y(3) = " << y(3,1) << "\n";
    cout << "y(5) = " << y(5,1) << "\n";
    cout << "y(10) = " << y(10,1) << "\n\n";

    int n;
    char flag;
    do {
        cout << "Введите n:\n";
        cin >> n;
        cout << "y(" << n << ") = " << y(n,1) << "\n\n";

        cout << "Продолжить работу? (y/n):\n";
        cin >> flag;
    } while (flag == 'y');
}
