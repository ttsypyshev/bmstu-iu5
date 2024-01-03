#include <iostream>
#include "Task_1.h"
#include "Task_2.h"
#include "Task_3.h"
#include "Task_4.h"

using namespace std;

int main() {
    system("chcp 65001");
    int flag = 0;
    cout << "Введите номер задачи (1-4):\n";
    cin >> flag;

    if (flag == 1) task1();
    else if (flag == 2) task2();
    else if (flag == 3) task3();
    else if (flag == 4) task4();
    else cout << "Такой задачаи нет";

//     task1();
//     task2();
//     task3();
//     task4();

    return 0;
}
