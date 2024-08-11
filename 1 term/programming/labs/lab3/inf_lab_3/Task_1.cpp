#include <iostream>
#include "Task_1.h"

using namespace std;

int get_sum(int n, int m) {
    int sum = 0, count = 0, i = 1;

    while (count < n) {
        if (i % 5 == 0 && i % m != 0) {
            sum += i;
            count++;
        }
        i++;
    }
    return sum;
}

void task1() {
    cout << "\n--- №1 ---\n";

    char flag = 'y';
    int n = 0, m = 0;
    do {
        cout << "Введите n и m (n < m):\n";
        cin >> n >> m;

        if (n < m) cout << "Введены недопустимые данные\n\n";
        else if (m == 5) cout << "Сумма = 0\n\n";
        else cout << "Сумма = " << get_sum(n, m) << "\n\n";

        cout << "Продолжить работу? (y/n):\n";
        cin >> flag;
    } while (flag == 'y');
}
