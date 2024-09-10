/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include "../include/Header.h"

using namespace std;


int main() {
    // сначала вводим в виде строки, потом переводим в int
    // необходимо, что бы избавиться от ошибки закцикливания при вводе некоректного значения пользователем
    int item = 8;
    char str_item[1];
    while (true) {
        // вызываем конкретные ф-ии в зависимости от выбранного пункта меню
        if (item == 1) AddItem();
        else if (item == 2) RemoveItem();
        else if (item == 3) EditItem();
        else if (item == 4) ViewingDictionary();
        else if (item == 5) FindItem();
        else if (item == 6) LoggingDictionary();
        else if (item == 7) SortDictionary();
        else if (item == 8) Help();
        else if (item == 9) return 0;
        else { cout << "Данные введены не верно! Введите номер заново.\n"; }
        cout << "\nВыберете пункт меню (1-9):\n";
        cin >> str_item;
        item = atoi(str_item);
    }
}
